#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include "core/audios/frozenvector.hpp"
#include "core/audios/currentstate.hpp"

class Audios : public audios::FrozenVector
{
    Q_OBJECT

public:
    using audios::FrozenVector::FrozenVector;

    void insert(int index, const Audio &audio);
    void append(const Audio &audio);
    void remove(int index);

    Audios::iterator insert(Audios::iterator before, const Audio &audio);
    Audios::iterator erase(Audios::iterator position);

    int lowerBound(const Audio &audio);

    audios::CurrentState *currentState();

    Audios &operator<<(const Audio &audio);

public slots:
    void removeAudio(const Audio &audio);

signals:
    void inserted(int index);
    void updated(int index);
};

#endif // AUDIOS_HPP
