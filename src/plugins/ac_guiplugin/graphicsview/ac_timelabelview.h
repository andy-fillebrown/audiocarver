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

#ifndef AC_TIMELABELVIEW_H
#define AC_TIMELABELVIEW_H

#include <ac_labelview.h>

class TimeLabelViewPrivate;

class TimeLabelView : public LabelView
{
    Q_OBJECT

public:
    TimeLabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~TimeLabelView();

protected:
    qreal paddingScale() const { return 0.5f * sceneTransform().m11(); }
    QModelIndex gridLineListIndex() const;
    Ac::ItemDataRole scaleRole() const { return Ac::TimeScaleRole; }

    qreal sceneWidth() const;
    QPointF sceneCenter() const;

    Ac::ItemDataRole positionXRole() const { return Ac::TimePositionRole; }
    Ac::ItemDataRole scaleXRole() const { return Ac::TimeScaleRole; }

private:
    Q_DISABLE_COPY(TimeLabelView)
    TimeLabelViewPrivate *d;
};

#endif // AC_TIMELABELVIEW_H
