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

#ifndef SAILFISH_ACCESSPOLICY_H
#define SAILFISH_ACCESSPOLICY_H

#include <QObject>

namespace Sailfish {

class AccessPolicyPrivate;

class AccessPolicy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool cameraEnabled READ cameraEnabled NOTIFY cameraEnabledChanged)
    Q_PROPERTY(bool locationSettingsEnabled READ locationSettingsEnabled NOTIFY locationSettingsEnabledChanged)
    Q_PROPERTY(bool osUpdatesEnabled READ osUpdatesEnabled NOTIFY osUpdatesEnabledChanged)
    Q_PROPERTY(bool flightModeToggleEnabled READ flightModeToggleEnabled NOTIFY flightModeToggleEnabledChanged)
    Q_PROPERTY(bool wlanToggleEnabled READ wlanToggleEnabled NOTIFY wlanToggleEnabledChanged)
    Q_PROPERTY(bool bluetoothToggleEnabled READ bluetoothToggleEnabled NOTIFY bluetoothToggleEnabledChanged)
    Q_PROPERTY(bool internetSharingEnabled READ internetSharingEnabled NOTIFY internetSharingEnabledChanged)
    Q_PROPERTY(bool sideLoadingSettingsEnabled READ sideLoadingSettingsEnabled NOTIFY sideLoadingSettingsEnabledChanged)
    Q_PROPERTY(bool developerModeSettingsEnabled READ developerModeSettingsEnabled NOTIFY developerModeSettingsEnabledChanged)
    Q_PROPERTY(bool applicationInstallationEnabled READ applicationInstallationEnabled NOTIFY applicationInstallationEnabledChanged)
    Q_PROPERTY(bool dateTimeSettingsEnabled READ dateTimeSettingsEnabled NOTIFY dateTimeSettingsEnabledChanged)
    Q_PROPERTY(bool deviceResetEnabled READ deviceResetEnabled NOTIFY deviceResetEnabledChanged)
    Q_PROPERTY(bool screenshotEnabled READ screenshotEnabled NOTIFY screenshotEnabledChanged)
    Q_PROPERTY(bool microphoneEnabled READ microphoneEnabled NOTIFY microphoneEnabledChanged)
    Q_PROPERTY(bool mobileNetworkSettingsEnabled READ mobileNetworkSettingsEnabled NOTIFY mobileNetworkSettingsEnabledChanged)
    Q_PROPERTY(bool networkProxySettingsEnabled READ networkProxySettingsEnabled NOTIFY networkProxySettingsEnabledChanged)
    Q_PROPERTY(bool networkDataCounterSettingsEnabled READ networkDataCounterSettingsEnabled NOTIFY networkDataCounterSettingsEnabledChanged)
    Q_PROPERTY(bool callStatisticsSettingsEnabled READ callStatisticsSettingsEnabled NOTIFY callStatisticsSettingsEnabledChanged)
    Q_PROPERTY(bool cellularTechnologySettingsEnabled READ cellularTechnologySettingsEnabled NOTIFY cellularTechnologySettingsEnabledChanged)
    Q_PROPERTY(bool mobileDataAccessPointSettingsEnabled READ mobileDataAccessPointSettingsEnabled NOTIFY mobileDataAccessPointSettingsEnabledChanged)
    Q_PROPERTY(bool vpnConnectionSettingsEnabled READ vpnConnectionSettingsEnabled NOTIFY vpnConnectionSettingsEnabledChanged)
    Q_PROPERTY(bool vpnConfigurationSettingsEnabled READ vpnConfigurationSettingsEnabled NOTIFY vpnConfigurationSettingsEnabledChanged)
    Q_PROPERTY(bool browserEnabled READ browserEnabled NOTIFY browserEnabledChanged)
    Q_PROPERTY(bool accountCreationEnabled READ accountCreationEnabled NOTIFY accountCreationEnabledChanged)

public:
    AccessPolicy(QObject *parent = 0);
    ~AccessPolicy();

    bool cameraEnabled() const;
    bool setCameraEnabled(bool enabled);

    bool locationSettingsEnabled() const;
    bool setLocationSettingsEnabled(bool locked);

    bool osUpdatesEnabled() const;
    bool setOsUpdatesEnabled(bool enabled);

    bool flightModeToggleEnabled() const;
    bool setFlightModeToggleEnabled(bool locked);

    bool wlanToggleEnabled() const;
    bool setWlanToggleEnabled(bool locked);

    bool bluetoothToggleEnabled() const;
    bool setBluetoothToggleEnabled(bool locked);

    bool internetSharingEnabled() const;
    bool setInternetSharingEnabled(bool enabled);

    bool sideLoadingSettingsEnabled() const;
    bool setSideLoadingSettingsEnabled(bool enabled);

    bool developerModeSettingsEnabled() const;
    bool setDeveloperModeSettingsEnabled(bool enabled);

    bool applicationInstallationEnabled() const;
    bool setApplicationInstallationEnabled(bool enabled);

    bool dateTimeSettingsEnabled() const;
    bool setDateTimeSettingsEnabled(bool enabled);

    bool deviceResetEnabled() const;
    bool setDeviceResetEnabled(bool enabled);

    bool screenshotEnabled() const;
    bool setScreenshotEnabled(bool enabled);

    bool microphoneEnabled() const;
    bool setMicrophoneEnabled(bool enabled);

    bool mobileNetworkSettingsEnabled() const;
    bool setMobileNetworkSettingsEnabled(bool enabled);

    bool networkProxySettingsEnabled() const;
    bool setNetworkProxySettingsEnabled(bool enabled);

    bool networkDataCounterSettingsEnabled() const;
    bool setNetworkDataCounterSettingsEnabled(bool enabled);

    bool callStatisticsSettingsEnabled() const;
    bool setCallStatisticsSettingsEnabled(bool enabled);

    bool cellularTechnologySettingsEnabled() const;
    bool setCellularTechnologySettingsEnabled(bool enabled);

    bool mobileDataAccessPointSettingsEnabled() const;
    bool setMobileDataAccessPointSettingsEnabled(bool enabled);

    bool vpnConnectionSettingsEnabled() const;
    bool setVpnConnectionSettingsEnabled(bool enabled);

    bool vpnConfigurationSettingsEnabled() const;
    bool setVpnConfigurationSettingsEnabled(bool enabled);
    
    bool browserEnabled() const;
    bool setBrowserEnabled(bool enabled);

    bool accountCreationEnabled() const;
    bool setAccountCreationEnabled(bool enabled);


protected:
    void connectNotify(const QMetaMethod &signal);

signals:
    void cameraEnabledChanged();
    void locationSettingsEnabledChanged();
    void osUpdatesEnabledChanged();
    void flightModeToggleEnabledChanged();
    void wlanToggleEnabledChanged();
    void bluetoothToggleEnabledChanged();
    void internetSharingEnabledChanged();
    void sideLoadingSettingsEnabledChanged();
    void developerModeSettingsEnabledChanged();
    void applicationInstallationEnabledChanged();
    void dateTimeSettingsEnabledChanged();
    void deviceResetEnabledChanged();
    void screenshotEnabledChanged();
    void microphoneEnabledChanged();
    void mobileNetworkSettingsEnabledChanged();
    void networkProxySettingsEnabledChanged();
    void networkDataCounterSettingsEnabledChanged();
    void callStatisticsSettingsEnabledChanged();
    void cellularTechnologySettingsEnabledChanged();
    void mobileDataAccessPointSettingsEnabledChanged();
    void vpnConnectionSettingsEnabledChanged();
    void vpnConfigurationSettingsEnabledChanged();
    void browserEnabledChanged();
    void accountCreationEnabledChanged();

private:
    AccessPolicyPrivate *d_ptr;
    Q_DISABLE_COPY(AccessPolicy)
    Q_DECLARE_PRIVATE(AccessPolicy)
};
}

#endif // SAILFISH_ACCESSPOLICY_H
