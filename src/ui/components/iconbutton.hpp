#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QIcon>
#include <QPushButton>
#include <QStyle>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(bool locked READ isLocked WRITE setLocked)

public:
    IconButton(QWidget *parent = 0);

    void setIcon1(QIcon icon);
    QIcon icon1() const;

    void setIcon2(QIcon icon);
    QIcon icon2() const;

    void setSelected(bool selected);
    void setSelected(int selected);
    bool isSelected() const;

    void setLockable(bool lockable);

    void setLocked(bool locked);
    bool isLocked() const;

    void init(QIcon icon, QSize size);
    void init(QIcon icon1, QIcon icon2, QSize size);

    void switchIcon();

public slots:
    void switchLocked();

private:
    void setSelectedIcon();

    QIcon m_icon1;
    QIcon m_icon2;
    bool m_selected;
    bool m_lockable;
    bool m_locked;
};

#endif // ICONBUTTON_HPP
