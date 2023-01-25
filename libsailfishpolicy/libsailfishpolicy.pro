TEMPLATE = lib
CONFIG += qt create_pc create_prl no_install_prl link_pkgconfig
QT -= gui
TARGET = sailfishpolicy
TARGET = $$qtLibraryTarget($$TARGET)
TARGETPATH = $$[QT_INSTALL_LIBS]

DEFINES += LIBSAILFISH_POLICY_PLUGIN_PATH=\"\\\"$$[QT_INSTALL_LIBS]/libsailfishpolicy/plugin/libsailfishpolicyplugin.so\\\"\"

SOURCES += accesspolicy.cpp \
           policyvalue.cpp \
           accesspolicypluginloader.cpp

HEADERS += accesspolicy.h \
    accesspolicy_p.h \
    policytypes.h \
    policyvalue.h \
    policyvalue_p.h \
    accesspolicyplugin.h \
    accesspolicypluginloader_p.h

PKGCONFIG += glib-2.0

develheaders.path = /usr/include/lib$$TARGET
# Include non private headers only (mark private header with _p suffix)
develheaders.files = $$system( find *.h | grep -v "_p.h" )

target.path = $$TARGETPATH

pkgconfig.files = $$TARGET.pc
pkgconfig.path = $$target.path/pkgconfig

QMAKE_PKGCONFIG_NAME = lib$$TARGET
QMAKE_PKGCONFIG_DESCRIPTION = Sailfish Device Management (MDM) policy library
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$develheaders.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_VERSION = $$VERSION

INSTALLS += target develheaders pkgconfig
