#ifndef POLICYTYPE_H
#define POLICYTYPE_H

/*!
  \namespace Sailfish::PolicyTypes
  \internal
*/

#ifdef  __cplusplus
namespace Sailfish {
namespace PolicyTypes {
#endif

enum PolicyType {
    Unknown,
    CameraEnabled,
    LocationSettingsEnabled,
    OsUpdatesEnabled,
    SideLoadingSettingsEnabled,
    DeveloperModeSettingsEnabled,
    ApplicationInstallationEnabled,
    WlanToggleEnabled,
    BluetoothToggleEnabled,
    InternetSharingEnabled,
    DeviceResetEnabled,
    ScreenshotEnabled,
    MobileNetworkSettingsEnabled,
    UsbMassStorageEnabled,
    UsbDeveloperModeEnabled,
    UsbMtpEnabled,
    UsbHostEnabled,
    UsbConnectionSharingEnabled,
    UsbDiagnosticModeEnabled,
    UsbAdbEnabled,
    DateTimeSettingsEnabled,
    MicrophoneEnabled,
    FlightModeToggleEnabled,
    NetworkProxySettingsEnabled,
    NetworkDataCounterSettingsEnabled,
    CallStatisticsSettingsEnabled,
    CellularTechnologySettingsEnabled,
    MobileDataAccessPointSettingsEnabled,
    VpnConnectionSettingsEnabled,
    VpnConfigurationSettingsEnabled,
    BrowserEnabled,
    AccountCreationEnabled
};

#ifdef  __cplusplus
}
}
#endif

#endif
