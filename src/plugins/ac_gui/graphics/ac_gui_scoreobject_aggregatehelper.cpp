/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_gui_scoreobject_aggregatehelper.h"
#include "ac_gui_graphicsnode.h"
#include "ac_gui_namespace.h"

using namespace Ac;

namespace ScoreObject {
namespace Gui {

AggregateHelper::AggregateHelper()
{
    mainNodes.insert(PitchScene, new GraphicsNode);
    mainNodes.insert(ControlScene, new GraphicsNode);
}

AggregateHelper::~AggregateHelper()
{
    delete mainNodes.value(PitchScene);
    mainNodes.insert(PitchScene, 0);
    delete mainNodes.value(ControlScene);
    mainNodes.insert(ControlScene, 0);
}

}
}
