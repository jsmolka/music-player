#include "cfgbase.hpp"

#include <ShellScalingApi.h>

cfg::Base::Base()
{

}

cfg::Base::Base(const QJsonObject &object)
    : m_object(object)
{

}

QJsonObject cfg::Base::object() const
{
    return m_object;
}

void cfg::Base::set(const QString &key, const QJsonValue &value)
{
    m_object.insert(key, value);
}

QJsonValue cfg::Base::get(const QString &key) const
{
    return m_object.value(key);
}

void cfg::Base::setDefault(const QString &key, const QJsonValue &value)
{
    if (!m_object.contains(key))
         m_object.insert(key, value);
}

float cfg::Base::scale(float value) const
{
    static const float factor = static_cast<float>(GetScaleFactorForDevice(DEVICE_PRIMARY)) / 100.0f;
    return factor * value;
}

int cfg::Base::scale(int value) const
{
    return static_cast<int>(scale(static_cast<float>(value)));
}