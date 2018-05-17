#include "eggplayer.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
EggPlayer::EggPlayer(QWidget *parent) :
    QWidget(parent),
    pm_library(new Library(this)),
    pm_musicLibrary(new MusicLibrary(this)),
    pm_musicBar(new MusicBar(this))
{
    setupUi();

    connect(pm_library, SIGNAL(inserted(Audio*, int)), pm_musicLibrary, SLOT(insert(Audio*, int)));
    connect(pm_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onMusicLibraryDoubleClicked(QModelIndex)));

    pm_library->setSorted(true);
    pm_library->load(Config::Library::paths());
}

/*
 * Destructor.
 */
EggPlayer::~EggPlayer()
{

}

/*
 * Loads the saved registry position and shows
 * the window. Should be called instead of show().
 */
void EggPlayer::showSavedPosition()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    move(settings.value("pos", pos()).toPoint());
    resize(settings.value("size", size()).toSize());

    if (settings.value("maximized", isMaximized()).toBool())
        showMaximized();
    else
        show();
}

/*
 * Implemented close event to save current
 * position before closing.
 *
 * :param event: event
 */
void EggPlayer::closeEvent(QCloseEvent *event)
{
    savePosition();
    QWidget::closeEvent(event);
}

/*
 * Musc library double clicked event. It starts
 * the player with the clicked audio.
 *
 * :param index: index
 */
void EggPlayer::onMusicLibraryDoubleClicked(const QModelIndex &index)
{
    pm_musicBar->player()->loadPlaylist(pm_library->audios(), index.row());
    pm_musicBar->player()->play();
}

/*
 * Sets up user interface.
 */
void EggPlayer::setupUi()
{
    QLabel *west = new QLabel(this);
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    pm_musicLibrary->showColumn(MusicLibrary::Title);
    pm_musicLibrary->showColumn(MusicLibrary::Artist);
    pm_musicLibrary->showColumn(MusicLibrary::Album);
    pm_musicLibrary->showColumn(MusicLibrary::Year, Qt::AlignLeft, false);
    pm_musicLibrary->showColumn(MusicLibrary::Genre);
    pm_musicLibrary->showColumn(MusicLibrary::Length, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(pm_musicLibrary, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(pm_musicBar, BorderLayout::South);
    setLayout(layout);
}

/*
 * Saves current position in registry. Does not
 * need to be in config because position is not
 * really relevant there.
 */
void EggPlayer::savePosition()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("maximized", isMaximized());
    if (!isMaximized())
    {
        settings.setValue("pos", pos());
        settings.setValue("size", size());
    }
}
