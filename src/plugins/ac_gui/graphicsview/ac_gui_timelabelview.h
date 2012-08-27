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

#ifndef AC_GUI_TIMELABELVIEW_H
#define AC_GUI_TIMELABELVIEW_H

#include "ac_gui_labelview.h"
#include "ac_gui_namespace.h"

class TimeLabelViewPrivate;
class TimeLabelView : public LabelView
{
    Q_OBJECT

    TimeLabelViewPrivate *d;

public:
    TimeLabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~TimeLabelView();

protected:
    qreal paddingScale() const { return qreal(0.5f) * sceneTransform().m11(); }
    IModelItem *gridLineList() const;
    int scaleRole() const { return Ac::TimeScaleRole; }

    int sceneType() const { return Ac::TimeLabelScene; }
    qreal sceneWidth() const;
    QPointF sceneCenter() const;

    int positionRoleX() const { return Ac::TimePositionRole; }
    int scaleRoleX() const { return Ac::TimeScaleRole; }

    void zoomStarting();
};

#endif
