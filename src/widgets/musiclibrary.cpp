#include "musiclibrary.hpp"


MusicLibrary::MusicLibrary(QWidget *parent)
    : TableWidget(parent)
{
    setup();
}

MusicLibrary::~MusicLibrary()
{

}

void MusicLibrary::addColumn(SongInfo info, Qt::Alignment horizontal, bool expand)
{
    m_columns << Column(info, Qt::AlignVCenter | horizontal);
    setColumnCount(m_columns.size());

    if (!expand)
        horizontalHeader()->setSectionResizeMode(m_columns.size() - 1, QHeaderView::ResizeToContents);
}

void MusicLibrary::insert(Audio *audio, int row)
{
    setUpdatesEnabled(false);

    if (row == -1)
        row = rowCount();
    insertRow(row);

    for (int i = 0; i < m_columns.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(audioText(audio, i));
        item->setTextAlignment(m_columns[i].alignment);
        setItem(row, i, item);
    }
    setUpdatesEnabled(true);
}

void MusicLibrary::loadCss()
{
    setStyleSheet(
        FileUtil::read(CSS_MUSICLIBRARY)
            .replace("cell-padding", QString::number(cfgLibrary->cellPadding()))
            .replace("scrollbar-width", QString::number(cfgLibrary->scrollBarWidth()))
    );
}

void MusicLibrary::setup()
{
    loadCss();

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(cfgLibrary->itemHeight());
}

QString MusicLibrary::audioText(Audio *audio, int column)
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
        case SongInfo::Length:
            return Util::time(audio->duration());
    }
    return QString();
}
