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

class MainWidgetPrivate
{
public:
    MainWidget *q;
    QGridLayout *layout;
    ViewManager *viewManager;
    MiGraphicsView *topLeft;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
        ,   layout(new QGridLayout(q))
        ,   viewManager(new ViewManager(q))
        ,   topLeft(new MiGraphicsView)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSpacing(0);
    }

    virtual ~MainWidgetPrivate()
    {}
};

MainWidget::MainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new MainWidgetPrivate(this))
{
    int sideWidth = 48;
    int sideHeight = 32;
    int controlHeight = 192;

    d->layout->addWidget(d->topLeft, 0, 0);
    d->topLeft->setFixedSize(sideWidth, sideHeight);
    d->topLeft->setFrameShape(QFrame::NoFrame);

    QGraphicsView *timeLabelView = d->viewManager->view(Ac::TimeLabelScene);
    d->layout->addWidget(timeLabelView, 0, 1);
    timeLabelView->setFixedHeight(sideHeight);
    timeLabelView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *pitchLabelView = d->viewManager->view(Ac::PitchLabelScene);
    d->layout->addWidget(pitchLabelView, 1, 0);
    pitchLabelView->setFixedWidth(sideWidth);
    pitchLabelView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *pitchView = d->viewManager->view(Ac::PitchScene);
    d->layout->addWidget(pitchView, 1, 1);
    pitchView->setFrameShape(QFrame::Box);
    pitchView->setFrameShadow(QFrame::Sunken);
    pitchView->setLineWidth(1);

    QGraphicsView *controlLabelView = d->viewManager->view(Ac::ControlLabelScene);
    d->layout->addWidget(controlLabelView, 2, 0);
    controlLabelView->setFixedSize(sideWidth, controlHeight);
    controlLabelView->setFrameShape(QFrame::NoFrame);

    QGraphicsView *controlView = d->viewManager->view(Ac::ControlScene);
    d->layout->addWidget(controlView, 2, 1);
    controlView->setFixedHeight(controlHeight);
    controlView->setFrameShape(QFrame::Box);
    controlView->setFrameShadow(QFrame::Sunken);
}

MainWidget::~MainWidget()
{
    delete d;
}

void MainWidget::setModel(Model *model)
{
    d->viewManager->setModel(model);
}
