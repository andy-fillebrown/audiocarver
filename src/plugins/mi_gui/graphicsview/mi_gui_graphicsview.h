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

#ifndef MI_GUI_GRAPHICSVIEW_H
#define MI_GUI_GRAPHICSVIEW_H

#include <QGraphicsView>
#include "mi_gui_global.h"

namespace Base {

class MI_GUI_EXPORT GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0)
        :   QGraphicsView(scene, parent)
    {}

    ~GraphicsView()
    {}

protected:
    void wheelEvent(QWheelEvent *event);
};

}

#endif
