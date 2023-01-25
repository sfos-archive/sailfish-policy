/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Joona Petrell <joona.petrell@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#ifndef POLICYPLUGIN_H
#define POLICYPLUGIN_H

#include <qobject.h>
#include <accesspolicyplugin.h>
#include <QDebug>
#include <QTimer>

class PolicyPlugin : public Sailfish::AccessPolicyPlugin
{
    Q_OBJECT
    Q_INTERFACES(Sailfish::AccessPolicyPlugin)
    Q_PLUGIN_METADATA(IID "org.sailfishos.AccessPolicyPlugin/1.0")
public:
    PolicyPlugin() : m_sideLoadingSettingsEnabled(true)
    {
        QTimer::singleShot(5000, this, SLOT(toggleSideLoadingPolicy()));
    }

    ~PolicyPlugin() {}

    void setKeyValue(const QString &key, const QVariant &value) {
        Q_UNUSED(key)
        Q_UNUSED(value)
        qWarning() << "setKeyValue not implemented";
    }

    QVariant keyValue(const QString &key)
    {
        qDebug() << Q_FUNC_INFO << "key" << key;

        if (key == QLatin1String("CameraEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("LocationSettingsEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("OsUpdatesEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("SideLoadingSettingsEnabled")) {
            return QVariant::fromValue<bool>(m_sideLoadingSettingsEnabled);
        } else if (key == QLatin1String("DeveloperModeSettingsEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("ApplicationInstallationEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("DateTimeSettingsEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("FlightModeToggleEnabled")) {
            return QVariant::fromValue<bool>(true);
        } else if (key == QLatin1String("WlanToggleEnabled")) {
            return QVariant::fromValue<bool>(true);
        }

        return QVariant::fromValue<bool>(true);
    }

protected slots:
    void toggleSideLoadingPolicy()
    {
        m_sideLoadingSettingsEnabled = !m_sideLoadingSettingsEnabled;
        emit keyValueChanged("SideLoadingSettingsEnabled", m_sideLoadingSettingsEnabled);
        QTimer::singleShot(5000, this, SLOT(toggleSideLoadingPolicy()));
    }
private:
    bool m_sideLoadingSettingsEnabled;
};

#endif // POLICYPLUGIN_H
