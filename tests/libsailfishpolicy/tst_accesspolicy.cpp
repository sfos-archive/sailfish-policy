#include <QtTest>
#include <QObject>

#include "accesspolicy.h"

using namespace Sailfish;

typedef bool (AccessPolicy::*GetterFunction) () const;
typedef bool (AccessPolicy::*SetterFunction) (bool);
typedef void (AccessPolicy::*SignalName) ();

class tst_accesspolicy : public QObject
{
    Q_OBJECT

public slots:
    void init();
    void cleanup();

private slots:
    void cameraEnabled();
    void locationSettingsEnabled();
    void osUpdatesEnabled();
    void flightModeToggleEnabled();
    void wlanToggleEnabled();
    void internetSharingEnabled();
    void sideLoadingSettingsEnabled();
    void developerModeSettingsEnabled();
    void applicationInstallationEnabled();
    void dateTimeSettingsEnabled();
    void deviceResetEnabled();
    void mobileNetworkSettingsEnabled();
    void networkProxySettingsEnabled();
    void networkDataCounterSettingsEnabled();
    void callStatisticsSettingsEnabled();
    void cellularTechnologySettingsEnabled();
    void mobileDataAccessPointSettingsEnabled();
    void vpnConnectionSettingsEnabled();
    void vpnConfigurationSettingsEnabled();
    void browserEnabled();
    void accountCreationEnabled();

private:
    void testPolicy(GetterFunction getterFunction, SetterFunction setterFunction, SignalName signalName);
};

void tst_accesspolicy::testPolicy(GetterFunction getterFunction, SetterFunction setterFunction, SignalName signalName)
{
    AccessPolicy policy;
    QSignalSpy spy(&policy, signalName);
    int expectedCount = 0;
    QCOMPARE(spy.count(), expectedCount);
    bool originalEnabled = (policy.*getterFunction)();

    (policy.*setterFunction)(false);
    if (originalEnabled != false) {
        expectedCount += 1;
    }
    QTRY_COMPARE(spy.count(), expectedCount);
    QCOMPARE((policy.*getterFunction)(), false);

    (policy.*setterFunction)(true);
    expectedCount += 1;
    QTRY_COMPARE(spy.count(), expectedCount);
    QCOMPARE((policy.*getterFunction)(), true);

    (policy.*setterFunction)(false);
    expectedCount += 1;
    QTRY_COMPARE(spy.count(), expectedCount);
    QCOMPARE((policy.*getterFunction)(), false);

    (policy.*setterFunction)(originalEnabled);
    QCOMPARE((policy.*getterFunction)(), originalEnabled);
}

void tst_accesspolicy::init()
{
}

void tst_accesspolicy::cleanup()
{
}

void tst_accesspolicy::cameraEnabled()
{
    testPolicy(&AccessPolicy::cameraEnabled,
                   &AccessPolicy::setCameraEnabled,
                   &AccessPolicy::cameraEnabledChanged);
}

void tst_accesspolicy::locationSettingsEnabled()
{
    testPolicy(&AccessPolicy::locationSettingsEnabled,
                   &AccessPolicy::setLocationSettingsEnabled,
                   &AccessPolicy::locationSettingsEnabledChanged);
}

void tst_accesspolicy::osUpdatesEnabled()
{
    testPolicy(&AccessPolicy::osUpdatesEnabled,
                   &AccessPolicy::setOsUpdatesEnabled,
                   &AccessPolicy::osUpdatesEnabledChanged);
}

void tst_accesspolicy::flightModeToggleEnabled()
{
    testPolicy(&AccessPolicy::flightModeToggleEnabled,
                   &AccessPolicy::setFlightModeToggleEnabled,
                   &AccessPolicy::flightModeToggleEnabledChanged);
}

void tst_accesspolicy::wlanToggleEnabled()
{
    testPolicy(&AccessPolicy::wlanToggleEnabled,
                   &AccessPolicy::setWlanToggleEnabled,
                   &AccessPolicy::wlanToggleEnabledChanged);
}

void tst_accesspolicy::internetSharingEnabled()
{
    testPolicy(&AccessPolicy::internetSharingEnabled,
                   &AccessPolicy::setInternetSharingEnabled,
                   &AccessPolicy::internetSharingEnabledChanged);
}

void tst_accesspolicy::sideLoadingSettingsEnabled()
{
    testPolicy(&AccessPolicy::sideLoadingSettingsEnabled,
                   &AccessPolicy::setSideLoadingSettingsEnabled,
                   &AccessPolicy::sideLoadingSettingsEnabledChanged);
}

void tst_accesspolicy::developerModeSettingsEnabled()
{
    testPolicy(&AccessPolicy::developerModeSettingsEnabled,
                   &AccessPolicy::setDeveloperModeSettingsEnabled,
                   &AccessPolicy::developerModeSettingsEnabledChanged);
}

void tst_accesspolicy::applicationInstallationEnabled()
{
    testPolicy(&AccessPolicy::applicationInstallationEnabled,
                   &AccessPolicy::setApplicationInstallationEnabled,
                   &AccessPolicy::applicationInstallationEnabledChanged);
}

void tst_accesspolicy::dateTimeSettingsEnabled()
{
    testPolicy(&AccessPolicy::dateTimeSettingsEnabled,
                   &AccessPolicy::setDateTimeSettingsEnabled,
                   &AccessPolicy::dateTimeSettingsEnabledChanged);
}

void tst_accesspolicy::deviceResetEnabled()
{
    testPolicy(&AccessPolicy::deviceResetEnabled,
                   &AccessPolicy::setDeviceResetEnabled,
                   &AccessPolicy::deviceResetEnabledChanged);
}

void tst_accesspolicy::mobileNetworkSettingsEnabled()
{
    testPolicy(&AccessPolicy::mobileNetworkSettingsEnabled,
                   &AccessPolicy::setMobileNetworkSettingsEnabled,
                   &AccessPolicy::mobileNetworkSettingsEnabledChanged);
}

void tst_accesspolicy::networkProxySettingsEnabled()
{
    testPolicy(&AccessPolicy::networkProxySettingsEnabled,
                   &AccessPolicy::setNetworkProxySettingsEnabled,
                   &AccessPolicy::networkProxySettingsEnabledChanged);
}

void tst_accesspolicy::networkDataCounterSettingsEnabled()
{
    testPolicy(&AccessPolicy::networkDataCounterSettingsEnabled,
                   &AccessPolicy::setNetworkDataCounterSettingsEnabled,
                   &AccessPolicy::networkDataCounterSettingsEnabledChanged);
}

void tst_accesspolicy::callStatisticsSettingsEnabled()
{
    testPolicy(&AccessPolicy::callStatisticsSettingsEnabled,
                   &AccessPolicy::setCallStatisticsSettingsEnabled,
                   &AccessPolicy::callStatisticsSettingsEnabledChanged);
}

void tst_accesspolicy::cellularTechnologySettingsEnabled()
{
    testPolicy(&AccessPolicy::cellularTechnologySettingsEnabled,
                   &AccessPolicy::setCellularTechnologySettingsEnabled,
                   &AccessPolicy::cellularTechnologySettingsEnabledChanged);
}

void tst_accesspolicy::mobileDataAccessPointSettingsEnabled()
{
    testPolicy(&AccessPolicy::mobileDataAccessPointSettingsEnabled,
                   &AccessPolicy::setMobileDataAccessPointSettingsEnabled,
                   &AccessPolicy::mobileDataAccessPointSettingsEnabledChanged);
}

void tst_accesspolicy::vpnConnectionSettingsEnabled()
{
    testPolicy(&AccessPolicy::vpnConnectionSettingsEnabled,
                   &AccessPolicy::setVpnConnectionSettingsEnabled,
                   &AccessPolicy::vpnConnectionSettingsEnabledChanged);
}

void tst_accesspolicy::vpnConfigurationSettingsEnabled()
{
    testPolicy(&AccessPolicy::vpnConfigurationSettingsEnabled,
                   &AccessPolicy::setVpnConfigurationSettingsEnabled,
                   &AccessPolicy::vpnConfigurationSettingsEnabledChanged);
}

void tst_accesspolicy::browserEnabled()
{
    testPolicy(&AccessPolicy::browserEnabled,
                   &AccessPolicy::setBrowserEnabled,
                   &AccessPolicy::browserEnabledChanged);
}

void tst_accesspolicy::accountCreationEnabled()
{
    testPolicy(&AccessPolicy::accountCreationEnabled,
                   &AccessPolicy::setAccountCreationEnabled,
                   &AccessPolicy::accountCreationEnabledChanged);
}

#include "tst_accesspolicy.moc"
QTEST_MAIN(tst_accesspolicy)
