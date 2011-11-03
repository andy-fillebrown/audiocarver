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

#include <ac_namespace.h>

#include <mi_graphicsview.h>

#include <QMouseEvent>
#include <QStyleOption>

#define LABELVIEW_WIDTH 48
#define LABELVIEW_HEIGHT 24

class MainWidgetPrivate
{
public:
    MainWidget *q;
    ViewManager *viewManager;
    MiGraphicsView *topRightView;
    qreal controlHeightPercentage;
    quint32 draggingSeparator;
    QPoint currentPos;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
        ,   viewManager(new ViewManager(q))
        ,   topRightView(new MiGraphicsView)
        ,   controlHeightPercentage(0.25f)
        ,   draggingSeparator(quint32(false))
    {
        topRightView->setParent(q);
        topRightView->setBackgroundRole(QPalette::Window);
        topRightView->setCursor(Qt::ArrowCursor);
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

    int separatorHeight() const
    {
        return q->style()->pixelMetric(QStyle::PM_SplitterWidth, 0, q);
    }

    QRect separatorRect() const
    {
        return QRect(0, q->height() - controlViewHeight() - separatorHeight(), q->width(), separatorHeight());
    }

    int controlViewHeight() const
    {
        const int h = (q->height() - LABELVIEW_HEIGHT) * controlHeightPercentage;
        return h < 0 ? 0 : h;
    }

    int pitchViewHeight() const
    {
        const int h = q->height() - LABELVIEW_HEIGHT - controlViewHeight();
        return h < 0 ? 0 : h;
    }

    void updateViewHeights()
    {
        const int separator_height = separatorHeight();
        const int leftWidth = q->width() - LABELVIEW_WIDTH;
        const int rightWidth = LABELVIEW_WIDTH;
        const int topHeight = LABELVIEW_HEIGHT;
        int middleHeight = pitchViewHeight() - (separator_height / 2);
        if (middleHeight < 0)
            middleHeight = 0;
        if (q->height() < (topHeight + middleHeight + separator_height))
            middleHeight = q->height() - topHeight - separator_height;
        const int bottomHeight = q->height() - (topHeight + middleHeight + separator_height);
        const int bottomPosY = topHeight + middleHeight + separator_height;
        viewManager->view(Ac::TimeLabelScene)->setGeometry(0, 0, leftWidth, topHeight);
        topRightView->setGeometry(QRect(leftWidth, 0, rightWidth, topHeight));
        viewManager->view(Ac::PitchScene)->setGeometry(QRect(0, topHeight, leftWidth, middleHeight));
        viewManager->view(Ac::PitchLabelScene)->setGeometry(QRect(leftWidth, topHeight, rightWidth, middleHeight));
        viewManager->view(Ac::ControlScene)->setGeometry(QRect(0, bottomPosY, leftWidth, bottomHeight));
        viewManager->view(Ac::ControlLabelScene)->setGeometry(QRect(leftWidth, bottomPosY, rightWidth, bottomHeight));
        viewManager->updateViews();
    }

    void moveSeparator(const QPoint &pos)
    {
        qreal height = q->height() - LABELVIEW_HEIGHT;
        controlHeightPercentage = (height - (qreal(pos.y()) - LABELVIEW_HEIGHT)) / height;
        controlHeightPercentage = qBound(qreal(0.0f), controlHeightPercentage, qreal(1.0f));
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
    setCursor(Qt::SplitVCursor);
}

MainWidget::~MainWidget()
{
    delete d;
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    int offset = 0;
    if (d->controlViewHeight()) {
        offset = d->separatorHeight();
        if (d->pitchViewHeight())
            offset /= 2;
    }
    d->draggingSeparator =
            Qt::LeftButton == event->button()
            && d->separatorRect().translated(0, offset).contains(event->pos());
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    d->currentPos = event->pos();
    if (d->draggingSeparator)
        d->moveSeparator(event->pos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button() && d->draggingSeparator) {
        d->moveSeparator(event->pos());
        d->draggingSeparator = false;
    }
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    d->updateViewHeights();
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QStyleOption opt(0);
    opt.rect = d->separatorRect();
    opt.palette = palette();
    opt.state = QStyle::State_Horizontal;
    if (opt.rect.contains(d->currentPos))
        opt.state |= QStyle::State_MouseOver;
    if (d->draggingSeparator)
        opt.state |= QStyle::State_Sunken;
    if (isEnabled())
        opt.state |= QStyle::State_Enabled;
    parentWidget()->style()->drawControl(QStyle::CE_Splitter, &opt, &p, this);
}
