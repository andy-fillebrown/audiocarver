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

#include "ac_mainwidget.h"
#include <ac_viewmanager.h>
#include <mi_graphicsview.h>
#include <QApplication>
#include <QGraphicsPathItem>
#include <QGraphicsView>
#include <QLayout>
#include <QWheelEvent>

class AcMainWidgetPrivate
{
public:
    AcMainWidget *q;
    QGridLayout *layout;
    AcViewManager *viewManager;
    MiGraphicsView *topLeft;

    AcMainWidgetPrivate(AcMainWidget *q)
        :   q(q)
        ,   layout(new QGridLayout(q))
        ,   viewManager(new AcViewManager(q))
        ,   topLeft(new MiGraphicsView)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSpacing(0);
    }

    virtual ~AcMainWidgetPrivate()
    {}
};

AcMainWidget::AcMainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new AcMainWidgetPrivate(this))
{
    const int sideWidth = 48;
    const int sideHeight = 32;
    const int controlHeight = 192;

    d->layout->addWidget(d->topLeft, 0, 0);
    d->topLeft->setFixedSize(sideWidth, sideHeight);
    d->topLeft->setFrameShape(QFrame::NoFrame);

    QGraphicsView *timeLabelView = d->viewManager->timeLabelView();
    d->layout->addWidget(timeLabelView, 0, 1);
    timeLabelView->setFixedHeight(sideHeight);
    timeLabelView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *pitchLabelView = d->viewManager->pitchLabelView();
    d->layout->addWidget(pitchLabelView, 1, 0);
    pitchLabelView->setFixedWidth(sideWidth);
    pitchLabelView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *pitchView = d->viewManager->pitchView();
    d->layout->addWidget(pitchView, 1, 1);
    pitchView->setFrameShape(QFrame::Box);
    pitchView->setFrameShadow(QFrame::Sunken);
    pitchView->setLineWidth(1);

    QGraphicsView *volumeLabelView = d->viewManager->volumeLabelView();
    d->layout->addWidget(volumeLabelView, 2, 0);
    volumeLabelView->setFixedSize(sideWidth, controlHeight);
    volumeLabelView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *volumeView = d->viewManager->volumeView();
    d->layout->addWidget(volumeView, 2, 1);
    volumeView->setFixedHeight(controlHeight);
    volumeView->setFrameShape(QFrame::Box);
    volumeView->setFrameShadow(QFrame::Sunken);

    d->viewManager->updateViews();
}

AcMainWidget::~AcMainWidget()
{
    delete d;
}

bool AcMainWidget::isPointInVolumeViews(QWidget *widget, const QPoint &pos) const
{
    QGraphicsView *volumeView = d->viewManager->volumeView();
    if (volumeView->rect().contains(volumeView->mapFrom(widget, pos)))
        return true;
    QGraphicsView *volumeLabelView = d->viewManager->volumeLabelView();
    if (volumeLabelView->rect().contains(volumeLabelView->mapFrom(widget, pos)))
        return true;
    return false;
}

void AcMainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    d->viewManager->updateViews();
}

void AcMainWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    d->viewManager->updateViews();
}

void AcMainWidget::wheelEvent(QWheelEvent *event)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        qreal scale = event->delta() < 0 ? 0.8f : 1.25f;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            d->viewManager->setTimeScale(scale * d->viewManager->timeScale());
        else if (!isPointInVolumeViews(this, event->pos()))
            d->viewManager->setPitchScale(scale * d->viewManager->pitchScale());
        else
            d->viewManager->setVolumeScale(scale * d->viewManager->volumeScale());
    } else {
        int offset = event->delta() < 0 ? 100 : -100;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            d->viewManager->setTimePosition(d->viewManager->timePosition() - (offset / d->viewManager->timeScale()));
        else if (!isPointInVolumeViews(this, event->pos()))
            d->viewManager->setPitchPosition(d->viewManager->pitchPosition() + (offset / d->viewManager->pitchScale()));
        else
            d->viewManager->setVolumePosition(d->viewManager->volumePosition() + (offset / d->viewManager->volumeScale()));
    }
    event->accept();
}
