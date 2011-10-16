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

#include <QModelIndex>

#define LABELVIEW_WIDTH 48
#define LABELVIEW_HEIGHT 24

class MainWidgetPrivate
{
public:
    MainWidget *q;
    QGridLayout *layout;
    ViewManager *viewManager;
    MiGraphicsView *topRight;
    qreal controlHeightPercentage;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
        ,   layout(new QGridLayout(q))
        ,   viewManager(new ViewManager(q))
        ,   topRight(new MiGraphicsView)
        ,   controlHeightPercentage(0.25f)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSizeConstraint(QLayout::SetNoConstraint);
        layout->setSpacing(0);
    }

    virtual ~MainWidgetPrivate()
    {}

    void updateViewHeights()
    {
        layout->setRowMinimumHeight(2, (q->height() - LABELVIEW_HEIGHT) * controlHeightPercentage);
    }
};

MainWidget::MainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new MainWidgetPrivate(this))
{
    QGraphicsView *timeLabelView = d->viewManager->view(Ac::TimeLabelScene);
    d->layout->addWidget(timeLabelView, 0, 0);
    timeLabelView->setFixedHeight(LABELVIEW_HEIGHT);

    d->layout->addWidget(d->topRight, 0, 1);
    d->topRight->setFixedSize(LABELVIEW_WIDTH, LABELVIEW_HEIGHT);
    d->topRight->setFrameShape(QFrame::HLine);

    QGraphicsView *pitchView = d->viewManager->view(Ac::PitchScene);
    d->layout->addWidget(pitchView, 1, 0);

    QGraphicsView *pitchLabelView = d->viewManager->view(Ac::PitchLabelScene);
    d->layout->addWidget(pitchLabelView, 1, 1);
    pitchLabelView->setFixedWidth(LABELVIEW_WIDTH);

    QGraphicsView *controlView = d->viewManager->view(Ac::ControlScene);
    d->layout->addWidget(controlView, 2, 0);
    controlView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);

    QGraphicsView *controlLabelView = d->viewManager->view(Ac::ControlLabelScene);
    d->layout->addWidget(controlLabelView, 2, 1);
    controlLabelView->setFixedWidth(LABELVIEW_WIDTH);
    controlLabelView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
}

MainWidget::~MainWidget()
{
    delete d;
}

void MainWidget::setModel(Model *model)
{
    d->viewManager->setModel(model);
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    d->updateViewHeights();
}

void MainWidget::showEvent(QShowEvent *)
{
    d->updateViewHeights();
}
