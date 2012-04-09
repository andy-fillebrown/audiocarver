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

class AC_CORE_EXPORT PitchCurve : public Curve
        ,   public ISubEntity
{
    Q_OBJECT

public:
    enum { ItemType = Ac::PitchCurveItem };

    explicit PitchCurve(QObject *parent = 0);

    // Curve
    ScoreObject *scoreObject() const;

    // ISubEntity
    IParentEntity *parentEntity() const;

    int sceneType() const
    {
        return Ac::PitchScene;
    }

    bool isCurve() const
    {
        return true;
    }

    // IModelItem
    int itemType() const { return ItemType; }
};

#endif // AC_PITCHCURVE_H
