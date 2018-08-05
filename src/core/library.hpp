#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <QApplication>
#include <QFileSystemWatcher>
#include <QObject>
#include <QSet>

#include "audio.hpp"
#include "audioloadercontroller.hpp"
#include "coverloadercontroller.hpp"
#include "types.hpp"

#define eLibrary (Library::instance())

class Library : public QObject
{
    Q_OBJECT

public:
    Library(QObject *parent = nullptr);
    Library(bool sorted, QObject *parent = nullptr);
    ~Library();

    static Library * instance();

    void setSorted(bool sorted);
    bool isSorted() const;

    Audios audios() const;
    CoverLoaderController * coverLoader();
    AudioLoaderController * audioLoader();

    void load(const Paths &paths);

public slots:
    void insert(Audio *audio);
    void remove(const QString &file);

signals:
    void inserted(Audio *audio, int index);
    void removed(int index);

private slots:
    void onAudioLoaderFinished();
    void onWatcherFileChanged(const QString &file);

private:
    int lowerBound(Audio *audio);
    int insertBinary(Audio *audio);
    int insertLinear(Audio *audio);

    int removeLinear(const QString &file);

    Files globFiles(const Paths &paths);

    bool m_sorted;
    Audios m_audios;
    QSet<QString> m_loaded;
    QFileSystemWatcher m_watcher;
    AudioLoaderController m_audioLoader;
    CoverLoaderController m_coverLoader;

};

#endif // LIBRARY_HPP
