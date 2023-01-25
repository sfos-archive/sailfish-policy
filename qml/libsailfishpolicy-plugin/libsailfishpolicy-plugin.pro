MODULENAME = Sailfish/Policy
DEFINES *= MODULENAME=\"\\\"\"$${MODULENAME}\"\\\"\"
TEMPLATE = lib
TARGET  = sailfishpolicyplugin
TARGET = $$qtLibraryTarget($$TARGET)
TARGETPATH = $$[QT_INSTALL_QML]/$$MODULENAME

QT += qml dbus
CONFIG += \
    plugin \
    link_pkgconfig \
    hide_symbols \
    c++11

MDM_POLICY_LIB_PATH = ../../libsailfishpolicy

LIBS += -L$$MDM_POLICY_LIB_PATH -lsailfishpolicy
INCLUDEPATH += $$MDM_POLICY_LIB_PATH
SOURCES += plugin.cpp

import.files = *.qml *.js qmldir plugins.qmltypes
import.path = $$TARGETPATH
target.path = $$TARGETPATH
INSTALLS += target import

QMAKE_CXXFLAGS += -Wparentheses -Werror -Wfatal-errors
OTHER_FILES += qmldir *.qml *.js

qmltypes.commands = qmlplugindump -nonrelocatable Sailfish.Policy 1.0 > $$PWD/plugins.qmltypes
QMAKE_EXTRA_TARGETS += qmltypes
