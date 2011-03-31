/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include <QGraphicsView>

#include <mi_editor_global.h>

class MI_EDITOR_EXPORT MiGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MiGraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
protected:
    virtual ~MiGraphicsView() {}

protected:
    virtual void wheelEvent(QWheelEvent *event);

private:
    Q_DISABLE_COPY(MiGraphicsView)
};

#endif // MI_GRAPHICSVIEW_H
