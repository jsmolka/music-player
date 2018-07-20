#include "barwidget.hpp"

BarWidget::BarWidget(QWidget *parent)
    : ColorTransitionWidget(parent)
    , m_coverLabel(this)
    , m_trackLabel(this)
    , m_currentTimeLabel(this)
    , m_totalTimeLabel(this)
    , m_playPauseButton(this)
    , m_nextButton(this)
    , m_previousButton(this)
    , m_shuffleButton(this)
    , m_loopButton(this)
    , m_volumeButton(this)
    , m_lengthSlider(this)
    , m_volumeSlider(this)
    , m_scPlayPause(cfgShortcut->playPause(), false, this)
    , m_scNext(cfgShortcut->next(), false, this)
    , m_scPrevious(cfgShortcut->previous(), false, this)
    , m_scVolumeUp(cfgShortcut->volumeUp(), true, this)
    , m_scVolumeDown(cfgShortcut->volumeDown(), true, this)
{
    setup();
    setupUi();

    connect(ePlayer, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(ePlayer, SIGNAL(stateChanged()), this, SLOT(onPlayerStateChanged()));
    connect(ePlayer, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
    connect(ePlayer, SIGNAL(volumeChanged(int)), this, SLOT(onPlayerVolumeChanged(int)));

    connect(&m_nextButton, SIGNAL(pressed()), ePlayer, SLOT(next()));
    connect(&m_playPauseButton, SIGNAL(pressed()), this, SLOT(onPlayPauseButtonPressed()));
    connect(&m_previousButton, SIGNAL(pressed()), ePlayer, SLOT(previous()));
    connect(&m_shuffleButton, SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));
    connect(&m_loopButton, SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(&m_volumeButton, SIGNAL(pressed()), this, SLOT(onVolumeButtonPressed()));

    connect(&m_lengthSlider, SIGNAL(sliderMoved(int)), this, SLOT(onLengthSliderMoved(int)));
    connect(&m_lengthSlider, SIGNAL(sliderValueChanged(int)), this, SLOT(onLengthSliderValueChanged(int)));
    connect(&m_volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(onVolumeSliderMoved(int)));

    connect(&m_scPlayPause, SIGNAL(pressed()), this, SLOT(onShortcutPlayPausePressed()));
    connect(&m_scNext, SIGNAL(pressed()), ePlayer, SLOT(next()));
    connect(&m_scPrevious, SIGNAL(pressed()), ePlayer, SLOT(previous()));
    connect(&m_scVolumeUp, SIGNAL(pressed()), this, SLOT(onShortcutVolumeUpPressed()));
    connect(&m_scVolumeDown, SIGNAL(pressed()), this, SLOT(onShortcutVolumeDownPressed()));
}

BarWidget::~BarWidget()
{

}

QLabel * BarWidget::coverLabel()
{
    return &m_coverLabel;
}

QLabel * BarWidget::trackLabel()
{
    return &m_trackLabel;
}

QLabel * BarWidget::currentTimeLabel()
{
    return &m_currentTimeLabel;
}

QLabel * BarWidget::totalTimeLabel()
{
    return &m_totalTimeLabel;
}

IconButton * BarWidget::playPauseButton()
{
    return &m_playPauseButton;
}

IconButton * BarWidget::nextButton()
{
    return &m_nextButton;
}

IconButton * BarWidget::previousButton()
{
    return &m_previousButton;
}

IconButton * BarWidget::shuffleButton()
{
    return &m_shuffleButton;
}

IconButton * BarWidget::loopButton()
{
    return &m_loopButton;
}

IconButton * BarWidget::volumeButton()
{
    return &m_volumeButton;
}

Slider * BarWidget::lengthSlider()
{
    return &m_lengthSlider;
}

Slider * BarWidget::volumeSlider()
{
    return &m_volumeSlider;
}

void BarWidget::onPlayerAudioChanged(Audio *audio)
{
    QPixmap cover = Cache().cover(audio, cfgBar->coverSize());

    m_coverLabel.setPixmap(cover);
    m_trackLabel.setText(QString("%1\n%2").arg(audio->title(), audio->artist()));

    m_currentTimeLabel.setText(Util::time(0));
    m_totalTimeLabel.setText(Util::time(audio->duration()));

    m_lengthSlider.setRange(0, audio->duration());
    m_lengthSlider.setEnabled(true);

    startTransition(ColorUtil::background(cover));
}

void BarWidget::onPlayerStateChanged()
{
    m_playPauseButton.setIndex(ePlayer->isPlaying() ? 1 : 0);
}

void BarWidget::onPlayerPositionChanged(int position)
{
    if (m_lengthSlider.isPressed() || m_lengthSlider.maximum() < position)
        return;

    m_currentTimeLabel.setText(Util::time(position));
    m_lengthSlider.setValue(position);
}

void BarWidget::onPlayerVolumeChanged(int volume)
{
    setVolumeConfig(volume);
    setVolumeIcon(volume);
    setVolumeSlider(volume);
}

void BarWidget::onPlayPauseButtonPressed()
{
    if (!ePlayer->currentAudio())
        return;

    if (m_playPauseButton.index() == 0)
        ePlayer->play();
    else
        ePlayer->pause();
}

void BarWidget::onShuffleButtonLocked(bool locked)
{
    ePlayer->setShuffle(locked);
    cfgPlayer->setShuffle(locked);
}

void BarWidget::onLoopButtonLocked(bool locked)
{
    ePlayer->setLoop(locked);
    cfgPlayer->setLoop(locked);
}

void BarWidget::onVolumeButtonPressed()
{
    if (m_volumeSlider.isVisible())
    {
        m_volumeSlider.setVisible(false);
        setButtonVisibility(true);
    }
    else
    {
        setButtonVisibility(false);
        m_volumeSlider.setVisible(true);
    }
}

void BarWidget::onLengthSliderMoved(int value)
{
    m_currentTimeLabel.setText(Util::time(value));
}

void BarWidget::onLengthSliderValueChanged(int value)
{
    if (value != ePlayer->currentAudio()->duration())
        ePlayer->setPosition(value);
    else
        ePlayer->next();
}

void BarWidget::onVolumeSliderMoved(int value)
{
    setVolumePlayer(value);
}

void BarWidget::onShortcutPlayPausePressed()
{
    if (ePlayer->isPlaying())
        ePlayer->pause();
    else
        ePlayer->play();
}

void BarWidget::onShortcutVolumeUpPressed()
{
    setVolumePlayer(ePlayer->volume() + 1);
}

void BarWidget::onShortcutVolumeDownPressed()
{
    setVolumePlayer(ePlayer->volume() - 1);
}

void BarWidget::setup()
{
    setColor(ColorUtil::background(Util::cover()));
    setFixedHeight(cfgBar->height());
    setStyleSheet(FileUtil::Css::bar());
}

void BarWidget::setupUi()
{
    m_coverLabel.setPixmap(Util::cover(cfgBar->coverSize()));
    m_coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_trackLabel.setFixedWidth(cfgBar->trackWidth());
    m_trackLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_currentTimeLabel.setFixedWidth(cfgBar->timeWidth());
    m_currentTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_currentTimeLabel.setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    m_totalTimeLabel.setFixedWidth(cfgBar->timeWidth());
    m_totalTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

    m_lengthSlider.setEnabled(false);
    m_lengthSlider.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setVisible(false);
    m_volumeSlider.setRange(0, 100);
    m_volumeSlider.setValue(cfgPlayer->volume());
    m_volumeSlider.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setFixedWidth(5 * cfgBar->iconSize() + 4 * cfgBar->spacing());

    m_playPauseButton.setIcons({
        IconFactory::make(ICO_PLAY),
        IconFactory::make(ICO_PAUSE)
    });
    m_previousButton.setIcons({
        IconFactory::make(ICO_PREVIOUS)
    });
    m_nextButton.setIcons({
        IconFactory::make(ICO_NEXT)
    });
    m_shuffleButton.setIcons({
        IconFactory::make(ICO_SHUFFLE)
    });
    m_loopButton.setIcons({
        IconFactory::make(ICO_LOOP)
    });
    m_volumeButton.setIcons({
        IconFactory::make(ICO_VOLUME_FULL),
        IconFactory::make(ICO_VOLUME_MEDIUM),
        IconFactory::make(ICO_VOLUME_LOW),
        IconFactory::make(ICO_VOLUME_MUTE)
    });

    m_shuffleButton.setLockable(true);
    m_loopButton.setLockable(true);

    m_playPauseButton.setSize(QSize(cfgBar->iconSize(), cfgBar->iconSize()));
    m_previousButton.setSize(QSize(cfgBar->iconSize(), cfgBar->iconSize()));
    m_nextButton.setSize(QSize(cfgBar->iconSize(), cfgBar->iconSize()));
    m_shuffleButton.setSize(QSize(cfgBar->iconSize(), cfgBar->iconSize()));
    m_loopButton.setSize(QSize(cfgBar->iconSize(), cfgBar->iconSize()));
    m_volumeButton.setSize(QSize(cfgBar->iconSize(), cfgBar->iconSize()));

    m_shuffleButton.setLocked(cfgPlayer->shuffle());
    m_loopButton.setLocked(cfgPlayer->loop());
    setVolumeIcon(cfgPlayer->volume());

    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(cfgBar->spacing());
    layout->setContentsMargins(cfgBar->margin(), cfgBar->margin(), cfgBar->margin(), cfgBar->margin());
    layout->addWidget(&m_coverLabel, 0, 0);
    layout->addWidget(&m_trackLabel, 0, 1);
    layout->addWidget(&m_currentTimeLabel, 0, 2);
    layout->addWidget(&m_lengthSlider, 0, 3);
    layout->addWidget(&m_totalTimeLabel, 0, 4);
    layout->addWidget(&m_previousButton, 0, 5);
    layout->addWidget(&m_volumeSlider, 0, 5, 1, 5, Qt::AlignRight);
    layout->addWidget(&m_playPauseButton, 0, 6);
    layout->addWidget(&m_nextButton, 0, 7);
    layout->addWidget(&m_shuffleButton, 0, 8);
    layout->addWidget(&m_loopButton, 0, 9);
    layout->addWidget(&m_volumeButton, 0, 10);
    setLayout(layout);
}

void BarWidget::setButtonVisibility(bool visible)
{
    m_previousButton.setVisible(visible);
    m_playPauseButton.setVisible(visible);
    m_nextButton.setVisible(visible);
    m_shuffleButton.setVisible(visible);
    m_loopButton.setVisible(visible);
}

void BarWidget::setVolumeConfig(int volume)
{
    cfgPlayer->setVolume(volume);
}

void BarWidget::setVolumeIcon(int volume)
{
    if (volume > 66)
        m_volumeButton.setIndex(0);
    else if (volume > 33)
        m_volumeButton.setIndex(1);
    else if (volume > 0)
        m_volumeButton.setIndex(2);
    else
        m_volumeButton.setIndex(3);
}

void BarWidget::setVolumePlayer(int volume)
{
    ePlayer->setVolume(volume);
}

void BarWidget::setVolumeSlider(int volume)
{
    m_volumeSlider.setValue(volume);
}
