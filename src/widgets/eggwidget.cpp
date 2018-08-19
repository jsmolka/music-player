#include "eggwidget.hpp"

#include "fileutil.hpp"
#include "player.hpp"

EggWidget::EggWidget(QWidget *parent)
    : MainWindow(parent)
    , m_bar(this)
    , m_library(this)
{
    setup();
    setupUi();

    connect(&m_library, &LibraryWidget::doubleClicked, this, &EggWidget::onLibraryDoubleClicked);

    m_library.setLibrary(eLibrary);
    eLibrary->load(cfgLibrary.paths());
}

EggWidget::~EggWidget()
{

}

void EggWidget::closeEvent(QCloseEvent *event)
{
    AudioLoaderController *audioLoader = eLibrary->audioLoader();
    AudioUpdaterController *audioUpdater = eLibrary->audioUpdater();
    CoverLoaderController *coverLoader = eLibrary->coverLoader();

    audioLoader->stopWorkerThreads();
    audioUpdater->stopWorkerThreads();
    coverLoader->stopWorkerThreads();

    QWidget::closeEvent(event);
}

void EggWidget::onLibraryDoubleClicked(const QModelIndex &index)
{
    ePlayer->createPlaylist(eLibrary->audios(), index.row());
    ePlayer->play();
}

void EggWidget::setup()
{
    setupCss();
}

void EggWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_EGG));
}

void EggWidget::setupUi()
{
    QLabel *label = new QLabel(this);
    label->setFixedWidth(315);
    label->setStyleSheet("QLabel {background-color: #666666;}");

    m_library.addColumn(LibraryWidget::Title);
    m_library.addColumn(LibraryWidget::Artist);
    m_library.addColumn(LibraryWidget::Album);
    m_library.addColumn(LibraryWidget::Year, Qt::AlignLeft, false);
    m_library.addColumn(LibraryWidget::Genre);
    m_library.addColumn(LibraryWidget::Duration, Qt::AlignRight, false);

    BorderLayout *layout = new BorderLayout(0, this);
    layout->addWidget(&m_library, BorderLayout::Center);
    layout->addWidget(label, BorderLayout::West);
    layout->addWidget(&m_bar, BorderLayout::South);
    setLayout(layout);
}
