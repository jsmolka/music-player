#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <QSlider>

class Slider : public QSlider
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = nullptr);

    bool isPressed() const;

signals:
    void sliderValueChanged(int value);

protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void onSliderPressed();
    void onSliderReleased();

private:
    void setup();

    bool m_pressed;
};

#endif // SLIDER_HPP
