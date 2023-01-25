/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Joona Petrell <joona.petrell@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#ifndef ACCESSPOLICYPLUGINLOADER_H
#define ACCESSPOLICYPLUGINLOADER_H

#include <QObject>

namespace Sailfish {

class AccessPolicyPlugin;

class AccessPolicyPluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit AccessPolicyPluginLoader();
    ~AccessPolicyPluginLoader();

    static AccessPolicyPluginLoader* instance();
    AccessPolicyPlugin *plugin();

private:
    AccessPolicyPlugin *m_plugin;
};
}

#endif //ACCESSPOLICYPLUGINLOADER_H
