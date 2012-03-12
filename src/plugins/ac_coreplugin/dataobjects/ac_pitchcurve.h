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

#ifndef AC_PITCHCURVE_H
#define AC_PITCHCURVE_H

#include <ac_curve.h>

class PitchCurvePrivate;
class AC_CORE_EXPORT PitchCurve : public Curve
        ,   public ISubEntity
{
    Q_OBJECT

public:
    enum { Type = Ac::PitchCurveItem };

    explicit PitchCurve(QObject *parent = 0);

    // Curve
    ScoreObject *scoreObject() const;

    // ISubEntity
    IEntity *parentEntity() const;

    int sceneType() const
    {
        return Ac::PitchScene;
    }

    // IModelItem
    int type() const { return Type; }

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
    Q_DECLARE_PRIVATE(PitchCurve)
};

#endif // AC_PITCHCURVE_H
