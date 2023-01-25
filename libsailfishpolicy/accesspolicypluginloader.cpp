/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Joona Petrell <joona.petrell@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#include "accesspolicypluginloader_p.h"
#include "accesspolicyplugin.h"
#include <QPluginLoader>
#include <QDebug>
#include <QFile>

using namespace Sailfish;

static const QString pluginPath = LIBSAILFISH_POLICY_PLUGIN_PATH;
static AccessPolicyPluginLoader *m_pluginLoader = 0;

/*!
  \class AccessPolicyPluginLoader
  \internal
*/
AccessPolicyPluginLoader::AccessPolicyPluginLoader() : m_plugin(0)
{
    if (!QFile(pluginPath).exists()) {
        return;
    }

    QScopedPointer<QPluginLoader> loader(new QPluginLoader(pluginPath));

    if (!loader->load()) {
        qWarning() << "Failed to load plugin" << pluginPath << loader->errorString();
    }
    if (AccessPolicyPlugin *plugin = qobject_cast<AccessPolicyPlugin *>(loader->instance())) {
        m_plugin = plugin;
    } else {
        loader->unload();
    }
}

AccessPolicyPluginLoader::~AccessPolicyPluginLoader()
{
    delete m_plugin;
}

AccessPolicyPluginLoader* AccessPolicyPluginLoader::AccessPolicyPluginLoader::instance()
{
    if (!m_pluginLoader) {
        m_pluginLoader = new AccessPolicyPluginLoader();
    }

    return m_pluginLoader;
}

AccessPolicyPlugin *AccessPolicyPluginLoader::plugin()
{
    return m_plugin;
}
