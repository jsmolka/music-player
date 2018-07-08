#include "audio.hpp"

Audio::Audio(const QString &path)
    : m_valid(true)
    , m_path(path)
    , m_coverId(-1)
    , m_outdated(false)
    , m_size(FileUtil::size(path))
{
    if (!(m_valid = readTags()))
    {
        if (!FileUtil::exists(path))
            log("Audio: File does not exist %1", {m_path});
        else
            log("Audio: Cannot read tags %1", {m_path});
    }
}

Audio::Audio(const QString &path, const QString &title, const QString &artist,
             const QString &album, const QString &genre, int year, int track,
             int length, int coverId, int size)
    : m_valid(true)
    , m_path(path)
    , m_title(title)
    , m_artist(artist)
    , m_album(album)
    , m_genre(genre)
    , m_year(year)
    , m_track(track)
    , m_duration(length)
    , m_coverId(coverId)
    , m_size(size)
{
    m_outdated = size != FileUtil::size(path);
}

Audio::~Audio()
{

}

bool Audio::isValid() const
{
    return m_valid;
}

QString Audio::path() const
{
    return m_path;
}

QString Audio::title() const
{
    return m_title;
}

QString Audio::artist() const
{
    return m_artist;
}

QString Audio::album() const
{
    return m_album;
}

QString Audio::genre() const
{
    return m_genre;
}

int Audio::year() const
{
    return m_year;
}

int Audio::track() const
{
    return m_track;
}

int Audio::duration() const
{
    return m_duration;
}

void Audio::setCoverId(int id)
{
    m_coverId = id;
}

int Audio::coverId() const
{
    return m_coverId;
}

quint64 Audio::size() const
{
    return m_size;
}

bool Audio::isOutdated() const
{
    return m_outdated;
}

const wchar_t * Audio::pathWChar() const
{
    return reinterpret_cast<const wchar_t *>(m_path.constData());
}

QPixmap Audio::cover(int size)
{
    return Tag(pathWChar()).cover(size);
}

bool Audio::readTags()
{
    Tag tag(pathWChar());

    if (!tag.isAudioValid())
        return false;

    m_duration = tag.duration();

    if (tag.isTagValid())
    {
        m_title = tag.title();
        m_artist = tag.artist();
        m_album = tag.album();
        m_genre = tag.genre();
        m_year = tag.year();
        m_track = tag.track();
    }

    if (m_title.isEmpty())
        m_title = FileUtil::fileName(m_path);

    return true;
}
