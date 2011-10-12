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

#include "ac_pitchview.h"

#include <ac_graphicsscene.h>

#include <ac_model.h>

#include <QWheelEvent>

class PitchViewPrivate
{
public:
    PitchView *q;
    bool panning;
    QPointF panStartPos;
    QPointF panStartCenter;

    PitchViewPrivate(PitchView *q)
        :   q(q)
        ,   panning(false)
    {}

    virtual ~PitchViewPrivate()
    {}

    void startPan(const QPoint &pos)
    {
        panning = true;
        panStartPos = q->mapToScene(pos);
        QModelIndex viewSettings = SceneManager::instance()->model()->viewSettingsIndex();
        panStartCenter.setX(viewSettings.data(Ac::TimePositionRole).toReal());
        panStartCenter.setY(viewSettings.data(Ac::PitchPositionRole).toReal());
    }

    void panTo(const QPoint &pos)
    {
        Model *model = SceneManager::instance()->model();
        QModelIndex viewSettings = model->viewSettingsIndex();
        model->setData(viewSettings, panStartCenter.x(), Ac::TimePositionRole);
        model->setData(viewSettings, panStartCenter.y(), Ac::PitchPositionRole);
        QPointF offset = q->mapToScene(pos) - panStartPos;
        offset.setY(-offset.y());
        QPointF center = panStartCenter - offset;
        model->setData(model->viewSettingsIndex(), center.x(), Ac::TimePositionRole);
        model->setData(model->viewSettingsIndex(), center.y(), Ac::PitchPositionRole);
    }

    void endPan(const QPoint &pos)
    {
        panTo(pos);
        panning = false;
    }
};

PitchView::PitchView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHView(scene, parent)
    ,   d(new PitchViewPrivate(this))
{}

PitchView::~PitchView()
{
    delete d;
}

QPointF PitchView::sceneCenter() const
{
    Model *model = SceneManager::instance()->model();
    QModelIndex viewSettings = model->viewSettingsIndex();
    qreal x = viewSettings.data(Ac::TimePositionRole).toReal();
    qreal y = viewSettings.data(Ac::PitchPositionRole).toReal();
    return QPointF(x, -y);
}

void PitchView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
        d->startPan(event->pos());
    else
        GraphicsView::mousePressEvent(event);
}

void PitchView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->panning)
        d->panTo(event->pos());
    else
        GraphicsView::mouseMoveEvent(event);
}

void PitchView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button())
        d->endPan(event->pos());
    else
        GraphicsView::mouseReleaseEvent(event);
}

void PitchView::wheelEvent(QWheelEvent *event)
{
    Model *model = SceneManager::instance()->model();
    QModelIndex viewSettings = model->viewSettingsIndex();
    qreal timeScale = viewSettings.data(Ac::TimeScaleRole).toReal();
    qreal pitchScale = viewSettings.data(Ac::PitchScaleRole).toReal();
    qreal scaleAmount = 1.25f;
    if (event->delta() < 0)
        scaleAmount = 1.0f / scaleAmount;
    model->setData(viewSettings, scaleAmount * timeScale, Ac::TimeScaleRole);
//    model->setData(viewSettings, scaleAmount * pitchScale, Ac::PitchScaleRole);
}
