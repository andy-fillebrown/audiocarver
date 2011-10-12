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

    void updateGridLineVisibilites()
    {
        Model *model = SceneManager::instance()->model();
        QModelIndex viewSettings = model->viewSettingsIndex();
        qreal padding = 5.0f / viewSettings.data(Ac::TimeScaleRole).toReal();
        QModelIndex gridLines = model->timeGridLineListIndex();
        int n = model->rowCount(gridLines);
        int minPriority = INT_MAX;
        int prevPriority = 0;
        qreal prevLocation = -1.0f;
        for (int i = 0;  i < n;  ++i) {
            QModelIndex line = model->index(i, gridLines);
            int curPriority = line.data(Ac::PriorityRole).toInt();
            if (minPriority && minPriority < curPriority)
                continue;
            qreal curLocation = line.data(Ac::LocationRole).toReal();
            if (curLocation < prevLocation)
                minPriority = qMin(prevPriority, curPriority);
            else {
                prevPriority = curPriority;
                prevLocation = curLocation + padding;
            }
        }
        for (int i = 0;  i < n;  ++i) {
            QModelIndex line = model->index(i, gridLines);
            if (line.data(Ac::PriorityRole).toInt() <= minPriority)
                model->setData(line, true, Ac::VisibilityRole);
            else
                model->setData(line, false, Ac::VisibilityRole);
        }
    }
};

TimeLabelView::TimeLabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHView(scene, parent)
    ,   d(new TimeLabelViewPrivate(this))
{}

TimeLabelView::~TimeLabelView()
{
    delete d;
}

QPointF TimeLabelView::sceneCenter() const
{
    Model *model = SceneManager::instance()->model();
    QModelIndex viewSettings = model->viewSettingsIndex();
    qreal x = viewSettings.data(Ac::TimePositionRole).toReal();
    return QPointF(x, -0.0f);
}

void TimeLabelView::scoreDataChanged()
{
    GraphicsHView::scoreDataChanged();
    d->updateGridLineVisibilites();
}
