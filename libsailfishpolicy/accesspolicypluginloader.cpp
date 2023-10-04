/****************************************************************************************
** Copyright (c) 2017 - 2023 Jolla Ltd.
**
** All rights reserved.
**
** This file is part of Sailfish Policy package.
**
** You may use this file under the terms of BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
**    list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
** OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************************/

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
