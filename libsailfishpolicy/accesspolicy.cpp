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

#include "accesspolicy.h"
#include "accesspolicy_p.h"

#include <QDebug>
#include <QMetaMethod>

/*!
  \class Sailfish::AccessPolicyPrivate
  \internal
*/
Sailfish::AccessPolicyPrivate::AccessPolicyPrivate(AccessPolicy *parent) : q(parent)
{
}

Sailfish::AccessPolicyPrivate::~AccessPolicyPrivate()
{
}

Sailfish::PolicyValue *Sailfish::AccessPolicyPrivate::policy(PolicyValue::PolicyType type, SignalName signalName) const
{
    if (!policies.contains(type)) {
        PolicyValue *policy = new PolicyValue(q);
        policy->setPolicyType(type);
        q->connect(policy, &PolicyValue::valueChanged, q, signalName);
        policies.insert(type, policy);
    }
    return policies.value(type);
}

/*!
  \qmltype AccessPolicy
  \inqmlmodule Sailfish.Policy
  \instantiates Sailfish::AccessPolicy
  \brief Controls the access policy for a variety of settings.
*/

/*!
  \class Sailfish::AccessPolicy
  \inmodule SailfishPolicy
  \inheaderfile accesspolicy.h
  \brief The AccessPolicy class controls the access policy for a variety of settings.

   This is useful to the MDM application if it wants to "lock" the settings
   related to some subset of system functionality, so that some specific
   configuration is maintained.

   Note that this class is merely a convenience wrapper around the
   \l PolicyValue class for specific policy types.
*/

Sailfish::AccessPolicy::AccessPolicy(QObject *parent)
    : QObject(parent)
    , d_ptr(new AccessPolicyPrivate(this))
{
}

/*!
  \internal
*/
void Sailfish::AccessPolicy::connectNotify(const QMetaMethod &signal)
{
    Q_D(AccessPolicy);
    // Make sure respective policy value has been created
    if (signal == QMetaMethod::fromSignal(&AccessPolicy::cameraEnabledChanged)) {
        d->policy(PolicyValue::CameraEnabled, &AccessPolicy::cameraEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::locationSettingsEnabledChanged)) {
        d->policy(PolicyValue::LocationSettingsEnabled, &AccessPolicy::locationSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::osUpdatesEnabledChanged)) {
        d->policy(PolicyValue::OsUpdatesEnabled, &AccessPolicy::osUpdatesEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::flightModeToggleEnabledChanged)) {
        d->policy(PolicyValue::FlightModeToggleEnabled, &AccessPolicy::flightModeToggleEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::wlanToggleEnabledChanged)) {
        d->policy(PolicyValue::WlanToggleEnabled, &AccessPolicy::wlanToggleEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::bluetoothToggleEnabledChanged)) {
        d->policy(PolicyValue::BluetoothToggleEnabled, &AccessPolicy::bluetoothToggleEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::internetSharingEnabledChanged)) {
        d->policy(PolicyValue::InternetSharingEnabled, &AccessPolicy::internetSharingEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::sideLoadingSettingsEnabledChanged)) {
        d->policy(PolicyValue::SideLoadingSettingsEnabled, &AccessPolicy::sideLoadingSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::developerModeSettingsEnabledChanged)) {
        d->policy(PolicyValue::DeveloperModeSettingsEnabled, &AccessPolicy::developerModeSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::applicationInstallationEnabledChanged)) {
        d->policy(PolicyValue::ApplicationInstallationEnabled, &AccessPolicy::applicationInstallationEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::dateTimeSettingsEnabledChanged)) {
        d->policy(PolicyValue::DateTimeSettingsEnabled, &AccessPolicy::dateTimeSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::deviceResetEnabledChanged)) {
        d->policy(PolicyValue::DeviceResetEnabled, &AccessPolicy::deviceResetEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::screenshotEnabledChanged)) {
        d->policy(PolicyValue::ScreenshotEnabled, &AccessPolicy::screenshotEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::microphoneEnabledChanged)) {
        d->policy(PolicyValue::MicrophoneEnabled, &AccessPolicy::microphoneEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::mobileNetworkSettingsEnabledChanged)) {
        d->policy(PolicyValue::MobileNetworkSettingsEnabled, &AccessPolicy::mobileNetworkSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::networkProxySettingsEnabledChanged)) {
        d->policy(PolicyValue::NetworkProxySettingsEnabled, &AccessPolicy::networkProxySettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::networkDataCounterSettingsEnabledChanged)) {
        d->policy(PolicyValue::NetworkDataCounterSettingsEnabled, &AccessPolicy::networkDataCounterSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::callStatisticsSettingsEnabledChanged)) {
        d->policy(PolicyValue::CallStatisticsSettingsEnabled, &AccessPolicy::callStatisticsSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::cellularTechnologySettingsEnabledChanged)) {
        d->policy(PolicyValue::CellularTechnologySettingsEnabled, &AccessPolicy::cellularTechnologySettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::mobileDataAccessPointSettingsEnabledChanged)) {
        d->policy(PolicyValue::MobileDataAccessPointSettingsEnabled, &AccessPolicy::mobileDataAccessPointSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::vpnConnectionSettingsEnabledChanged)) {
        d->policy(PolicyValue::VpnConnectionSettingsEnabled, &AccessPolicy::vpnConnectionSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::vpnConfigurationSettingsEnabledChanged)) {
        d->policy(PolicyValue::VpnConfigurationSettingsEnabled, &AccessPolicy::vpnConfigurationSettingsEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::browserEnabledChanged)) {
        d->policy(PolicyValue::BrowserEnabled, &AccessPolicy::browserEnabledChanged);
    } else if (signal == QMetaMethod::fromSignal(&AccessPolicy::accountCreationEnabledChanged)) {
        d->policy(PolicyValue::AccountCreationEnabled, &AccessPolicy::accountCreationEnabledChanged);
    } else {
        qWarning() << "Unhandled signal connected" << signal.methodSignature();
    }
}

Sailfish::AccessPolicy::~AccessPolicy()
{
    delete d_ptr;
    d_ptr = nullptr;
}

/*!
  \qmlproperty bool AccessPolicy::cameraEnabled
  \readonly

  \brief True if the policy allows enabling the camera.

  If the camera policy is enabled, the user is able turn the
  camera on or off. If the camera policy is disabled,
  the configuration set by the MDM application will be
  maintained.
*/
/*!
  \property AccessPolicy::cameraEnabled

  \brief True if the policy allows enabling the camera.

  If the camera policy is enabled, the user is able turn the
  camera on or off. If the camera policy is disabled,
  the configuration set by the MDM application will be
  maintained.
*/
bool Sailfish::AccessPolicy::cameraEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::CameraEnabled, &AccessPolicy::cameraEnabledChanged)->value().toBool();
}

/*!
  Sets the camera enablement policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setCameraEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::CameraEnabled, &AccessPolicy::cameraEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::flightModeToggleEnabled
  \readonly

  \brief True if the Flight Mode toggle setting is enabled.

  If the Flight Mode toggle setting is enabled, then the user is
  able to enable or disable flight mode.
  If the Flight Mode toggle setting is disabled, the user will be
  prevented from enabling or disabling flight mode,
  thus the configuration set by the MDM application will
  be maintained.

  Note that some network technologies (e.g. WLAN, Bluetooth, GPS)
  can be enabled or disabled separately, regardless of whether
  flight mode is enabled or disabled, unless their policies
  also prevent the user from changing those.
*/
/*!
  \property AccessPolicy::flightModeToggleEnabled

  \brief True if the Flight Mode toggle setting is enabled.

  If the Flight Mode toggle setting is enabled, then the user is
  able to enable or disable flight mode.
  If the Flight Mode toggle setting is disabled, the user will be
  prevented from enabling or disabling flight mode,
  thus the configuration set by the MDM application will
  be maintained.

  Note that some network technologies (e.g. WLAN, Bluetooth, GPS)
  can be enabled or disabled separately, regardless of whether
  flight mode is enabled or disabled, unless their policies
  also prevent the user from changing those.
*/
bool Sailfish::AccessPolicy::flightModeToggleEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::FlightModeToggleEnabled, &AccessPolicy::flightModeToggleEnabledChanged)->value().toBool();
}

/*!
  Sets the Flight Mode toggle setting policy to \a enabled.
  Returns true if the policy was successfully changed.

  In some jurisdictions it may be illegal to prevent the user from
  enabling flight mode, to prevent violating civil aviation laws.
  Please ensure that your application doesn't prevent the device
  or the user of the device from complying with all relevant
  laws and regulations, through its use of this API.
*/
bool Sailfish::AccessPolicy::setFlightModeToggleEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::FlightModeToggleEnabled, &AccessPolicy::flightModeToggleEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::wlanToggleEnabled
  \readonly

  \brief True if the WLAN toggle setting is enabled.

  If the WLAN toggle setting is enabled, then the user is
  able to enable or disable the WLAN network.
  If the WLAN toggle setting is disabled, the user will be
  prevented from enabling or disabling the WLAN network,
  thus the configuration set by the MDM application will
  be maintained.

  Per-network access policy is handled through ConnMan Manager
  and Service interface APIs.
*/
/*!
  \property AccessPolicy::wlanToggleEnabled

  \brief True if the WLAN toggle setting is enabled.

  If the WLAN toggle setting is enabled, then the user is
  able to enable or disable the WLAN network.
  If the WLAN toggle setting is disabled, the user will be
  prevented from enabling or disabling the WLAN network,
  thus the configuration set by the MDM application will
  be maintained.

  Per-network access policy is handled through ConnMan Manager
  and Service interface APIs.
*/
bool Sailfish::AccessPolicy::wlanToggleEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::WlanToggleEnabled, &AccessPolicy::wlanToggleEnabledChanged)->value().toBool();
}

/*!
  Sets the WLAN toggle setting policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setWlanToggleEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::WlanToggleEnabled, &AccessPolicy::wlanToggleEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::bluetoothToggleEnabled
  \readonly

  \brief True if the Bluetooth toggle setting is enabled.

  If the Bluetooth toggle setting is enabled, then the user is
  able to enable or disable the Bluetooth.
  If the Bluetooth toggle setting is disabled, the user will be
  prevented from enabling or disabling Bluetooth,
  thus the configuration set by the MDM application will
  be maintained.
*/
/*!
  \property AccessPolicy::bluetoothToggleEnabled

  \brief True if the Bluetooth toggle setting is enabled.

  If the Bluetooth toggle setting is enabled, then the user is
  able to enable or disable the Bluetooth.
  If the Bluetooth toggle setting is disabled, the user will be
  prevented from enabling or disabling Bluetooth,
  thus the configuration set by the MDM application will
  be maintained.
*/
bool Sailfish::AccessPolicy::bluetoothToggleEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::BluetoothToggleEnabled, &AccessPolicy::bluetoothToggleEnabledChanged)->value().toBool();
}

/*!
  Sets the Bluetooth toggle setting policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setBluetoothToggleEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::BluetoothToggleEnabled, &AccessPolicy::bluetoothToggleEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::internetSharingEnabled
  \readonly

  \brief True if the internet sharing setting is enabled.

  If the internet sharing setting is enabled, then the user is
  able to enable or disable mobile internet sharing (tethering).
  If the internet sharing setting is disabled, the user will be
  prevented from enabling or disabling internet sharing,
  thus the configuration set by the MDM application will
  be maintained.
*/
/*!
  \property AccessPolicy::internetSharingEnabled

  \brief True if the internet sharing setting is enabled.

  If the internet sharing setting is enabled, then the user is
  able to enable or disable mobile internet sharing (tethering).
  If the internet sharing setting is disabled, the user will be
  prevented from enabling or disabling internet sharing,
  thus the configuration set by the MDM application will
  be maintained.
*/
bool Sailfish::AccessPolicy::internetSharingEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::InternetSharingEnabled, &AccessPolicy::internetSharingEnabledChanged)->value().toBool();
}

/*!
  Sets the internet sharing setting policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setInternetSharingEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::InternetSharingEnabled, &AccessPolicy::internetSharingEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::locationSettingsEnabled
  \readonly

  \brief True if the location settings are enabled.

  If the location settings are enabled, then the user is
  able to enable or disable any positioning provider.
  If the location settings are disabled, the user will be
  prevented from enabling or disabling location providers,
  thus the configuration set by the MDM application will
  be maintained.
*/
/*!
  \property AccessPolicy::locationSettingsEnabled

  \brief True if the location settings are enabled.

  If the location settings are enabled, then the user is
  able to enable or disable any positioning provider.
  If the location settings are disabled, the user will be
  prevented from enabling or disabling location providers,
  thus the configuration set by the MDM application will
  be maintained.
*/
bool Sailfish::AccessPolicy::locationSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::LocationSettingsEnabled, &AccessPolicy::locationSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the location settings policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setLocationSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::LocationSettingsEnabled, &AccessPolicy::locationSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::osUpdatesEnabled
  \readonly

  \brief True if OS updates are enabled.

  If OS updates are enabled, the user can trigger OS updates
  via the Settings application UI. If they are disabled,
  the device will only be able to be updated by the MDM
  application.
*/
/*!
  \property AccessPolicy::osUpdatesEnabled

  \brief True if OS updates are enabled.

  If OS updates are enabled, the user can trigger OS updates
  via the Settings application UI. If they are disabled,
  the device will only be able to be updated by the MDM
  application.
*/
bool Sailfish::AccessPolicy::osUpdatesEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::OsUpdatesEnabled, &AccessPolicy::osUpdatesEnabledChanged)->value().toBool();
}

/*!
  Sets the OS updates enablement policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setOsUpdatesEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::OsUpdatesEnabled, &AccessPolicy::osUpdatesEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::sideLoadingSettingsEnabled
  \readonly

  \brief True if the side loading setting is enabled.

  If the side loading setting is enabled, then the user is
  able to allow or disallow side loading. If side loading
  setting is disabled the configuration set by the MDM application
  will be maintained. Side loading controls whether user
  is allowed to install unsecure software packages that have
  not been downloaded from the secure application store.
*/
/*!
  \property AccessPolicy::sideLoadingSettingsEnabled

  \brief True if the side loading setting is enabled.

  If the side loading setting is enabled, then the user is
  able to allow or disallow side loading. If side loading
  setting is disabled the configuration set by the MDM application
  will be maintained. Side loading controls whether user
  is allowed to install unsecure software packages that have
  not been downloaded from the secure application store.
*/

bool Sailfish::AccessPolicy::sideLoadingSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::SideLoadingSettingsEnabled, &AccessPolicy::sideLoadingSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the side loading policy to \a enabled.
  Returns true if the policy was successfully changed.
*/

bool Sailfish::AccessPolicy::setSideLoadingSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::SideLoadingSettingsEnabled, &AccessPolicy::sideLoadingSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::developerModeSettingsEnabled
  \readonly

  \brief True if the developer mode settings are enabled.

  If the developer mode settings are enabled, then the user is
  able to enable or disable developer mode, and use different
  developer mode settings. If the developer mode settings are
  disabled the configuration set by the MDM application will
  be maintained.
*/
/*!
  \property AccessPolicy::developerModeSettingsEnabled

  \brief True if the developer mode settings are enabled.

  If the developer mode settings are enabled, then the user is
  able to enable or disable developer mode, and use different
  developer mode settings. If the developer mode settings are
  disabled the configuration set by the MDM application will
  be maintained.
*/

bool Sailfish::AccessPolicy::developerModeSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::DeveloperModeSettingsEnabled, &AccessPolicy::developerModeSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the developer mode policy to \a enabled.
  Returns true if the policy was successfully changed.
*/

bool Sailfish::AccessPolicy::setDeveloperModeSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::DeveloperModeSettingsEnabled, &AccessPolicy::developerModeSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::applicationInstallationEnabled
  \readonly

  \brief True if the application installations are allowed.

  If the application installations are enabled, then the user is
  able to install applications and packages. If application
  installations are disabled, only MDM applications can install
  new applications.
*/
/*!
  \property AccessPolicy::applicationInstallationEnabled

  \brief True if the application installations are allowed.

  If the application installations are enabled, then the user is
  able to install applications and packages. If application
  installations are disabled, only MDM applications can install
  new applications.
*/

bool Sailfish::AccessPolicy::applicationInstallationEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::ApplicationInstallationEnabled, &AccessPolicy::applicationInstallationEnabledChanged)->value().toBool();
}

/*!
  Sets the application installation policy to \a enabled.
  Returns true if the policy was successfully changed.
*/

bool Sailfish::AccessPolicy::setApplicationInstallationEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::ApplicationInstallationEnabled, &AccessPolicy::applicationInstallationEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::dateTimeSettingsEnabled
  \readonly

  \brief True if the policy allows changing the system date/time settings.

  If the policy is enabled, the user is change the system date, time, time zone
  and whether these settings are automatically updated from a time server.
  If the policy is disabled, the configuration set by the MDM application will be
  maintained.
*/
/*!
  \property AccessPolicy::dateTimeSettingsEnabled

  \brief True if the policy allows changing the system date/time settings.

  If the policy is enabled, the user is change the system date, time, time zone
  and whether these settings are automatically updated from a time server.
  If the policy is disabled, the configuration set by the MDM application will be
  maintained.
*/
bool Sailfish::AccessPolicy::dateTimeSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::DateTimeSettingsEnabled, &AccessPolicy::dateTimeSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the date/time settings enablement policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setDateTimeSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::DateTimeSettingsEnabled, &AccessPolicy::dateTimeSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::deviceResetEnabled
  \readonly

  \brief True if the device reset policy is enabled.

  If the device reset is enabled, then the user is able to
  execute device factory reset, clearing all the user data
  and reverting the OS to the original factory software.
  If the device reset is disabled, only MDM application
  can initialize the reset.
*/
/*!
  \property AccessPolicy::deviceResetEnabled

  \brief True if the device reset policy is enabled.

  If the device reset is enabled, then the user is able to
  execute device factory reset, clearing all the user data
  and reverting the OS to the original factory software.
  If the device reset is disabled, only MDM application
  can initialize the reset.
*/
bool Sailfish::AccessPolicy::deviceResetEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::DeviceResetEnabled, &AccessPolicy::deviceResetEnabledChanged)->value().toBool();
}

/*!
  Sets the device reset enabled policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setDeviceResetEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::DeviceResetEnabled, &AccessPolicy::deviceResetEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::screenshotEnabled
  \readonly

  \brief True if the screenshot policy is enabled.
*/
/*!
  \property AccessPolicy::screenshotEnabled

  \brief True if the screenshot policy is enabled.
*/
bool Sailfish::AccessPolicy::screenshotEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::ScreenshotEnabled, &AccessPolicy::screenshotEnabledChanged)->value().toBool();
}

/*!
  Sets the screenshot policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setScreenshotEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::ScreenshotEnabled, &AccessPolicy::screenshotEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::microphoneEnabled
  \readonly

  \brief True if the microphone policy is enabled.
*/
/*!
  \property AccessPolicy::microphoneEnabled

  \brief True if the microphone policy is enabled.
*/
bool Sailfish::AccessPolicy::microphoneEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::MicrophoneEnabled, &AccessPolicy::microphoneEnabledChanged)->value().toBool();
}

/*!
  Sets the microphone policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setMicrophoneEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::MicrophoneEnabled, &AccessPolicy::microphoneEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::mobileNetworkSettingsEnabled
  \readonly

  \brief True if the mobile network settings are enabled.

  If the mobile network settings are enabled, then the user is
  able to change, enable or disable the mobile network.
  If the mobile network settings are disabled, the user will be
  prevented from changing, enabling or disabling the mobile network,
  thus the configuration set by the MDM application will
  be maintained.
*/
/*!
  \property AccessPolicy::mobileNetworkSettingsEnabled

  \brief True if the mobile network settings are enabled.

  If the mobile network settings are enabled, then the user is
  able to change, enable or disable the mobile network.
  If the mobile network settings are disabled, the user will be
  prevented from changing, enabling or disabling the mobile network,
  thus the configuration set by the MDM application will
  be maintained.
*/
bool Sailfish::AccessPolicy::mobileNetworkSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::MobileNetworkSettingsEnabled, &AccessPolicy::mobileNetworkSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the mobile network settings policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setMobileNetworkSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::MobileNetworkSettingsEnabled, &AccessPolicy::mobileNetworkSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::networkProxySettingsEnabled
  \readonly

  \brief True if the network proxy settings are enabled.

  If the network proxy settings are enabled, then the user is
  able to configure the proxy for each network service. If the
  network proxy settings are disabled, the user will be prevented
  from configuring the proxy for any of the network services, or
  from changing the global proxy configuration, thus the
  configuration set by the MDM application will be maintained.
*/
/*!
  \property AccessPolicy::networkProxySettingsEnabled

  \brief True if the network proxy settings are enabled.

  If the network proxy settings are enabled, then the user is
  able to configure the proxy for each network service. If the
  network proxy settings are disabled, the user will be prevented
  from configuring the proxy for any of the network services, or
  from changing the global proxy configuration, thus the
  configuration set by the MDM application will be maintained.
*/
bool Sailfish::AccessPolicy::networkProxySettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::NetworkProxySettingsEnabled, &AccessPolicy::networkProxySettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the network proxy settings policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setNetworkProxySettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::NetworkProxySettingsEnabled, &AccessPolicy::networkProxySettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::networkDataCounterSettingsEnabled
  \readonly

  \brief True if the network data counter policy is enabled.

  If the network data counter policy is enabled, then the user is
  able to reset the network data counter statistics.
*/
/*!
  \property AccessPolicy::networkDataCounterSettingsEnabled

  \brief True if the network data counter policy is enabled.

  If the network data counter policy is enabled, then the user is
  able to reset the network data counter statistics.
*/
bool Sailfish::AccessPolicy::networkDataCounterSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::NetworkDataCounterSettingsEnabled, &AccessPolicy::networkDataCounterSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the network data counter policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setNetworkDataCounterSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::NetworkDataCounterSettingsEnabled, &AccessPolicy::networkDataCounterSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::callStatisticsSettingsEnabled
  \readonly

  \brief True if the call statistics policy is enabled.

  If the call statistics policy is enabled, then the user is
  able to reset call statistic data.
*/
/*!
  \property AccessPolicy::callStatisticsSettingsEnabled

  \brief True if the call statistics policy is enabled.

  If the call statistics policy is enabled, then the user is
  able to reset call statistic data.
*/
bool Sailfish::AccessPolicy::callStatisticsSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::CallStatisticsSettingsEnabled, &AccessPolicy::callStatisticsSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the call statistics policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setCallStatisticsSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::CallStatisticsSettingsEnabled, &AccessPolicy::callStatisticsSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::cellularTechnologySettingsEnabled
  \readonly

  \brief True if the cellular technology selection settings are enabled.

  If the cellular technology selection settings are enabled, then the user is
  able to change which technology (e.g. 2G, 3G, 4G) the device may
  use to access the cellular network.

  If the cellular technology settings are disabled, the user will be
  prevented from changing the cellular technology selection,
  thus the configuration set by the MDM application will
  be maintained.
*/
/*!
  \property AccessPolicy::cellularTechnologySettingsEnabled

  \brief True if the cellular technology selection settings are enabled.

  If the cellular technology selection settings are enabled, then the user is
  able to change which technology (e.g. 2G, 3G, 4G) the device may
  use to access the cellular network.

  If the cellular technology settings are disabled, the user will be
  prevented from changing the cellular technology selection,
  thus the configuration set by the MDM application will
  be maintained.
*/
bool Sailfish::AccessPolicy::cellularTechnologySettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::CellularTechnologySettingsEnabled, &AccessPolicy::cellularTechnologySettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the cellular technology settings policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setCellularTechnologySettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::CellularTechnologySettingsEnabled, &AccessPolicy::cellularTechnologySettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::mobileDataAccessPointSettingsEnabled
  \readonly

  \brief True if the mobile data access point (APN) settings are enabled.

  If the mobile data access point settings are enabled, then the user is
  able to change the access point name, protocol, authentication method,
  username, password, message center and message proxy for various
  mobile data connection contexts (internet, mms, etc).

  If the mobile data access point settings are disabled, the user will be
  prevented from changing the settings, thus the configuration set by the
  MDM application will be maintained.
*/
/*!
  \property AccessPolicy::mobileDataAccessPointSettingsEnabled

  \brief True if the mobile data access point (APN) settings are enabled.

  If the mobile data access point settings are enabled, then the user is
  able to change the access point name, protocol, authentication method,
  username, password, message center and message proxy for various
  mobile data connection contexts (internet, mms, etc).

  If the mobile data access point settings are disabled, the user will be
  prevented from changing the settings, thus the configuration set by the
  MDM application will be maintained.
*/
bool Sailfish::AccessPolicy::mobileDataAccessPointSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::MobileDataAccessPointSettingsEnabled, &AccessPolicy::mobileDataAccessPointSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the mobile data access point settings policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setMobileDataAccessPointSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::MobileDataAccessPointSettingsEnabled, &AccessPolicy::mobileDataAccessPointSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::vpnConnectionSettingsEnabled
  \readonly

  \brief True if the VPN connection settings policy is enabled.

  If the VPN connection settings policy is enabled, then the user is
  able to activate and deactivate any individual VPN connection.

  If the VPN connection settings policy is disabled, the user will be
  prevented from turning any of the VPN connections on or off, thus
  the activation setting set by the MDM application will be maintained.

  Because modifying a connection configuration could be used to disable it,
  disabling the VPN connection settings policy will also prevent modification,
  creation or removal of VPN configurations. As such, although they can be
  set independently, the restrictions of this policy are a superset of the
  restrictions of the \l AccessPolicy::vpnConfigurationSettingsEnabled policy.
*/
/*!
  \property AccessPolicy::vpnConnectionSettingsEnabled

  \brief True if the VPN connection settings policy is enabled.

  If the VPN connection settings policy is enabled, then the user is
  able to activate and deactivate any individual VPN connection.

  If the VPN connection settings policy is disabled, the user will be
  prevented from turning any of the VPN connections on or off, thus
  the activation setting set by the MDM application will be maintained.

  Because modifying a connection configuration could be used to disable it,
  disabling the VPN connection settings policy will also prevent modification,
  creation or removal of VPN configurations. As such, although they can be
  set independently, the restrictions of this policy are a superset of the
  restrictions of the \l AccessPolicy::vpnConfigurationSettingsEnabled policy.
*/
bool Sailfish::AccessPolicy::vpnConnectionSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::VpnConnectionSettingsEnabled, &AccessPolicy::vpnConnectionSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the VPN connection status policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setVpnConnectionSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::VpnConnectionSettingsEnabled, &AccessPolicy::vpnConnectionSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::vpnConfigurationSettingsEnabled
  \readonly

  \brief True if the VPN manager settings policy is enabled.

  If the VPN manager settings policy is enabled, then the user is
  able to create, remove and modify VPN configurations.

  If the VPN manager settings policy is disabled, the user will be
  prevented from creating new, modifying or removing existing VPN
  configurations, thus the activation setting set by the MDM
  application will be maintained.

  Because modifying a connection configuration could be used to disable it,
  the restrictions of this policy are also applied by the
  \l AccessPolicy::vpnConnectionSettingsEnabled policy, although the two
  polices can be set independently.
*/
/*!
  \property AccessPolicy::vpnConfigurationSettingsEnabled

  \brief True if the VPN manager settings policy is enabled.

  If the VPN manager settings policy is enabled, then the user is
  able to create, remove and modify VPN configurations.

  If the VPN manager settings policy is disabled, the user will be
  prevented from creating new, modifying or removing existing VPN
  configurations, thus the activation setting set by the MDM
  application will be maintained.

  Because modifying a connection configuration could be used to disable it,
  the restrictions of this policy are also applied by the
  \l AccessPolicy::vpnConnectionSettingsEnabled policy, although the two
  polices can be set independently.
*/
bool Sailfish::AccessPolicy::vpnConfigurationSettingsEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::VpnConfigurationSettingsEnabled, &AccessPolicy::vpnConfigurationSettingsEnabledChanged)->value().toBool();
}

/*!
  Sets the VPN manager status policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setVpnConfigurationSettingsEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::VpnConfigurationSettingsEnabled, &AccessPolicy::vpnConfigurationSettingsEnabledChanged)->setValue(enabled);
}

/*!
  \qmlproperty bool AccessPolicy::browserEnabled
  \readonly

  \brief True if the policy allows web browsing in the browser application.

  If the browser policy is enabled, the user is able to use the browser app.
  If the browser policy is disabled, browser will display a message 
  indicating this to the user, and will not allow websites to be viewed.

  This property is considered experimental and may be changed or removed at
  a later date.
*/
/*!
  \property AccessPolicy::browserEnabled

  \brief True if the policy allows web browsing in the browser application.

  If the browser policy is enabled, the user is able to use the browser app.
  If the browser policy is disabled, browser will display a message 
  indicating this to the user, and will not allow websites to be viewed.

  This property is considered experimental and may be changed or removed at
  a later date.
*/
bool Sailfish::AccessPolicy::browserEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::BrowserEnabled, &AccessPolicy::browserEnabledChanged)->value().toBool();
}

/*!
  Sets the web browser policy to \a enabled.
  Returns true if the policy was successfully changed.
*/

bool Sailfish::AccessPolicy::setBrowserEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::BrowserEnabled, &AccessPolicy::browserEnabledChanged)->setValue(enabled);
}
/*!
  \qmlproperty bool AccessPolicy::accountCreationEnabled
  \readonly

  \brief True if the policy allows to modify accounts.

  If the account setting policy is enabled, then the user has
  access to account's menu item.
*/
/*!
  \property AccessPolicy::accountCreationEnabled

  \brief True if the policy allows to modify accounts.

  If the account setting policy is enabled, then the user has
  access to account's menu item.
*/
bool Sailfish::AccessPolicy::accountCreationEnabled() const
{
    Q_D(const AccessPolicy);
    return d->policy(PolicyValue::AccountCreationEnabled, &AccessPolicy::accountCreationEnabledChanged)->value().toBool();
}

/*!
  Sets the account setting policy to \a enabled.
  Returns true if the policy was successfully changed.
*/
bool Sailfish::AccessPolicy::setAccountCreationEnabled(bool enabled)
{
    Q_D(AccessPolicy);
    return d->policy(PolicyValue::AccountCreationEnabled, &AccessPolicy::accountCreationEnabledChanged)->setValue(enabled);
}
