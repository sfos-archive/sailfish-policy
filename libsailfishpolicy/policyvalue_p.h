/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Pekka Vuorela <pekka.vuorela@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#ifndef SAILFISH_POLICYVALUE_P_H
#define SAILFISH_POLICYVALUE_P_H

#include <QString>
#include <QFileSystemWatcher>

namespace Sailfish {

class PolicyValuePrivate
{
public:
    PolicyValuePrivate();

    QString m_key;
    QVariant m_value;
    QFileSystemWatcher m_watcher;
};
}

#endif // SAILFISH_POLICYVALUE_P_H
