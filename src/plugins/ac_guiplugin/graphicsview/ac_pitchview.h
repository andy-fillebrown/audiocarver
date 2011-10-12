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

#ifndef AC_PITCHVIEW_H
#define AC_PITCHVIEW_H

#include <ac_graphicsview.h>

class PitchViewPrivate;

class PitchView : public GraphicsHView
{
    Q_OBJECT

public:
    PitchView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~PitchView();

protected:
    qreal sceneHeight() const { return 127.0f; }
    QPointF sceneCenter() const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Q_DISABLE_COPY(PitchView)
    PitchViewPrivate *d;
};

#endif // AC_PITCHVIEW_H
