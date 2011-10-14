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

#include <ac_viewmanager.h>

#include <ac_model.h>

#include <QWheelEvent>

class PitchViewPrivate
{
public:
    PitchView *q;
    bool panning;
    QPoint panStartPos;
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
        panStartPos = pos;
        ViewManager *vm = ViewManager::instance();
        panStartCenter.setX(vm->position(Ac::TimePositionRole));
        panStartCenter.setY(vm->position(Ac::PitchPositionRole));
    }

    void panTo(const QPoint &pos)
    {
        ViewManager *vm = ViewManager::instance();
        QPointF offset = q->sceneScale().inverted().map(QPointF(pos - panStartPos));
        QPointF center = panStartCenter - offset;
        vm->setPosition(center.x(), Ac::TimePositionRole);
        vm->setPosition(center.y(), Ac::PitchPositionRole);
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

qreal PitchView::sceneHeight() const
{
    return 127.0f / ViewManager::instance()->scale(Ac::PitchScaleRole);
}

QPointF PitchView::sceneCenter() const
{
    ViewManager *vm = ViewManager::instance();
    return QPointF(vm->position(Ac::TimePositionRole), -vm->position(Ac::PitchPositionRole));
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
    if (d->panning) {
        d->panTo(event->pos());
        emit ViewManager::instance()->viewSettingsChanged();
    }
    else
        GraphicsView::mouseMoveEvent(event);
}

void PitchView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::RightButton == event->button()) {
        d->endPan(event->pos());
        ViewManager *vm = ViewManager::instance();
        emit vm->viewSettingsChanged();
        vm->updateViewSettings();
    }
    else
        GraphicsView::mouseReleaseEvent(event);
}

void PitchView::wheelEvent(QWheelEvent *event)
{
    if (d->panning)
        return;
    ViewManager *vm = ViewManager::instance();
    qreal timeScale = vm->scale(Ac::TimeScaleRole);
    qreal pitchScale = vm->scale(Ac::PitchScaleRole);
    qreal scaleAmount = 1.25f;
    if (event->delta() < 0)
        scaleAmount = 1.0f / scaleAmount;
    vm->setScale(scaleAmount * timeScale, Ac::TimeScaleRole);
    vm->setScale(scaleAmount * pitchScale, Ac::PitchScaleRole);
    emit vm->viewSettingsChanged();
}
