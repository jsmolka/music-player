#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QVector>

#include "audio.hpp"
#include "audios.hpp"
#include "tablewidget.hpp"

class AudiosWidget : public TableWidget
{
    Q_OBJECT

public:
    explicit AudiosWidget(QWidget *parent = nullptr);

    enum AudioInfo {Title, Artist, Album, Track, Year, Genre, Duration};

    void setAudios(Audios *audios);
    void addColumn(AudioInfo info, Qt::Alignment horizontal = Qt::AlignLeft, bool expand = true);

public slots:
    void insert(Audio *audio, int row = -1);

private slots:
    void onAudiosUpdated(int index);
    void onAudioInserted(int index);
    void onAudiosRemoved(int index);

private:
    struct Column
    {
        Column(AudioInfo info = AudioInfo::Title, Qt::Alignment alignment = Qt::AlignLeft) :
            info(info), alignment(alignment) {}

        AudioInfo info;
        Qt::Alignment alignment;
    };
    QString audioText(Audio *audio, int column) const;

    void setup();
    void setupCss();

    Audios *m_audios;
    QVector<Column> m_columns;
};

#endif // AUDIOSWIDGET_HPP