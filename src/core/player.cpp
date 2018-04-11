#include "player.hpp"

Player::Player(QWidget *parent) : QWidget(parent)
{
    qsrand(time(0));

    pm_player = new QMediaPlayer(this);
    pm_player->setPlaylist(new QMediaPlaylist(this));
    pm_timer = new Timer(1000, this);

    m_index = -1;
    m_loop = false;
    m_shuffled = false;
    m_playing = false;

    connect(pm_player->playlist(), SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChanged(int)));
    connect(pm_player, SIGNAL(volumeChanged(int)), this, SIGNAL(volumeChanged(int)));

    connect(pm_timer, SIGNAL(timeout(qint64)), this, SLOT(onTimeout(qint64)));
}

Player::~Player()
{

}

Timer * Player::timer()
{
    return pm_timer;
}

void Player::setIndex(int index)
{
    m_index = index;
    if (index != -1)
        setActiveAudio(index);
}

int Player::index() const
{
    return m_index;
}

bool Player::isLoop() const
{
    return m_loop;
}

bool Player::isShuffled() const
{
    return m_shuffled;
}

int Player::volume() const
{
    return pm_player->volume();
}

int Player::position() const
{
    return pm_timer->total() + (pm_timer->interval() - pm_timer->remaining());
}

bool Player::isPlaying() const
{
    return m_playing;
}

void Player::setAudioList(const AudioList &audioList)
{
    m_index = -1;
    m_shuffled = false;
    m_playing = false;

    m_playlist.clear();

    for (int i = 0; i < audioList.size(); i++)
        m_playlist << AudioPosition(i, audioList[i]);
}

Audio * Player::audioAt(int index)
{
    return m_playlist[index].audio;
}

Audio * Player::currentAudio()
{
    return audioAt(m_index);
}

int Player::nextIndex()
{
    if (m_index == -1)
        return -1;

    if (m_index == m_playlist.size() - 1)
        return m_loop ? 0 : -1;

    return ++m_index;
}

int Player::backIndex()
{
    if (m_index == -1)
        return -1;

    if (m_index == 0)
        return m_loop ? m_playlist.size() - 1 : -1;

    return --m_index;
}

void Player::setVolume(int volume)
{
    pm_player->setVolume(volume);
}

void Player::setPosition(int position)
{
    if (m_index != -1)
    {
        pm_player->setPosition(position * 1000);
        pm_timer->setTotal(position * 1000);
    }
}

void Player::setLoop(bool loop)
{
    m_loop = loop;
}

void Player::setShuffled(bool shuffled)
{
    if (m_shuffled != shuffled && m_index != -1)
    {
        if (shuffled)
            shuffle();
        else
            unshuffle();
    }
}

void Player::play()
{
    pm_player->play();
    pm_timer->start();
    m_playing = true;
    emit stateChanged(true);
}

void Player::pause()
{
    pm_player->pause();
    pm_timer->pause();
    m_playing = false;
    emit stateChanged(false);
}

void Player::next()
{
    int index = nextIndex();
    if (index != -1)
    {
        m_index = index;
        setActiveAudio(index);
    }
    else
    {
        pause();
        setPosition(0);
    }
}

void Player::back()
{
    int index = backIndex();
    if (index != -1)
    {
        m_index = index;
        setActiveAudio(index);
    }
}

void Player::onIndexChanged(int index)
{
    if (index == -1)
        next();

    if (m_index != -1)
        emit audioChanged(audioAt(m_index));
}

void Player::onTimeout(qint64 total)
{
    emit positionChanged(total / 1000);
}

void Player::shuffle()
{
    Audio * audio = currentAudio();

    std::random_shuffle(m_playlist.begin(), m_playlist.end());

    // Put current audio at the front
    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_playlist.swap(0, i);
            break;
        }
    }
    m_index = 0;
    m_shuffled = true;
}

void Player::unshuffle()
{
    Audio *audio = currentAudio();

    std::sort(m_playlist.begin(), m_playlist.end(),
        [](const AudioPosition &ap1, const AudioPosition &ap2) {return ap1.index < ap2.index;});

    // Find index of current audio
    for (int i = 0; i < m_playlist.size(); i++)
    {
        if (audio == audioAt(i))
        {
            m_index = i;
            break;
        }
    }
    m_shuffled = false;
}

void Player::setActiveAudio(int index)
{
    QMediaPlaylist *playlist = pm_player->playlist();

    playlist->clear();
    playlist->addMedia(audioAt(index)->url());
    playlist->setCurrentIndex(0);

    pm_timer->restart();

    if (m_playing)
        play();
}
