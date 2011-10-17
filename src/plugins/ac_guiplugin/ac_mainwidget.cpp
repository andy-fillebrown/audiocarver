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

#include <QLayout>
#include <QMouseEvent>

#define LABELVIEW_WIDTH 48
#define LABELVIEW_HEIGHT 24

class MainWidgetPrivate
{
public:
    MainWidget *q;
    ViewManager *viewManager;
    MiGraphicsView *topRightView;
    qreal controlHeightPercentage;
    QCursor prevCursor;
    bool cursorPushed;
    bool draggingSeparator;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
        ,   viewManager(new ViewManager(q))
        ,   topRightView(new MiGraphicsView)
        ,   controlHeightPercentage(0.25f)
        ,   cursorPushed(false)
        ,   draggingSeparator(false)
    {}

    void init()
    {
        topRightView->setParent(q);
        topRightView->setBackgroundRole(QPalette::Window);
        topRightView->setFrameShape(QFrame::NoFrame);
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            viewManager->view(Ac::SceneType(i))->setParent(q);
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
        qreal leftWidth = q->width() - LABELVIEW_WIDTH;
        qreal rightWidth = LABELVIEW_WIDTH;
        qreal topHeight = LABELVIEW_HEIGHT;
        qreal middleHeight = pitchViewHeight();
        qreal bottomHeight = controlViewHeight();
        qreal bottomPosY = topHeight + middleHeight;
        viewManager->view(Ac::TimeLabelScene)->setGeometry(0, 0, leftWidth, topHeight);
        topRightView->setGeometry(QRect(leftWidth, 0, rightWidth, topHeight));
        viewManager->view(Ac::PitchScene)->setGeometry(QRect(0, topHeight, leftWidth, middleHeight));
        viewManager->view(Ac::PitchLabelScene)->setGeometry(QRect(leftWidth, topHeight, rightWidth, middleHeight));
        viewManager->view(Ac::ControlScene)->setGeometry(QRect(0, bottomPosY, leftWidth, bottomHeight));
        viewManager->view(Ac::ControlLabelScene)->setGeometry(QRect(leftWidth, bottomPosY, rightWidth, bottomHeight));
    }

    int controlSeparatorY() const
    {
        return q->height() - controlViewHeight();
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
    d->init();
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
            &&  d->controlSeparatorY() == event->pos().y())
        d->draggingSeparator = true;
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (d->draggingSeparator)
        d->moveSeparator(event->pos());
    else if (d->controlSeparatorY() == event->pos().y())
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
