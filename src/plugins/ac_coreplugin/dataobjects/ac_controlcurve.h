/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include <ac_curve.h>

class ControlCurvePrivate;
class AC_CORE_EXPORT ControlCurve : public Curve
        ,   public ISubEntity
{
    Q_OBJECT
    Q_PROPERTY(int controlId READ controlId WRITE setControlId)

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

    // IModelItem
    int type() const { return Type; }

    int persistentRoleAt(int i) const
    {
        if (staticMetaObject.propertyOffset() == i)
            return Ac::ControlIdRole;
        return Curve::persistentRoleAt(i);
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

    // IUnknown
    void *query(int type) const
    {
        switch (type) {
        case Ac::SubEntityInterface:
            return objectToInterface_cast<ISubEntity>(this);
        default:
            return Curve::query(type);
        }
    }

private:
    Q_DECLARE_PRIVATE(ControlCurve)
};

#endif // AC_CONTROLCURVE_H
