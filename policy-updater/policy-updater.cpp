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

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QMetaEnum>

#include <QDBusInterface>
#include <QDBusReply>

#include <usb_moded-dbus.h>
#include <usb_moded-modes.h>

#include <ohm-ext/mdm.h>

#include "policyvalue.h"

static QString CameraDevicesFile("/usr/share/sailfish-policy/camera_devices.conf");


using namespace Sailfish;

static const QHash<PolicyValue::PolicyType, const char *> usbModes = {
    { PolicyValue::UsbMassStorageEnabled, MODE_MASS_STORAGE },
    { PolicyValue::UsbDeveloperModeEnabled, MODE_DEVELOPER },
    { PolicyValue::UsbMtpEnabled, MODE_MTP },
    { PolicyValue::UsbHostEnabled, MODE_HOST },
    { PolicyValue::UsbConnectionSharingEnabled, MODE_CONNECTION_SHARING },
    { PolicyValue::UsbDiagnosticModeEnabled, MODE_DIAG },
    { PolicyValue::UsbAdbEnabled, MODE_ADB }
};

static QStringList cameraDevices()
{
    static bool filesRead = false;
    static QStringList files;
    if (!filesRead) {
        filesRead = true;
        QFile file(CameraDevicesFile);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream textStream(&file);
            QString line;
            while (textStream.readLineInto(&line)) {
                if (!line.isEmpty() && QFileInfo::exists(line)) {
                    files << line;
                }
            }
            file.close();
        } else {
            qWarning() << "This device doesn't have camera policy file for MDM:" << CameraDevicesFile;
        }
    }
    return files;
}

static void killCameraDaemon(const QString& name)
{
    // pidof will complain if file does not exists
    if (!QFile::exists(name))
        return;

    QProcess pidof;
    pidof.setProcessChannelMode(QProcess::ForwardedErrorChannel);
    pidof.start(QLatin1String("pidof"), QStringList() << name, QIODevice::ReadOnly);
    pidof.waitForFinished();
    if (pidof.exitStatus() == QProcess::NormalExit) {
        QByteArray output = pidof.readAllStandardOutput();
        if (output.endsWith('\n')) {
            output.chop(1);
        }

        if (output.trimmed().isEmpty())
            return;

        QStringList pidsToKill = QString::fromUtf8(output).split(' ');
        pidsToKill.push_front(QLatin1String("-9"));
        QProcess::execute(QLatin1String("kill"), pidsToKill);
    }
}

static void killCameraDaemons()
{
    killCameraDaemon("/usr/libexec/droid-hybris/system/bin/minimediaservice");
    // Works for Qualcomm devices only
    killCameraDaemon("/system/bin/mm-qcamera-daemon");
}

typedef bool (*ApplyPolicy)(PolicyValue::PolicyType type, bool enabled);

static bool applyCameraPermissions(PolicyValue::PolicyType, bool enabled)
{
    QStringList files = cameraDevices();
    bool success = true;
    bool permissionsChanged = false;
    for (const QString &file : files) {
        QFile::Permissions r = QFile::permissions(file);
        QFile::Permissions oldPermissions = r;
        if (enabled) {
            r |= QFile::ReadGroup;
        } else {
            r &= ~QFile::ReadGroup;
        }
        bool didSetPermission = QFile::setPermissions(file, r);
        if (!didSetPermission) {
            success = false;
            qDebug() << "Failed to" << (enabled ? "enable" : "disable") << "camera.";
        } else if (r != oldPermissions) {
            permissionsChanged = true;
        }
    }

    if (permissionsChanged) {
        killCameraDaemons();
    }

    return success;
}

static bool applyUsbPermissions(PolicyValue::PolicyType type, bool enabled)
{
    const QString mode = QString::fromUtf8(usbModes.value(type));
    QDBusInterface moded(USB_MODE_SERVICE, USB_MODE_OBJECT, USB_MODE_INTERFACE, QDBusConnection::systemBus());
    QDBusReply<void> reply = moded.call(QStringLiteral(USB_MODE_WHITELISTED_SET), mode, enabled);
    if (!reply.isValid()) {
        qWarning() << "Failed to" << (enabled ? "enable" : "disable") << "USB mode" << mode << reply.error().name();
        return false;
    } else {
        return true;
    }
}

static bool applyMicrophonePermissions(PolicyValue::PolicyType, bool enabled)
{
    QDBusInterface moded(OHM_EXT_MDM_INTERFACE, OHM_EXT_MDM_PATH, OHM_EXT_MDM_INTERFACE, QDBusConnection::systemBus());
    QDBusReply<void> reply = moded.call(QStringLiteral(OHM_EXT_MDM_SET_METHOD),
                                        QStringLiteral("microphone"),
                                        enabled ? QStringLiteral("enabled") : QStringLiteral("disabled"));
    if (!reply.isValid()) {
        qWarning() << "Failed to" << (enabled ? "enable" : "disable") << "microphone" << reply.error().name();
        return false;
    } else {
        return true;
    }
}

static const QHash<PolicyValue::PolicyType, ApplyPolicy> policyEnforcement = {
    { PolicyValue::CameraEnabled, applyCameraPermissions },
    { PolicyValue::MicrophoneEnabled, applyMicrophonePermissions },
    { PolicyValue::UsbMassStorageEnabled, applyUsbPermissions },
    { PolicyValue::UsbDeveloperModeEnabled, applyUsbPermissions },
    { PolicyValue::UsbMtpEnabled, applyUsbPermissions },
    { PolicyValue::UsbHostEnabled, applyUsbPermissions },
    { PolicyValue::UsbConnectionSharingEnabled, applyUsbPermissions },
    { PolicyValue::UsbDiagnosticModeEnabled, applyUsbPermissions },
    { PolicyValue::UsbAdbEnabled, applyUsbPermissions }
};

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    int exitCode = EXIT_SUCCESS;

    if (argc <= 1) {
        if (!applyCameraPermissions(PolicyValue::CameraEnabled, PolicyValue::keyValue(PolicyValue::CameraEnabled).toBool())) {
            exitCode = EXIT_FAILURE;
        }

        QStringList usbWhitelist;
        for (auto it = usbModes.begin(); it != usbModes.end(); ++it) {
            if (PolicyValue::keyValue(it.key()).toBool()) {
                usbWhitelist.append(QString::fromUtf8(it.value()));
            }
        }
        QDBusInterface moded(USB_MODE_SERVICE, USB_MODE_OBJECT, USB_MODE_INTERFACE, QDBusConnection::systemBus());
        QDBusReply<void> reply = moded.call(QStringLiteral(USB_MODE_WHITELISTED_MODES_SET), usbWhitelist.join(QLatin1Char(',')));
        if (!reply.isValid()) {
            qWarning() << "Failed to update USB mode whitelist" << reply.error().name();
            exitCode = EXIT_FAILURE;
        }
    } else for (int i = 1; i < argc; ++i) {
        QString arg(argv[i]);
        QStringList keyValue = arg.split(":");
        if (keyValue.count() > 1) {
            QString key = keyValue.at(0);
            PolicyValue::PolicyType policy = static_cast<PolicyValue::PolicyType>(QMetaEnum::fromType<PolicyValue::PolicyType>().keyToValue(key.toUtf8()));
            bool ok = false;
            int value = keyValue.at(1).toInt(&ok);

            auto enforcement = policyEnforcement.find(policy);
            if (enforcement == policyEnforcement.end() || !ok || value < 0 || value > 1) {
                printf("Trying to enforce policy for unknown key.\n");
                exitCode = EXIT_FAILURE;
            } else if (!(*enforcement)(policy, value != 0)) {
                exitCode = EXIT_FAILURE;
            }
        }
    }

    return exitCode;
}
