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

using namespace Private;

namespace Private {

class AcMainWidgetData
{
public:
    AcMainWidget *q;
    QGridLayout *layout;
    AcViewManager *viewManager;
    MiGraphicsView *topLeft;

    AcMainWidgetData(AcMainWidget *q)
        :   q(q)
        ,   layout(new QGridLayout(q))
        ,   viewManager(new AcViewManager(q))
        ,   topLeft(new MiGraphicsView)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSpacing(0);
    }
};

} // namespace Private

AcMainWidget::AcMainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new AcMainWidgetData(this))
{
    const int sideWidth = 48;
    const int sideHeight = 32;
    const int controlHeight = 192;

    d->layout->addWidget(d->topLeft, 0, 0);
    d->topLeft->setFixedSize(sideWidth, sideHeight);
    d->topLeft->setFrameShape(QFrame::NoFrame);

    QGraphicsView *timeView = d->viewManager->timeView();
    d->layout->addWidget(timeView, 0, 1);
    timeView->setFixedHeight(sideHeight);
    timeView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *pitchView = d->viewManager->pitchView();
    d->layout->addWidget(pitchView, 1, 0);
    pitchView->setFixedWidth(sideWidth);
    pitchView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *scoreView = d->viewManager->scoreView();
    d->layout->addWidget(scoreView, 1, 1);
    scoreView->setFrameShape(QFrame::Box);
    scoreView->setFrameShadow(QFrame::Sunken);
    scoreView->setLineWidth(1);

    QGraphicsView *valueView = d->viewManager->valueView();
    d->layout->addWidget(valueView, 2, 0);
    valueView->setFixedSize(sideWidth, controlHeight);
    valueView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *controlView = d->viewManager->controlView();
    d->layout->addWidget(controlView, 2, 1);
    controlView->setFixedHeight(controlHeight);
    controlView->setFrameShape(QFrame::Box);
    controlView->setFrameShadow(QFrame::Sunken);

    d->viewManager->updateViews();
}

AcMainWidget::~AcMainWidget()
{
    delete d;
}

bool AcMainWidget::isPointInControlViews(QWidget *widget, const QPoint &pos) const
{
    QGraphicsView *controlView = d->viewManager->controlView();
    if (controlView->rect().contains(controlView->mapFrom(widget, pos)))
        return true;
    QGraphicsView *valueView = d->viewManager->valueView();
    if (valueView->rect().contains(valueView->mapFrom(widget, pos)))
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
        else if (isPointInControlViews(this, event->pos()))
            d->viewManager->setValueScale(scale * d->viewManager->valueScale());
        else
            d->viewManager->setPitchScale(scale * d->viewManager->pitchScale());
    } else {
        int offset = event->delta() < 0 ? 10 : -10;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            d->viewManager->setTimePosition(d->viewManager->timePosition() - offset);
        else if (isPointInControlViews(this, event->pos()))
            d->viewManager->setValuePosition(d->viewManager->valuePosition() + offset);
        else
            d->viewManager->setPitchPosition(d->viewManager->pitchPosition() + offset);
    }
    event->accept();
}
