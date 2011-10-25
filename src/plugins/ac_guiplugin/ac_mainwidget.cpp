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

#include <QMouseEvent>

#define LABELVIEW_WIDTH 48
#define LABELVIEW_HEIGHT 24
#define SEPARATOR_HEIGHT 4

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
    {
        topRightView->setParent(q);
        topRightView->setBackgroundRole(QPalette::Window);
        topRightView->setStyleSheet("QFrame {"
                                    "border-top: 1px solid palette(shadow);"
                                    "border-bottom: 1px solid palette(shadow);"
                                    "border-left: 0px solid palette(shadow);"
                                    "border-right: 1px solid palette(shadow);"
                                    "}");
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
        int leftWidth = q->width() - LABELVIEW_WIDTH;
        int rightWidth = LABELVIEW_WIDTH;
        int topHeight = LABELVIEW_HEIGHT;
        int middleHeight = pitchViewHeight() - (SEPARATOR_HEIGHT / 2);
        if (middleHeight < 0)
            middleHeight = 0;
        if (q->height() < (topHeight + middleHeight + SEPARATOR_HEIGHT))
            middleHeight = q->height() - topHeight - SEPARATOR_HEIGHT;
        int bottomHeight = q->height() - (topHeight + middleHeight + SEPARATOR_HEIGHT);
        int bottomPosY = topHeight + middleHeight + SEPARATOR_HEIGHT;
        viewManager->view(Ac::TimeLabelScene)->setGeometry(0, 0, leftWidth, topHeight);
        topRightView->setGeometry(QRect(leftWidth, 0, rightWidth, topHeight));
        viewManager->view(Ac::PitchScene)->setGeometry(QRect(0, topHeight, leftWidth, middleHeight));
        viewManager->view(Ac::PitchLabelScene)->setGeometry(QRect(leftWidth, topHeight, rightWidth, middleHeight));
        viewManager->view(Ac::ControlScene)->setGeometry(QRect(0, bottomPosY, leftWidth, bottomHeight));
        viewManager->view(Ac::ControlLabelScene)->setGeometry(QRect(leftWidth, bottomPosY, rightWidth, bottomHeight));
    }

    void moveSeparator(const QPoint &pos)
    {
        qreal height = q->height() - LABELVIEW_HEIGHT;
        controlHeightPercentage = (height - (qreal(pos.y()) - LABELVIEW_HEIGHT)) / height;
        updateViewHeights();
    }
};

MainWidget::MainWidget(QWidget *parent)
    :   QFrame(parent)
    ,   d(new MainWidgetPrivate(this))
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 0px solid palette(shadow);"
                  "border-left: 0px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
    setCursor(QCursor(Qt::SplitVCursor));
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
    if (Qt::LeftButton == event->button())
        d->draggingSeparator = true;
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (d->draggingSeparator)
        d->moveSeparator(event->pos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()) {
        d->moveSeparator(event->pos());
        d->draggingSeparator = false;
    }
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    d->updateViewHeights();
}
