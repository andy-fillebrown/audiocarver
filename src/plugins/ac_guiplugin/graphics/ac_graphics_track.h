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

#ifndef AC_GRAPHICS_TRACK_H
#define AC_GRAPHICS_TRACK_H

#include "ac_graphics_scoreobject.h"

namespace Graphics {

class Track : public ScoreObject
{
    friend class GraphicsFactory;

protected:
    Track()
    {}

    IAggregator *init();

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        return Track::createAggregate(interfaceType);
    }
};

} // namespace Graphics

#endif // AC_GRAPHICS_TRACK_H
