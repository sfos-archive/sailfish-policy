TARGET = policy-updater
CONFIG += c++11

CONFIG += link_pkgconfig

INCLUDEPATH += $$PWD/../libsailfishpolicy

LIBS += -L../libsailfishpolicy -lsailfishpolicy

QT = core dbus

PKGCONFIG += \
    ohm-ext-mdm \
    usb_moded

SOURCES += policy-updater.cpp

systemd.files = policies-setup.service
systemd.path = /usr/lib/systemd/system

target.path = /usr/libexec

INSTALLS += target systemd
