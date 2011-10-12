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

#include "ac_timelabelview.h"

#include <ac_graphicsscene.h>

#include <ac_model.h>

class TimeLabelViewPrivate
{
public:
    TimeLabelView *q;

    TimeLabelViewPrivate(TimeLabelView *q)
        :   q(q)
    {}

    virtual ~TimeLabelViewPrivate()
    {}
};

TimeLabelView::TimeLabelView(QGraphicsScene *scene, QWidget *parent)
    :   LabelView(scene, parent)
    ,   d(new TimeLabelViewPrivate(this))
{}

TimeLabelView::~TimeLabelView()
{
    delete d;
}

QModelIndex TimeLabelView::gridLineListIndex() const
{
    return SceneManager::instance()->model()->timeGridLineListIndex();
}

qreal TimeLabelView::sceneWidth() const
{
    return SceneManager::instance()->model()->data(QModelIndex(), Ac::LengthRole).toReal();
}

QPointF TimeLabelView::sceneCenter() const
{
    Model *model = SceneManager::instance()->model();
    QModelIndex viewSettings = model->viewSettingsIndex();
    qreal x = viewSettings.data(Ac::TimePositionRole).toReal();
    return QPointF(x, -0.0f);
}
