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

#ifndef AC_PITCHCURVEGRAPHICS_H
#define AC_PITCHCURVEGRAPHICS_H

#include "ac_pitchcurvedata.h"
#include "ac_isubentity.h"

#include <ac_guidefs.h>
#include <ac_guinamespace.h>
#include <ac_iparententity.h>

class AC_CORE_EXPORT PitchCurveGraphics : public PitchCurveData
{
    Q_IAGGREGATOR_DERIVED(PitchCurveGraphics, PitchCurveData)

protected:
    PitchCurveGraphics()
    {}

    // ISubEntity
    class SubEntity : public ISubEntity
    {
        Q_ISUBENTITY(Ac::IsACurve, Ac::PitchScene)
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::ISubEntity:
            return Q_NEW_AGGREGATE(SubEntity);
        default:
            return Base::createAggregate(interfaceType);
        }
    }
};

#endif // AC_PITCHCURVEGRAPHICS_H
