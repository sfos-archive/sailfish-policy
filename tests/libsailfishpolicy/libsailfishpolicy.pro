TEMPLATE = app
TARGET = tst_accesspolicy
CONFIG += testcase
QT += testlib
QT -= gui
target.path = /opt/tests/Sailfish/MDM/

INCLUDEPATH += ../../libsailfishpolicy
LIBS += -L../../libsailfishpolicy -lsailfishpolicy

SOURCES += tst_accesspolicy.cpp
INSTALLS += target
