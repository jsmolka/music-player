#include "libraryjson.hpp"

#include <QJsonArray>
#include <QStandardPaths>
#include <QVariant>
#include <QVector>

void cfg::LibraryJson::loadFromObject(const QJsonObject &object)
{
    setObject(object);
}

QJsonObject cfg::LibraryJson::toObject() const
{
    return object();
}

void cfg::LibraryJson::setDefaults()
{
    setDefault("cellPadding", 10);
    setDefault("itemHeight", 50);
    setDefault("paths", QJsonArray({QStandardPaths::writableLocation(QStandardPaths::MusicLocation)}));
    setDefault("scrollBarWidth", 15);
    setDefault("smoothScrolling", true);
}

void cfg::LibraryJson::setCellPadding(int padding)
{
    set("cellPadding", padding);
}

int cfg::LibraryJson::cellPadding() const
{
    return scale(get("cellPadding").toInt());
}

void cfg::LibraryJson::setItemHeight(int height)
{
    set("itemHeight", height);
}

int cfg::LibraryJson::itemHeight() const
{
    return scale(get("itemHeight").toInt());
}

void cfg::LibraryJson::setPaths(const QStrings &paths)
{
    QJsonArray array;
    for (const QString &path : paths)
        array << QJsonValue::fromVariant(path);

    set("paths", QJsonValue(array));
}

QStrings cfg::LibraryJson::paths() const
{
    QStrings paths;
    const QJsonArray values = get("paths").toArray();
    for (const QJsonValue &value : values)
        paths << value.toString();

    return paths;
}

void cfg::LibraryJson::setScrollBarWidth(int width)
{
    set("scrollBarWidth", width);
}

int cfg::LibraryJson::scrollBarWidth() const
{
    return scale(get("scrollBarWidth").toInt());
}

void cfg::LibraryJson::setSmoothScrolling(bool smooth)
{
    set("smoothScrolling", smooth);
}

bool cfg::LibraryJson::smoothScrolling() const
{
    return get("smoothScrolling").toBool();
}
