#ifndef LIBRARYWIDGET_HPP
#define LIBRARYWIDGET_HPP

#include <QResizeEvent>

#include "audioswidget.hpp"

class LibraryWidget : public AudiosWidget
{
public:
    LibraryWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void adjustToWidth(int width);
};

#endif // LIBRARYWIDGET_HPP
