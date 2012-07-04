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

#ifndef AC_GRAPHICS_PITCHCURVE_H
#define AC_GRAPHICS_PITCHCURVE_H

#include "ac_graphics_curve.h"

namespace Graphics {

class PitchCurve : public Curve
{
    friend class GraphicsFactory;

protected:
    PitchCurve()
    {}

    IAggregator *init();

    class SubEntity : public Curve::SubEntity
    {
        friend class PitchCurve;

    protected:
        SubEntity(Curve *aggregator)
            :   Curve::SubEntity(aggregator)
        {}

        IAggregate *init();

        // ISubEntity
        int sceneType() const
        {
            return Ac::PitchScene;
        }
    };

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::ISubEntity:
            return appendAggregate((new SubEntity(this))->init());
        default:
            return Curve::createAggregate(interfaceType);
        }
    }
};

} // namespace Graphics

#endif // AC_GRAPHICS_PITCHCURVE_H