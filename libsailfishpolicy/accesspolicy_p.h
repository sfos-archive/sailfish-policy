/****************************************************************************************
**
** Copyright (C) 2017 Jolla Ltd.
** Contact: Raine Makelainen <raine.makelainen@jolla.com>
** All rights reserved.
**
*****************************************************************************************/

#ifndef SAILFISH_ACCESSPOLICY_P_H
#define SAILFISH_ACCESSPOLICY_P_H

#include "accesspolicy.h"
#include "policyvalue.h"

namespace Sailfish {

typedef void (Sailfish::AccessPolicy::*SignalName) ();

class AccessPolicyPrivate
{
public:
    AccessPolicyPrivate(AccessPolicy *parent);
    ~AccessPolicyPrivate();

    PolicyValue *policy(PolicyValue::PolicyType type, SignalName signalName) const;

    mutable QMap<PolicyValue::PolicyType, PolicyValue*> policies;
    AccessPolicy *q;
};
}

#endif // SAILFISH_ACCESSPOLICY_P_H
