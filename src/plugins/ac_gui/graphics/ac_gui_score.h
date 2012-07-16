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

#ifndef AC_GUI_SCORE_H
#define AC_GUI_SCORE_H

#include "ac_gui_scoreobject.h"

namespace Ac {
namespace Gui {

class Score : public ScoreObject
{
    friend class GraphicsFactory;

protected:
    Score()
    {}

    IAggregator *init();

    // IAggregator
    IAggregate *createAggregate(int interfaceType)
    {
        switch (interfaceType) {
        case I::IChildEntity:
            return 0;
        default:
            return ScoreObject::createAggregate(interfaceType);
        }
    }
};

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_SCORE_H
