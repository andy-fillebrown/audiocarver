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

#ifndef MI_GRAPHICSVIEW_H
#define MI_GRAPHICSVIEW_H

#include <mi_guiglobal.h>
#include <QGraphicsView>

class MI_GUI_EXPORT MiGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MiGraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0)
        :   QGraphicsView(scene, parent)
    {}

    ~MiGraphicsView()
    {}

protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // MI_GRAPHICSVIEW_H
