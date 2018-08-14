#include "library.hpp"

Library::Library(QObject *parent)
    : Library(false, parent)
{

}

Library::Library(bool sorted, QObject *parent)
    : QObject(parent)
    , m_sorted(sorted)
    , m_audios(this)
    , m_fileSystem(this)
    , m_audioLoader(this)
    , m_audioUpdater(this)
    , m_coverLoader(this)
{
    connect(&m_audioLoader, &AudioLoaderController::loaded, this, &Library::insert);
    connect(&m_audioLoader, &AudioLoaderController::finished,this, &Library::onAudioLoaderFinished);
}

Library::~Library()
{
    while (!m_audios.isEmpty())
        delete m_audios.takeFirst();
}

Library * Library::instance()
{
    static Library *library = new Library(qApp);
    return library;
}

void Library::setSorted(bool sorted)
{
    m_sorted = sorted;
}

bool Library::isSorted() const
{
    return m_sorted;
}

Audios * Library::audios()
{
    return &m_audios;
}

AudioLoaderController * Library::audioLoader()
{
    return &m_audioLoader;
}

AudioUpdaterController * Library::audioUpdater()
{
    return &m_audioUpdater;
}

CoverLoaderController * Library::coverLoader()
{
    return &m_coverLoader;
}

void Library::load(const Paths &paths)
{
    for (const Path path: paths)
        m_fileSystem.addPath(path);

    m_audioLoader.setFiles(m_fileSystem.globAudios());
    m_audioLoader.start();
}

void Library::insert(Audio *audio)
{
    int index = m_sorted ? insertBinary(audio) : insertLinear(audio);
    emit inserted(audio, index);
}

void Library::onAudioLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

int Library::lowerBound(Audio *audio)
{
    int low = 0;
    int high = m_audios.size();
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (*audio < *m_audios.at(mid))
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

int Library::insertBinary(Audio *audio)
{
    int index = lowerBound(audio);
    m_audios.insert(index, audio);
    return index;
}

int Library::insertLinear(Audio *audio)
{
    m_audios << audio;
    return -1;
}
