#ifndef EGGWIDGET_HPP
#define EGGWIDGET_HPP

#include <QMimeData>

#include "core/shortcutprocessor.hpp"
#include "widgets/barwidget.hpp"
#include "widgets/librarywidget.hpp"
#include "widgets/mainwindow.hpp"

class EggWidget : public MainWindow
{
    Q_OBJECT    

public:
    explicit EggWidget(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void onLibraryDoubleClicked(const QModelIndex &index) const;

private:
    void init();
    void initUi();
    void initStyle();

    BarWidget m_bar;
    LibraryWidget m_library;
    ShortcutProcessor m_shortcuts;
};

#endif // EGGWIDGET_HPP
