#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>

#include <bass/bass.h>

#include "audio.hpp"
#include "timer.hpp"

#define eggPlayer (Player::instance())

class Player : public QObject
{
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);
    ~Player();

    static Player * instance();

    enum State {Playing, Paused};

    void setIndex(int index);
    int index() const;

    bool isLoop() const;
    bool isShuffle() const;
    bool isPlaying() const;

    int volume() const;
    int position() const;

    void loadPlaylist(const Audios &audios, int index = 0);

    Audio * audioAt(int index);
    Audio * currentAudio();

    int indexAt(int index);
    int currentIndex();

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void setLoop(bool loop);
    void setShuffle(bool shuffle);

    void play();
    void pause();

    void next();
    void previous();

signals:
    void audioChanged(Audio *audio);
    void stateChanged(Player::State state);
    void positionChanged(int position);
    void volumeChanged(int volume);

private slots:
    void onTimeout(qint64 elapsed);

private:
    struct AudioPosition
    {
        AudioPosition(int index = -1, Audio *audio = nullptr)
        {
            this->index = index;
            this->audio = audio;
        }

        int index;
        Audio *audio;
    };

    bool bassCreate();
    bool bassFree();
    bool bassCreateStream(Audio *audio);
    bool bassFreeStream();
    bool bassValidStream();
    bool bassSetVolume(int volume);
    bool bassSetPosition(int position);
    bool bassPlay();
    bool bassPause();

    void logAudio(const QString &message);

    bool validIndex(int index);

    void switchOrPause(int index);
    int nextIndex();
    int previousIndex();

    void shuffle();
    void unshuffle();

    void setAudio(int index);

    QVector<AudioPosition> m_playlist;
    Timer *pm_timer;
    HSTREAM m_stream;
    int m_index;
    int m_volume;
    bool m_loop;
    bool m_shuffle;
    bool m_playing;

    static Player *_instance;
};

#endif // PLAYER_HPP
