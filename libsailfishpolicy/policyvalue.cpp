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

#include "policyvalue.h"
#include "policyvalue_p.h"
#include "accesspolicypluginloader_p.h"
#include "accesspolicyplugin.h"

#include <glib.h>

#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QHash>
#include <QMetaEnum>
#include <QProcess>

using namespace Sailfish;

static QString PolicyFile("/var/lib/policy/policy.conf");
static const char * const GroupName = "policy";
static const bool FlightModePolicyEnabled = QFile::exists("/var/lib/policy/enable_flight_mode_policy");

static int keyToType(const QString &key)
{
    const int value = QMetaEnum::fromType<PolicyValue::PolicyType>().keyToValue(key.toUtf8());
    return value != -1 ? value : PolicyValue::Unknown;
}

static QString typeToKey(int type)
{
    return QString::fromUtf8(QMetaEnum::fromType<PolicyValue::PolicyType>().valueToKey(type));
}

static bool hasSideEffects(const QString &key)
{
    static const int policiesWithSideEffects[] = {
        PolicyValue::CameraEnabled,
        PolicyValue::MicrophoneEnabled,
        PolicyValue::UsbMassStorageEnabled,
        PolicyValue::UsbDeveloperModeEnabled,
        PolicyValue::UsbMtpEnabled,
        PolicyValue::UsbHostEnabled,
        PolicyValue::UsbConnectionSharingEnabled,
        PolicyValue::UsbDiagnosticModeEnabled,
        PolicyValue::UsbAdbEnabled,
        0
    };

    const int policy = keyToType(key);
    for (int i = 0; policiesWithSideEffects[i] != 0; ++i) {
        if (policiesWithSideEffects[i] == policy) {
            return true;
        }
    }
    return false;
}

static bool applyPolicy(const QString &key, bool value)
{
    return QProcess::execute(QStringLiteral("/usr/libexec/policy-updater"), QStringList() << QString("%1:%2").arg(key).arg(value)) == 0;
}

/*!
  \class Sailfish::PolicyValuePrivate
  \internal
*/

PolicyValuePrivate::PolicyValuePrivate()
{
}


/*!
  \qmltype PolicyValue
  \inqmlmodule Sailfish.Policy
  \instantiates Sailfish::PolicyValue
  \brief Controls the value of a specific access policy.
*/

/*!
  \class Sailfish::PolicyValue
  \inmodule SailfishPolicy
  \inheaderfile policyvalue.h
  \brief The PolicyValue class controls the value of a specific access policy.

   This is useful to the MDM application if it wants to "lock" the settings
   related to some subset of system functionality, so that some specific
   configuration is maintained.
*/


/*!
  \enum Sailfish::PolicyValue::PolicyType

  Describes the available policy types for controlling access to various features.

  \value Unknown No policy type
  \value CameraEnabled Device camera
  \value LocationSettingsEnabled Location settings
  \value OsUpdatesEnabled System operating system update
  \value SideLoadingSettingsEnabled Side-loading of untrusted software
  \value DeveloperModeSettingsEnabled Developer mode settings
  \value ApplicationInstallationEnabled Installation of applications
  \value WlanToggleEnabled WLAN on/off
  \value InternetSharingEnabled Internet sharing (tethering)
  \value DeviceResetEnabled Reset device to factory defaults
  \value ScreenshotEnabled Take screenshots
  \value MobileNetworkSettingsEnabled Mobile network settings
  \value UsbMassStorageEnabled USB mass storage
  \value UsbDeveloperModeEnabled USB developer mode
  \value UsbMtpEnabled USB MTP
  \value UsbHostEnabled USB Host
  \value UsbConnectionSharingEnabled
  \value UsbDiagnosticModeEnabled USB diagnostic mode
  \value UsbAdbEnabled USB Android Debug Bridge (ADB)
  \value DateTimeSettingsEnabled System date and time
  \value MicrophoneEnabled System microphone
  \value FlightModeToggleEnabled Flight mode on/off
  \value NetworkProxySettingsEnabled Network proxy settings
  \value NetworkDataCounterSettingsEnabled Network data counter settings
  \value CallStatisticsSettingsEnabled Call statistics settings
  \value CellularTechnologySettingsEnabled Cellular radio technology selection settings
  \value MobileDataAccessPointSettingsEnabled Mobile data access point name (APN) settings
  \value VpnConnectionSettingsEnabled VPN connection status
  \value VpnConfigurationSettingsEnabled VPN configuration management (create/remove/modify)
  \value BrowserEnabled Web browsing
*/

/*!
  Creates a PolicyValue with the given \a parent.
*/
PolicyValue::PolicyValue(QObject *parent)
    : QObject(parent),
      d(new PolicyValuePrivate)
{
    AccessPolicyPlugin *plugin = AccessPolicyPluginLoader::instance()->plugin();

    if (plugin) {
        connect(plugin, SIGNAL(keyValueChanged(QString,QVariant)), this, SLOT(updateValue(QString,QVariant)));
    } else {
        if (QFile(PolicyFile).exists()) {
            d->m_watcher.addPath(PolicyFile);
        }
        d->m_watcher.addPath(QFileInfo(PolicyFile).path());

        connect(&d->m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(updateValue()));
        connect(&d->m_watcher, &QFileSystemWatcher::directoryChanged, this, [=]() {
            if (QFile(PolicyFile).exists()) {
                d->m_watcher.addPath(PolicyFile);
            }
            updateValue();
        });
    }
}

PolicyValue::~PolicyValue()
{
    delete d;
}

/*!
  \qmlproperty enumeration PolicyValue::policyType

  \brief The policy type which this value exposes.

  Note that there is a one-to-one mapping between a supported
  policy type and a policy key.

  The type can be one of:
  \value PolicyValue.Unknown No policy type
  \value PolicyValue.CameraEnabled Device camera
  \value PolicyValue.LocationSettingsEnabled Location settings
  \value PolicyValue.OsUpdatesEnabled System operating system update
  \value PolicyValue.SideLoadingSettingsEnabled Side-loading of untrusted software
  \value PolicyValue.DeveloperModeSettingsEnabled Developer mode settings
  \value PolicyValue.ApplicationInstallationEnabled Installation of applications
  \value PolicyValue.WlanToggleEnabled WLAN on/off
  \value PolicyValue.InternetSharingEnabled Internet sharing (tethering)
  \value PolicyValue.DeviceResetEnabled Reset device to factory defaults
  \value PolicyValue.ScreenshotEnabled Take screenshots
  \value PolicyValue.MobileNetworkSettingsEnabled Mobile network settings
  \value PolicyValue.UsbMassStorageEnabled USB mass storage
  \value PolicyValue.UsbDeveloperModeEnabled USB developer mode
  \value PolicyValue.UsbMtpEnabled USB MTP
  \value PolicyValue.UsbHostEnabled USB Host
  \value PolicyValue.UsbConnectionSharingEnabled
  \value PolicyValue.UsbDiagnosticModeEnabled USB diagnostic mode
  \value PolicyValue.UsbAdbEnabled USB Android Debug Bridge (ADB)
  \value PolicyValue.DateTimeSettingsEnabled System date and time
  \value PolicyValue.MicrophoneEnabled System microphone
  \value PolicyValue.FlightModeToggleEnabled Flight mode on/off
  \value PolicyValue.NetworkProxySettingsEnabled Network proxy settings
  \value PolicyValue.NetworkDataCounterSettingsEnabled Network data counter settings
  \value PolicyValue.CallStatisticsSettingsEnabled Call statistics settings
  \value PolicyValue.CellularTechnologySettingsEnabled Cellular radio technology selection settings
  \value PolicyValue.MobileDataAccessPointSettingsEnabled Mobile data access point name (APN) settings
  \value PolicyValue.VpnConnectionSettingsEnabled VPN connection status
  \value PolicyValue.VpnConfigurationSettingsEnabled VPN configuration management (create/remove/modify)
  \value PolicyValue.AccountCreationEnabled Account Creation allowance
  \value PolicyValue.BrowserEnabled Web browsing
*/
/*!
  \property PolicyValue::policyType

  \brief The policy type which this value exposes.

  Note that there is a one-to-one mapping between a supported
  policy type and a policy key.
*/
int PolicyValue::policyType() const
{
    return keyToType(d->m_key);
}

void PolicyValue::setPolicyType(int type)
{
    setKey(typeToKey(type));
}

/*!
  \qmlproperty string PolicyValue::key

  \brief The policy type key which this value exposes.

  Note that there is a one-to-one mapping between a supported
  policy type and a policy key.
*/
/*!
  \property PolicyValue::key

  \brief The policy type key which this value exposes.

  Note that there is a one-to-one mapping between a supported
  policy type and a policy key.
*/
QString PolicyValue::key() const
{
    return d->m_key;
}

void PolicyValue::setKey(const QString &newKey)
{
    if (d->m_key != newKey) {
        d->m_key = newKey;
        updateValue();
        emit keyChanged();
    }
}

/*!
  \qmlproperty string PolicyValue::value
  \readonly

  \brief The policy value associated with the policy type (or key).
*/
/*!
  \property PolicyValue::value

  \brief The policy value associated with the policy type (or key).
*/
QVariant PolicyValue::value() const
{
    return d->m_value;
}

/*!
  Returns the policy value associated with the specified policy \a key.
*/
QVariant PolicyValue::keyValue(const QString &key)
{
    QVariant value;

    AccessPolicyPlugin *plugin = AccessPolicyPluginLoader::instance()->plugin();
    if (plugin) {
        value = plugin->keyValue(key);
    } else {
        if (!key.isEmpty()) {
            GKeyFile *keyFile = g_key_file_new();

            g_key_file_load_from_file(keyFile, qPrintable(PolicyFile), G_KEY_FILE_NONE, NULL);

            GError *error = NULL;
            gboolean val = g_key_file_get_boolean(keyFile, GroupName, qPrintable(key), &error);
            // considering booleans as true if not found.
            // TODO: if other types or default values are needed, could include a qhash name -> info,
            // would also protect against fetching data with unknown keys
            value.setValue(val == TRUE || error != NULL);
            if (error) {
                g_error_free(error);
            }

            g_key_file_free(keyFile);
        }
    }

    return value;
}

/*!
  Returns the policy value associated with the specified policy \a type.
*/
QVariant PolicyValue::keyValue(int type)
{
    return keyValue(typeToKey(type));
}

/*!
  Sets the policy value associated with the given policy \a key to \a value.
  Returns true on success; otherwise false.
*/
bool PolicyValue::setKeyValue(const QString &key, const QVariant &value)
{
    if (!FlightModePolicyEnabled && key == QStringLiteral("FlightModeToggleEnabled")) {
        qWarning() << "Cannot set flight mode policy setting, this policy is not available!";
        return false;
    }

    if (AccessPolicyPlugin *plugin = AccessPolicyPluginLoader::instance()->plugin()) {
        plugin->setKeyValue(key, value);
    } else {
        GKeyFile *keyFile = g_key_file_new();
        GError *error = NULL;

        if (QFile(PolicyFile).exists()) {

            g_key_file_load_from_file(keyFile, qPrintable(PolicyFile), G_KEY_FILE_NONE, &error);
            if (error) {
                qWarning() << "Error loading key file" << error->code << error->message;
                g_key_file_free(keyFile);
                g_error_free(error);
                return false;
            }
        }

        g_key_file_set_boolean(keyFile, GroupName, qPrintable(key), value.toBool() ? TRUE : FALSE);
        error = NULL;
        g_key_file_save_to_file(keyFile, qPrintable(PolicyFile), &error);

        if (error) {
            qWarning() << "Error saving key file" << error->code << error->message;
            g_key_file_free(keyFile);
            g_error_free(error);
            return false;
        }
        g_key_file_free(keyFile);
    }

    return enforcePolicy(key, value.toBool());
}

/*!
  Sets the policy value associated with the given policy \a type to \a value.
  Returns true on success; otherwise false.
*/
bool PolicyValue::setKeyValue(int type, const QVariant &value)
{
    return setKeyValue(typeToKey(type), value);
}

/*!
  Sets the policy value associated with this policy to \a value.
  Returns true on success; otherwise false.
*/
bool PolicyValue::setValue(const QVariant &value)
{
    if (!key().isEmpty() && setKeyValue(key(), value)) {
        if (d->m_value != value) {
            d->m_value = value;
            emit valueChanged();
        }
        return true;
    } else {
        return false;
    }
}

/*!
  Enforces operating system level changes for the policy \a type to be \a value. Returns
  true on success; otherwise false.

  This method must be called when \l setKeyValue or
  \l setValue is not used for writing policy \a type.

*/
bool PolicyValue::enforcePolicy(int type, bool value)
{
    return enforcePolicy(typeToKey(type), value);
}

/*!
  Enforces operating system level changes for the policy \a key. Returns
  true on success; otherwise false.

  This method must to be called when \l setKeyValue or
  \l setValue is not used for writing policy \l key.
  */
bool PolicyValue::enforcePolicy(const QString &key, bool value)
{
    bool retValue = true;
    if (hasSideEffects(key)) {
        retValue = applyPolicy(key, value);
    }

    return retValue;
}

/*!
  \internal
  Refreshes the cached policy value associated with this policy's
         key (or type) by reading the value from the policy file on disk.
*/
void PolicyValue::updateValue()
{
    QVariant newVal = keyValue(d->m_key);

    if (newVal != d->m_value) {
        d->m_value = newVal;
        emit valueChanged();
    }
}

void PolicyValue::updateValue(const QString &key)
{
    if (d->m_key == key) {
        updateValue();
    }
}

void PolicyValue::updateValue(const QString &key, const QVariant &value)
{
    if (d->m_key == key && d->m_value != value) {
        d->m_value = value;
        emit valueChanged();
    }
}
