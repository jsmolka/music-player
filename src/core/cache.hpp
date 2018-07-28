#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QHash>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

#include "audio.hpp"
#include "constants.hpp"
#include "util.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    bool transaction();
    bool commit();
    bool rollback();

    void createTables();

    Audio * loadAudio(const QString &path);
    void insertAudio(Audio *audio);
    void updateAudio(Audio *audio);

    int insertCover(const QPixmap &cover);
    void updateCover(const QPixmap &cover);
    void setAudioCoverId(Audio *audio, int id);

    QPixmap coverById(int id);
    QPixmap coverByAudioPath(Audio *audio);

private:
    static QString dbName();
    static QSqlDatabase db();
    static QByteArray coverToBytes(const QPixmap &cover);

    void createCovers();
    void createAudios();
    bool defaultCoverExists();
    void insertDefaultCover();

    int insertByteCover(const QByteArray &bytes);
    void updateByteCover(int id, const QByteArray &bytes);

    int coverId(const QByteArray &bytes);
    int lastCoverId();
    int coverIdBySize(int size);
    int coverIdByBlob(const QByteArray &bytes);

    void error();

    QString lastQuery();

    QSqlDatabase m_db;
    QSqlQuery m_query;
};

#endif // CACHE_HPP
