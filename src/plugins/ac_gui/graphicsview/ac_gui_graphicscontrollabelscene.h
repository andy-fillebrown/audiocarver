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

#ifndef AC_GUI_GRAPHICSCONTROLLABELSCENE_H
#define AC_GUI_GRAPHICSCONTROLLABELSCENE_H

#include "ac_gui_graphicsscene.h"

class GraphicsControlLabelScene : public GraphicsScene
{
public:
    GraphicsControlLabelScene(QObject *parent = 0)
        :   GraphicsScene(parent)
    {
        setSceneRect(0.0f, 0.0f, 10.0f, 1.0f);
    }
};

#endif
