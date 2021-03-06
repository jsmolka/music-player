#include "audios.hpp"

void Audios::insert(int index, const Audio &audio)
{
    QVector<Audio>::insert(index, audio);
    emit inserted(index);
}

void Audios::append(const Audio &audio)
{
    QVector<Audio>::append(audio);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    Audio audio = at(index);
    QVector<Audio>::remove(index);
    emit removed(index);
    emit removedAudio(audio);
}

Audios::iterator Audios::insert(Audios::iterator before, const Audio &audio)
{
    auto position = QVector<Audio>::insert(before, audio);
    emit inserted(static_cast<int>(position - begin()));

    return position;
}

Audios::iterator Audios::erase(Audios::iterator position)
{
    auto next = QVector<Audio>::erase(position);
    emit removed(static_cast<int>(position - begin()));
    emit removedAudio(*position);

    return next;
}

int Audios::lowerBound(const Audio &audio)
{
    int low = 0;
    int high = size();
    while (low < high)
    {
        const int mid = (low + high) / 2;
        const int cmp = audio.tag().title().compare(at(mid).tag().title(), Qt::CaseInsensitive);
        if (cmp < 0)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

audios::CurrentState *Audios::currentState()
{
    return new audios::CurrentState(*this, this);
}

Audios &Audios::operator<<(const Audio &audio)
{
    append(audio);

    return *this;
}

void Audios::removeAudio(const Audio &audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        remove(index);
}
