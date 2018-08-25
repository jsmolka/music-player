#include "colortransitionwidget.hpp"

#include <QPalette>
#include <QPropertyAnimation>

ColorTransitionWidget::ColorTransitionWidget(QWidget *parent)
    : QWidget(parent)
    , m_duration(250)
{
    setup();
}

void ColorTransitionWidget::setDuration(int duration)
{
    m_duration = duration;
}

int ColorTransitionWidget::duration() const
{
    return m_duration;
}

void ColorTransitionWidget::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}

QColor ColorTransitionWidget::color() const
{
    return palette().color(QPalette::Background);
}

void ColorTransitionWidget::colorTransition(const QColor &color)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color", this);
    animation->setDuration(m_duration);
    animation->setStartValue(this->color());
    animation->setEndValue(color);
    animation->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);
}

void ColorTransitionWidget::setup()
{
    setAutoFillBackground(true);
}
