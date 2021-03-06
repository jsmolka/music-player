#include "expiringthread.hpp"

#include <QApplication>

ExpiringThread::ExpiringThread(QObject *parent)
    : QObject(parent)
    , m_thread(new Thread(this))
    , m_timer(this)
    , m_quitting(false)
{
    connect(m_thread, &Thread::emptied, this, &ExpiringThread::onEmptied);
    connect(&m_timer, &QTimer::timeout, this, &ExpiringThread::onTimeout);
    connect(qApp, &QApplication::aboutToQuit, this, &ExpiringThread::onQuitting);

    m_timer.setSingleShot(true);
}

Thread *ExpiringThread::thread()
{
    return m_thread;
}

void ExpiringThread::onEmptied()
{
    if (!m_quitting)
        m_timer.start(30000);
}

void ExpiringThread::onTimeout()
{
    if (m_thread->isEmpty())
    {
        m_thread->waitToQuit();
        m_thread->deleteLater();
        emit expired(this);
    }
}

void ExpiringThread::onQuitting()
{
    m_quitting = true;
}
