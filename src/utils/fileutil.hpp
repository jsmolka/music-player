#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <QDirIterator>
#include <QTextStream>

#include "constants.hpp"
#include "config.hpp"
#include "types.hpp"

namespace FileUtil
{
    extern bool exists(const QString &file);
    extern QString fileName(const QString &file);

    extern QString read(const QString &file, const QString &defaultValue = QString());
    extern QByteArray readBytes(const QString &file, const QByteArray &defaultValue = QByteArray());

    extern void write(const QString &file, const QString &content);
    extern void write(const QString &file, const QByteArray &content);

    extern Files glob(const QString &path, const QString &filter);

    namespace Css
    {
        extern QString bar();
        extern QString egg();
        extern QString library();
    }
}

#endif // FILEUTIL_HPP
