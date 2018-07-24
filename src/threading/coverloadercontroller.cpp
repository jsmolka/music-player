#include "coverloadercontroller.hpp"

CoverLoaderController::CoverLoaderController(QObject *parent)
    : CoverLoaderController(Audios(), parent)
{

}

CoverLoaderController::CoverLoaderController(Audios audios, QObject *parent)
    : AbstractController(parent)
    , m_audios(audios)
{

}

CoverLoaderController::~CoverLoaderController()
{

}

void CoverLoaderController::setAudios(const Audios &audios)
{
    m_audios = audios;
}

Audios CoverLoaderController::audios() const
{
    return m_audios;
}

void CoverLoaderController::start()
{
    for (Audios chunk : Util::chunk<Audio *>(m_audios, QThread::idealThreadCount()))
        createWorkerThread(new CoverLoaderWorker(chunk))->start();
}
