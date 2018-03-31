#include "eggplayer.hpp"

EggPlayer::EggPlayer() : QWidget()
{
    m_library = Library("C:/Users/Julian/Music/Tiny Moving Parts");
    m_cache.connect();

    setupUi();
}

EggPlayer::~EggPlayer()
{

}

void EggPlayer::start(const QModelIndex &index)
{
    Player *player = pm_musicBar->player();
    IconButton *playButton = pm_musicBar->playButton();
    IconButton *shuffleButton = pm_musicBar->shuffleButton();

    player->setAudioList(m_library.audioList());
    player->setCurrentIndex(index.row());
    if (shuffleButton->isLocked())
        player->shuffle();
    player->play();

    playButton->setSelected(1);
}

void EggPlayer::play()
{
    Player *player = pm_musicBar->player();
    IconButton *playButton = pm_musicBar->playButton();

    if (player->currentIndex() != -1)
    {
        playButton->switchIcon();

        if (!playButton->isSelected())
            player->play();
        else
            player->pause();
    }
}

void EggPlayer::stop()
{
    Player *player = pm_musicBar->player();
    IconButton *playButton = pm_musicBar->playButton();

    player->pause();

    playButton->setSelected(0);
}

void EggPlayer::loop()
{
    Player *player = pm_musicBar->player();
    IconButton *replayButton = pm_musicBar->loopButton();

    if (replayButton->isLocked())
        player->setLoop(true);
    else
        player->setLoop(false);
}

void EggPlayer::change(Audio *audio)
{
    updateTrackInfo(audio);
}

void EggPlayer::shuffle()
{
    Player *player = pm_musicBar->player();
    IconButton *shuffleButton = pm_musicBar->shuffleButton();

    if (player->currentIndex() != -1)
    {
        if (shuffleButton->isLocked())
            player->shuffle();
        else
            player->unshuffle();
    }
}

void EggPlayer::setupUi()
{
    createMusicLibrary();
    createMusicBar();

    QLabel *west = new QLabel;
    west->setFixedWidth(315);
    west->setStyleSheet("QLabel {background-color: #666666;}");

    BorderLayout *layout = new BorderLayout(0);
    layout->addWidget(pm_musicLibrary, BorderLayout::Center);
    layout->addWidget(west, BorderLayout::West);
    layout->addWidget(pm_musicBar, BorderLayout::South);
    setLayout(layout);
}

void EggPlayer::updateTrackInfo(Audio *audio)
{
    QLabel *trackLabel = pm_musicBar->trackLabel();
    QLabel *coverLabel = pm_musicBar->coverLabel();

    QString path = audio->path();
    QString title = audio->title();
    QString artist = audio->artist();
    QPixmap cover = m_cache.cover(path, 50);

    trackLabel->setText(QString("%1\n%2").arg(title, artist));
    coverLabel->setPixmap(cover);
}

void EggPlayer::createMusicLibrary()
{
    pm_musicLibrary = new MusicLibrary(&m_library, this);

    connect(pm_musicLibrary, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(start(QModelIndex)));
}

void EggPlayer::createMusicBar()
{
    pm_musicBar = new MusicBar(this);

    Player *player = pm_musicBar->player();
    player->setVolume(5);

    connect(pm_musicBar->playButton(), SIGNAL(pressed()), this, SLOT(play()));
    connect(pm_musicBar->loopButton(), SIGNAL(locked()), this, SLOT(loop()));
    connect(pm_musicBar->shuffleButton(), SIGNAL(locked()), this, SLOT(shuffle()));

    connect(pm_musicBar->nextButton(), SIGNAL(pressed()), pm_musicBar->player(), SLOT(next()));
    connect(pm_musicBar->backButton(), SIGNAL(pressed()), pm_musicBar->player(), SLOT(back()));

    connect(pm_musicBar->player(), SIGNAL(changed(Audio *)), this, SLOT(change(Audio *)));
    connect(pm_musicBar->player(), SIGNAL(stopped()), this, SLOT(stop()));
}
