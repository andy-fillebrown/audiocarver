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

#ifndef AC_GUI_SCORE_PLAYCURSOR_H
#define AC_GUI_SCORE_PLAYCURSOR_H

#include <ac_gui_base_playcursor.h>

class IAggregate;

namespace Score {

class PlayCursor : public Base::PlayCursor
{
public:
    PlayCursor(IAggregate *aggregate)
        :   Base::PlayCursor(aggregate)
    {}

protected:
    qreal position() const;
    void dragToPosition(qreal position);
    void setPosition(qreal position);
};

}

#endif
