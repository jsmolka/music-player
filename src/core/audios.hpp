#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include <QObject>

#include "core/audio.hpp"
#include "core/globals.hpp"

class Audios : public QObject, private Audio::vector
{
    Q_OBJECT

public:
    explicit Audios(QObject *parent = nullptr);
    explicit Audios(const Audio::vector &vector, QObject *parent = nullptr);

    Audio::vector vector() const;

    Audio *at(int index);
    Audio *at(int index) const;
    Audio *first() const;
    Audio *last() const;

    bool isEmpty() const;

    int size() const;
    int indexOf(Audio *audio, int from = 0) const;

    void clear();
    void reserve(int size);

    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);
    void remove(Audio *audio);
    void move(int from, int to);

    Audios::iterator insert(Audios::iterator before, Audio *audio);
    Audios::iterator erase(Audios::iterator position);

    Audios::iterator begin();
    Audios::iterator end();

    Audios::const_iterator cbegin() const;
    Audios::const_iterator cend() const;

    Audios &operator<<(Audio *audio);
    Audio *operator[](int index);

    Audios *currentState();

signals:
    void inserted(int index);
    void removed(int index);
    void removedAudio(Audio *audio);
    void moved(int from, int to);
    void updated(int index);

private slots:
    void onParentAudioRemoved(Audio *audio);
};

#endif // AUDIOS_HPP
