/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Raine Makelainen <raine.makelainen@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#include <QQmlExtensionPlugin>
#include <QQmlEngine>
#include <qqml.h>

// classes exposed to QML
#include "accesspolicy.h"
#include "policyvalue.h"

using namespace Sailfish;

template <typename T> static QObject *singletonApiCallback(QQmlEngine *engine, QJSEngine *)
{
    return new T(engine);
}

class SailfishPolicyPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Sailfish.Policy" )

public:
    virtual void registerTypes(const char *uri)
    {
        if (QLatin1String(uri) == QLatin1String("Sailfish.Policy")) {
            qmlRegisterSingletonType<AccessPolicy>(uri, 1, 0, "AccessPolicy", singletonApiCallback<AccessPolicy>);
            qmlRegisterType<PolicyValue>(uri, 1, 0, "PolicyValue");
        }
    }
};

#include "plugin.moc"



