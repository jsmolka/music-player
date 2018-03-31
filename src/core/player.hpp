#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = 0);
    ~Player();

    void setCurrentIndex(int index);
    int currentIndex();

    void setLoop(bool loop);
    bool isLoop() const;

    bool isShuffled() const;

    int volume() const;
    int position() const;

    bool isPlaying() const;

    void setAudioList(const AudioList &audioList);

    Audio * audioAt(int index);
    Audio * currentAudio();

    int nextIndex();
    int backIndex();

    void shuffle();
    void unshuffle();

public slots:
    void setVolume(int volume);
    void setPosition(int position);

    void play();
    void pause();
    void next();
    void back();

signals:
    void changed(Audio *audio);
    void stopped();

private slots:
    void slotAutoPlay(int index);
    void slotAudioChanged();

private:
    struct AudioPosition
    {
        AudioPosition(int i, Audio *a)
        {
            index = i;
            audio = a;
        }

        int index;
        Audio *audio;
    };

    void playAudio(int index);

    QMediaPlayer *pm_player;
    QList<AudioPosition> m_playlist;
    int m_currentIndex;
    bool m_loop;
    bool m_shuffled;
    bool m_playing;

};

#endif // PLAYER_HPP
