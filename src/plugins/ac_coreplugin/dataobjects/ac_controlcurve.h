/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
**
** Contact: Andy Fillebrown (andy.fillebrown@gmail.com)
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file.  Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#ifndef AC_CONTROLCURVE_H
#define AC_CONTROLCURVE_H

#include "ac_curve.h"

class AC_CORE_EXPORT ControlCurve : public Curve
{
public:
    enum { Type = Ac::ControlCurveItem };

    explicit ControlCurve(QObject *parent = 0);

    // Properties
    int controlId() const;
    void setControlId(int controlId);

    // Curve
    ScoreObject *scoreObject() const;

    // ISubEntity
    IEntity *parentEntity() const;

    int sceneType() const
    {
        return Ac::ControlScene;
    }

    bool isCurve() const
    {
        return true;
    }

    // IModelItem
    int type() const { return Type; }

    int persistentRoleAt(int i) const
    {
//        if (staticMetaObject.propertyOffset() == i)
//            return Ac::ControlIdRole;
//        return Curve::persistentRoleAt(i);
        Q_UNUSED(i);
        return 0;
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);
};

#endif // AC_CONTROLCURVE_H
