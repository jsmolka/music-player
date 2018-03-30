#ifndef CACHE_HPP
#define CACHE_HPP

#include <QBuffer>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "src/core/audio.hpp"
#include "src/constants/constant.hpp"

class Cache
{
public:
    Cache();
    ~Cache();

    bool connect();
    void close();
    bool insert(Audio audio);
    bool exists(Audio audio);
    QPixmap cover(const QString &path, int size);

private:
    QByteArray coverToBytes(const QPixmap &cover);
    int lastCoverId();
    int coverId(const QByteArray &bytes);
    int insertCover(const QByteArray &bytes);
    QPixmap scale(QPixmap pixmap, int size);

    QSqlDatabase m_db;

};

#endif // CACHE_HPP
