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
    QCursor prevCursor;
    bool cursorPushed;
    bool draggingSeparator;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
        ,   layout(new QGridLayout(q))
        ,   viewManager(new ViewManager(q))
        ,   topRight(new MiGraphicsView)
        ,   controlHeightPercentage(0.25f)
        ,   cursorPushed(false)
        ,   draggingSeparator(false)
    {
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSizeConstraint(QLayout::SetNoConstraint);
        layout->setSpacing(0);
    }

    virtual ~MainWidgetPrivate()
    {}

    int controlViewHeight() const
    {
        return (q->height() - LABELVIEW_HEIGHT) * controlHeightPercentage;
    }

    int pitchViewHeight() const
    {
        return q->height() - LABELVIEW_HEIGHT - controlViewHeight();
    }

    void updateViewHeights()
    {
        layout->itemAt(0)->setGeometry(QRect(0, 0, q->width() - LABELVIEW_WIDTH, LABELVIEW_HEIGHT));
        layout->itemAt(1)->setGeometry(QRect(q->width() - LABELVIEW_WIDTH, 0, LABELVIEW_WIDTH, LABELVIEW_HEIGHT));
        layout->itemAt(2)->setGeometry(QRect(0, LABELVIEW_HEIGHT, q->width() - LABELVIEW_WIDTH, pitchViewHeight()));
        layout->itemAt(3)->setGeometry(QRect(q->width() - LABELVIEW_WIDTH, LABELVIEW_HEIGHT, LABELVIEW_WIDTH, pitchViewHeight()));
        layout->itemAt(4)->setGeometry(QRect(0, q->height() - controlViewHeight(), q->width() - LABELVIEW_WIDTH, controlViewHeight()));
        layout->itemAt(5)->setGeometry(QRect(q->width() - LABELVIEW_WIDTH, q->height() - controlViewHeight(), LABELVIEW_WIDTH, controlViewHeight()));
    }

    bool posIsOverControlSeparator(const QPoint &pos) const
    {
        return q->height() - controlViewHeight() == pos.y();
    }

    void pushCursor(const QCursor &cursor)
    {
        if (cursorPushed)
            return;
        prevCursor = viewManager->view(Ac::PitchScene)->cursor();
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            viewManager->view(Ac::SceneType(i))->setCursor(cursor);
        cursorPushed = true;
    }

    void popCursor()
    {
        if (!cursorPushed)
            return;
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            viewManager->view(Ac::SceneType(i))->setCursor(prevCursor);
        cursorPushed = false;
    }

    void moveSeparator(const QPoint &pos)
    {
        qreal height = q->height() - LABELVIEW_HEIGHT;
        controlHeightPercentage = (height - (qreal(pos.y()) - LABELVIEW_HEIGHT)) / height;
        controlHeightPercentage = qBound(qreal(0.01f), controlHeightPercentage, qreal(0.99f));
        updateViewHeights();
    }
};

MainWidget::MainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new MainWidgetPrivate(this))
{
    QGraphicsView *timeLabelView = d->viewManager->view(Ac::TimeLabelScene);
    d->layout->addWidget(timeLabelView, 0, 0);
    timeLabelView->setBackgroundRole(QPalette::Window);
    timeLabelView->setStyleSheet("QFrame {"
                                 "border-top: 0px solid black;"
                                 "}");

    d->layout->addWidget(d->topRight, 0, 1);
    d->topRight->setBackgroundRole(QPalette::Window);
    d->topRight->setFrameShape(QFrame::NoFrame);

    QGraphicsView *pitchView = d->viewManager->view(Ac::PitchScene);
    d->layout->addWidget(pitchView, 1, 0);
    pitchView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    pitchView->setStyleSheet("QFrame {"
                             "border-top: 0px solid black;"
                             "}");

    QGraphicsView *pitchLabelView = d->viewManager->view(Ac::PitchLabelScene);
    d->layout->addWidget(pitchLabelView, 1, 1);
    pitchLabelView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    pitchLabelView->setBackgroundRole(QPalette::Window);
    pitchLabelView->setStyleSheet("QFrame {"
                                  "border-top: 0px solid black;"
                                  "}");

    QGraphicsView *controlView = d->viewManager->view(Ac::ControlScene);
    d->layout->addWidget(controlView, 2, 0);
    controlView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    controlView->setStyleSheet("QFrame {"
                               "border-top: 1px solid black;"
                               "}");

    QGraphicsView *controlLabelView = d->viewManager->view(Ac::ControlLabelScene);
    d->layout->addWidget(controlLabelView, 2, 1);
    controlLabelView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    controlLabelView->setBackgroundRole(QPalette::Window);
    controlLabelView->setStyleSheet("QFrame {"
                                    "border-top: 1px solid black;"
                                    "}");
    setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    delete d;
}

void MainWidget::setModel(Model *model)
{
    d->viewManager->setModel(model);
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()
            &&  d->posIsOverControlSeparator(event->pos()))
        d->draggingSeparator = true;
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (d->draggingSeparator)
        d->moveSeparator(event->pos());
    else if (d->posIsOverControlSeparator(event->pos()))
        d->pushCursor(QCursor(Qt::SplitVCursor));
    else
        d->popCursor();
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()
            && d->draggingSeparator) {
        d->moveSeparator(event->pos());
        d->popCursor();
        d->draggingSeparator = false;
    }
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    d->updateViewHeights();
}

void MainWidget::showEvent(QShowEvent *)
{
    d->updateViewHeights();
}
