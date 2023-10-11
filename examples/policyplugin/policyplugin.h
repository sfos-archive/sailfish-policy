/****************************************************************************************
** Copyright (c) 2017 - 2023 Jolla Ltd.
**
** All rights reserved.
**
** This file is part of Sailfish Policy package.
**
** You may use this file under the terms of BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
** OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************************/


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
