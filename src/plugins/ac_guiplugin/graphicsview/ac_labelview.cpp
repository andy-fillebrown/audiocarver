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

#include "ac_labelview.h"

#include <ac_viewmanager.h>

#include <ac_model.h>

class LabelViewPrivate
{
public:
    LabelView *q;

    LabelViewPrivate(LabelView *q)
        :   q(q)
    {}

    virtual ~LabelViewPrivate()
    {}

    void updateGridLineVisibilites()
    {
        qreal padding = 50.0f / q->paddingScale();
        QModelIndex gridLines = q->gridLineListIndex();
        Model *model = ViewManager::instance()->model();
        int n = model->rowCount(gridLines);
        int minPriority = INT_MAX;
        int prevPriority = 0;
        qreal prevLocation = -1.0f;
        for (int i = 0;  i < n;  ++i) {
            QModelIndex line = model->index(i, gridLines);
            int curPriority = line.data(Ac::PriorityRole).toInt();
            if (minPriority && (minPriority < curPriority))
                continue;
            qreal curLocation = line.data(Ac::LocationRole).toReal();
            if (curLocation < prevLocation)
                minPriority = qMin(minPriority, qMax(prevPriority, curPriority));
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

LabelView::LabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsView(scene, parent)
    ,   d(new LabelViewPrivate(this))
{
    setBackgroundRole(QPalette::Window);
}

LabelView::~LabelView()
{
    delete d;
}

void LabelView::viewScaleChanged(int role)
{
    if (scaleRole() == role)
        d->updateGridLineVisibilites();
}

void LabelView::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    Q_UNUSED(bottomLeft);
    QModelIndex index = gridLineListIndex();
    if (topRight == gridLineListIndex())
        d->updateGridLineVisibilites();
}

void LabelView::resizeEvent(QResizeEvent *event)
{
    GraphicsView::resizeEvent(event);
    d->updateGridLineVisibilites();
}

QPointF LabelVView::sceneCenter() const
{
    return QPointF(0.5f, -ViewManager::instance()->position(positionYRole()));
}
