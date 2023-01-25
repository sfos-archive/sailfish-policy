/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Joona Petrell <joona.petrell@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#ifndef SAILFISH_ACCESSPOLICYPLUGIN_H
#define SAILFISH_ACCESSPOLICYPLUGIN_H

#include <QObject>

namespace Sailfish {

class AccessPolicyPlugin : public QObject
{
    Q_OBJECT
public:
    virtual ~AccessPolicyPlugin() {}
    virtual QVariant keyValue(const QString &key) = 0;
    virtual void setKeyValue(const QString &key, const QVariant &value) = 0;
signals:
    void keyValueChanged(const QString &key, const QVariant &value);
};

}

Q_DECLARE_INTERFACE(Sailfish::AccessPolicyPlugin, "org.sailfishos.AccessPolicyPlugin/1.0")

#endif // SAILFISH_ACCESSPOLICYPLUGIN_H
