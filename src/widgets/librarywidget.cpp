#include "librarywidget.hpp"

#include <QHeaderView>

#include "config.hpp"
#include "constants.hpp"
#include "fileutil.hpp"

LibraryWidget::LibraryWidget(QWidget *parent)
    : TableWidget(parent)
    , m_audios(nullptr)
    , m_columns()
{
    setup();
}

LibraryWidget::~LibraryWidget()
{

}

void LibraryWidget::setAudios(Audios *audios)
{
    m_audios = audios;

    connect(audios, &Audios::inserted, this, &LibraryWidget::onAudioInserted);
    connect(audios, &Audios::updated, this, &LibraryWidget::onAudiosUpdated);
    connect(audios, &Audios::removed, this, &LibraryWidget::onAudiosRemoved);
}

void LibraryWidget::removeAudios()
{
    if (m_audios)
        disconnect(m_audios, &Audios::inserted, this, &LibraryWidget::onAudioInserted);

    m_audios = nullptr;
}

void LibraryWidget::addColumn(SongInfo info, Qt::Alignment horizontal, bool expand)
{
    m_columns << Column(info, Qt::AlignVCenter | horizontal);
    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void LibraryWidget::onAudiosUpdated(Audio *audio)
{
    const int row = m_audios ->indexOf(audio);

    removeRow(row);
    insert(audio, row);
}

void LibraryWidget::onAudioInserted(int index)
{
    insert(m_audios->at(index), index);
}

void LibraryWidget::onAudiosRemoved(int index)
{
    removeRow(index);
}

void LibraryWidget::insert(Audio *audio, int row)
{
    setUpdatesEnabled(false);

    insertRow(row);
    for (int i = 0; i < m_columns.size(); ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(audioText(audio, i));
        item->setTextAlignment(m_columns[i].alignment);
        setItem(row, i, item);
    }

    setUpdatesEnabled(true);
}

void LibraryWidget::setup()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(cfgLibrary.itemHeight());

    setupCss();
}

void LibraryWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_LIBRARY)
        .replace("cell-padding", QString::number(cfgLibrary.cellPadding()))
        .replace("scrollbar-width", QString::number(cfgLibrary.scrollBarWidth()))
    );
}

QString LibraryWidget::audioText(Audio *audio, int column) const
{
    switch(m_columns[column].info)
    {
        case SongInfo::Title:
            return audio->title();
        case SongInfo::Artist:
            return audio->artist();
        case SongInfo::Album:
            return audio->album();
        case SongInfo::Track:
            return audio->track() == 0 ? QString() : QString::number(audio->track());
        case SongInfo::Year:
            return audio->year() == 0 ? QString() : QString::number(audio->year());
        case SongInfo::Genre:
            return audio->genre();
        case SongInfo::Duration:
            return audio->duration().toString();
    }
    return QString();
}
