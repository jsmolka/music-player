#include "colorutil.hpp"

QColor ColorUtil::darker(QColor color, qreal factor)
{
    qreal r = (qreal) color.red() * (1 - factor);
    qreal g = (qreal) color.green() * (1 - factor);
    qreal b = (qreal) color.blue() * (1 - factor);

    return QColor(r, g, b);
}

QColor ColorUtil::averageColor(QImage image)
{
    quint32 red = 0;
    quint32 green = 0;
    quint32 blue = 0;

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();

    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]);

        red += pixel.red();
        green += pixel.green();
        blue += pixel.blue();
    }

    red = red / pixelCount;
    green = green / pixelCount;
    blue = blue / pixelCount;

    return QColor(red, green, blue);
}

QColor ColorUtil::dominantColor(QImage image)
{
    const quint32 RANGE = 18;
    std::array<quint32, RANGE> counts;
    std::array<quint32, RANGE> hues;
    std::array<quint32, RANGE> saturations;
    std::array<quint32, RANGE> values;

    counts.fill(0);
    hues.fill(0);
    saturations.fill(0);
    values.fill(0);

    QRgb *pixels = (QRgb *) image.bits();
    quint32 pixelCount = image.height() * image.width();

    for (quint32 i = 0; i < pixelCount; i++)
    {
        QColor pixel = QColor(pixels[i]).toHsv();
        qint32 hue = pixel.hsvHue();
        quint32 saturation = pixel.hsvSaturation();
        quint32 value = pixel.value();

        if (hue == -1)
            hue = 0;

        quint32 index = hue / (360 / RANGE);

        counts[index]++;
        hues[index] += hue;
        saturations[index] += saturation;
        values[index] += value;
    }

    quint32 index = 0;
    quint32 max = hues[0] + 2 * saturations[0];
    for (quint32 i = 1; i < RANGE; i++)
    {
        quint32 temp = hues[i] + 2 * saturations[i];
        if (temp > max)
        {
            index = i;
            max = temp;
        }
    }

    quint32 hue = hues[index] / counts[index];
    quint32 saturation = saturations[index] / counts[index];
    quint32 value = values[index] / counts[index];

    return QColor::fromHsv(hue, saturation, value);
}

QColor ColorUtil::backgroundColor(QPixmap image, quint32 width, quint32 height)
{
    return backgroundColor(image.toImage(), height, width);
}

QColor ColorUtil::backgroundColor(QImage image, quint32 width, quint32 height)
{
    QColor color = dominantColor(image.scaled(width, height));

    quint32 hue = color.hue();
    quint32 saturation = color.saturation();
    quint32 value = color.value();

    value = qMax((quint32) 20, qMin((quint32) 92, value));
    saturation = qMax((quint32) 20, qMin((quint32) 88, saturation));
    color.setHsv(hue, saturation, value);

    return darker(color.toRgb(), 0.175);
}
