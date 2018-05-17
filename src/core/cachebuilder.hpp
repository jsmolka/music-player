#ifndef CACHEBUILDER_HPP
#define CACHEBUILDER_HPP

#include <QApplication>
#include <QThread>

#include "audio.hpp"
#include "cache.hpp"

class CacheBuilder : public QThread
{
    Q_OBJECT

public:
    CacheBuilder(QObject *parent = nullptr);
    CacheBuilder(const Audios &audios, QObject *parent = nullptr);
    ~CacheBuilder();

    void setAudios(const Audios &audios);

public slots:
    void abort();

protected:
    void run() override;

private:
    bool m_abort;
    Audios m_audios;
};

#endif // CACHEBUILDER_HPP
