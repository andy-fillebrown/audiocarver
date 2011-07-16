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

#ifndef AC_GRAPHICSVIEW_H
#define AC_GRAPHICSVIEW_H

#include <mi_graphicsview.h>

namespace Private {

class AcGraphicsViewData;

} // namespace Private

class AcGraphicsView : public MiGraphicsView
{
    Q_OBJECT

public:
    AcGraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcGraphicsView();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Q_DISABLE_COPY(AcGraphicsView)
    Private::AcGraphicsViewData *d;
};

#endif // AC_GRAPHICSVIEW_H
