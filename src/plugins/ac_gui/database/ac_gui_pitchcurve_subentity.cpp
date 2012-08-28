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

#include "ac_gui_pitchcurve_subentity.h"
#include "ac_gui_namespace.h"

using namespace Ac;

namespace PitchCurve {

IUnknown *SubEntity::initialize()
{
    return Curve::SubEntity::initialize();
}

int SubEntity::sceneType() const
{
    return PitchScene;
}

}
