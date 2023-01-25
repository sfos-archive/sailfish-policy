#ifndef POLICYVALUE_H
#define POLICYVALUE_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <policytypes.h>

namespace Sailfish {

class PolicyValuePrivate;

class PolicyValue: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int policyType READ policyType WRITE setPolicyType NOTIFY policyTypeChanged)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QVariant value READ value NOTIFY valueChanged)

public:
    enum PolicyType {
        Unknown = PolicyTypes::Unknown,
        CameraEnabled = PolicyTypes::CameraEnabled,
        LocationSettingsEnabled = PolicyTypes::LocationSettingsEnabled,
        OsUpdatesEnabled = PolicyTypes::OsUpdatesEnabled,
        SideLoadingSettingsEnabled = PolicyTypes::SideLoadingSettingsEnabled,
        DeveloperModeSettingsEnabled = PolicyTypes::DeveloperModeSettingsEnabled,
        ApplicationInstallationEnabled = PolicyTypes::ApplicationInstallationEnabled,
        WlanToggleEnabled = PolicyTypes::WlanToggleEnabled,
        BluetoothToggleEnabled = PolicyTypes::BluetoothToggleEnabled,
        InternetSharingEnabled = PolicyTypes::InternetSharingEnabled,
        DeviceResetEnabled = PolicyTypes::DeviceResetEnabled,
        ScreenshotEnabled = PolicyTypes::ScreenshotEnabled,
        MobileNetworkSettingsEnabled = PolicyTypes::MobileNetworkSettingsEnabled,
        UsbMassStorageEnabled = PolicyTypes::UsbMassStorageEnabled,
        UsbDeveloperModeEnabled = PolicyTypes::UsbDeveloperModeEnabled,
        UsbMtpEnabled = PolicyTypes::UsbMtpEnabled,
        UsbHostEnabled = PolicyTypes::UsbHostEnabled,
        UsbConnectionSharingEnabled = PolicyTypes::UsbConnectionSharingEnabled,
        UsbDiagnosticModeEnabled = PolicyTypes::UsbDiagnosticModeEnabled,
        UsbAdbEnabled = PolicyTypes::UsbAdbEnabled,
        DateTimeSettingsEnabled = PolicyTypes::DateTimeSettingsEnabled,
        MicrophoneEnabled = PolicyTypes::MicrophoneEnabled,
        FlightModeToggleEnabled = PolicyTypes::FlightModeToggleEnabled,
        NetworkProxySettingsEnabled = PolicyTypes::NetworkProxySettingsEnabled,
        NetworkDataCounterSettingsEnabled = PolicyTypes::NetworkDataCounterSettingsEnabled,
        CallStatisticsSettingsEnabled = PolicyTypes::CallStatisticsSettingsEnabled,
        CellularTechnologySettingsEnabled = PolicyTypes::CellularTechnologySettingsEnabled,
        MobileDataAccessPointSettingsEnabled = PolicyTypes::MobileDataAccessPointSettingsEnabled,
        VpnConnectionSettingsEnabled = PolicyTypes::VpnConnectionSettingsEnabled,
        VpnConfigurationSettingsEnabled = PolicyTypes::VpnConfigurationSettingsEnabled,
        BrowserEnabled = PolicyTypes::BrowserEnabled,
        AccountCreationEnabled = PolicyTypes::AccountCreationEnabled
    };
    Q_ENUM(PolicyType)

    explicit PolicyValue(QObject *parent = 0);
    virtual ~PolicyValue();

    int policyType() const;
    void setPolicyType(int type);

    QString key() const;
    void setKey(const QString &newKey);

    QVariant value() const;

    // for MDM
    static QVariant keyValue(const QString &key);
    static QVariant keyValue(int type);
    static bool setKeyValue(const QString &key, const QVariant &value);
    static bool setKeyValue(int type, const QVariant &value);
    bool setValue(const QVariant &value);

    static bool enforcePolicy(int type, bool value);
    static bool enforcePolicy(const QString &key, bool value);

signals:
    void policyTypeChanged();
    void keyChanged();
    void valueChanged();

private slots:
    void updateValue();
    void updateValue(const QString &key);
    void updateValue(const QString &key, const QVariant &value);

private:
    PolicyValuePrivate *d;
    Q_DISABLE_COPY(PolicyValue)
    Q_DECLARE_PRIVATE(PolicyValue)
};
}

#endif // POLICYVALUE_H
