TARGET = sailfishpolicyplugin
TEMPLATE = lib
CONFIG += plugin c++11

# CONFIG += link_pkgconfig
# PKGCONFIG += sailfishpolicy

INCLUDEPATH +=  ../../libsailfishpolicy
LIBS += -L../../libsailfishpolicy -lsailfishpolicy

QT -= gui

HEADERS = policyplugin.h

target.path = $$[QT_INSTALL_LIBS]/libsailfishpolicy/plugin/
INSTALLS = target
