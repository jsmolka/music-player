#include "tag.hpp"

#include <QFileInfo>

#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "logger.hpp"
#include "utils.hpp"

Tag::Tag(QObject *parent)
    : Tag(QString(), parent)
{

}

Tag::Tag(const File &file, QObject *parent)
    : QObject(parent)
    , m_file(file)
    , m_year(0)
    , m_track(0)
    , m_duration(0)
{

}

bool Tag::read()
{
    const TagLib::MPEG::File file(Util::toWString(m_file));

    if (!file.isValid() || !file.audioProperties())
    {
        LOG(QFileInfo::exists(m_file)
            ? "Cannot read tags %1"
            : "File does not exist %1", m_file);
        return false;
    }

    m_duration = file.audioProperties()->lengthInSeconds();

    if (file.tag())
    {
        TagLib::Tag *tag = file.tag();
        m_title = Util::toQString(tag->title());
        m_artist = Util::toQString(tag->artist());
        m_album = Util::toQString(tag->album());
        m_genre = Util::toQString(tag->genre());
        m_year = static_cast<int>(tag->year());
        m_track = static_cast<int>(tag->track());
    }

    if (m_title.isEmpty())
        m_title = QFileInfo(m_file).baseName();

    return true;
}

void Tag::setFile(const File &file)
{
    m_file = file;
}

File Tag::file() const
{
    return m_file;
}

void Tag::setTitle(const QString &title)
{
    m_title = title;
}

QString Tag::title() const
{
    return m_title;
}

void Tag::setArtist(const QString &artist)
{
    m_artist = artist;
}

QString Tag::artist() const
{
    return m_artist;
}

void Tag::setAlbum(const QString &album)
{
    m_album = album;
}

QString Tag::album() const
{
    return m_album;
}

void Tag::setGenre(const QString &genre)
{
    m_genre = genre;
}

QString Tag::genre() const
{
    return m_genre;
}

void Tag::setYear(int year)
{
    m_year = year;
}

int Tag::year() const
{
    return m_year;
}

void Tag::setTrack(int track)
{
    m_track = track;
}

int Tag::track() const
{
    return m_track;
}

void Tag::setDuration(int duration)
{
    m_duration = duration;
}

int Tag::duration() const
{
    return m_duration;
}
