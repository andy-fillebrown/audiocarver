/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include <ac_gripselectionmodel.h>
#include <ac_selecteditemspropertyview.h>
#include <ac_trackview.h>
#include <ac_viewmanager.h>

#include <ac_namespace.h>

#include <mi_graphicsview.h>

#include <icore.h>
#include <mainwindow.h>

#include <QDockWidget>
#include <QMouseEvent>
#include <QStyleOption>
#include <QTableView>

#define LABELVIEW_WIDTH 48
#define LABELVIEW_HEIGHT 23

class MainWidgetPrivate
{
public:
    MainWidget *q;
    ViewManager *viewManager;
    MiGraphicsView *topRightView;
    qreal controlHeightPercentage;
    uint hoveringOverSeparator : 1;
    uint draggingSeparator : bitsizeof(uint) - 1;
    QDockWidget *trackViewDock;
    TrackView *trackView;
    QDockWidget *propertyViewDock;
    SelectedItemsPropertyView *propertyView;
    QTableView *gripView;
    GripSelectionModel *gripModel;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
        ,   viewManager(new ViewManager(q))
        ,   topRightView(new MiGraphicsView)
        ,   controlHeightPercentage(0.25f)
        ,   hoveringOverSeparator(false)
        ,   draggingSeparator(false)
        ,   trackViewDock(new QDockWidget("Track Editor", q))
        ,   trackView(new TrackView(trackViewDock))
        ,   propertyViewDock(new QDockWidget("Property Editor", q))
        ,   propertyView(new SelectedItemsPropertyView(propertyViewDock))
        ,   gripView(new QTableView(propertyViewDock))
        ,   gripModel(new GripSelectionModel(q))
    {
        topRightView->setParent(q);
        topRightView->setBackgroundRole(QPalette::Window);
        topRightView->setCursor(Qt::ArrowCursor);
        topRightView->setStyleSheet("QFrame {"
                                    "border-top: 0px solid palette(shadow);"
                                    "border-bottom: 1px solid palette(shadow);"
                                    "border-left: 0px solid palette(shadow);"
                                    "border-right: 1px solid palette(shadow);"
                                    "}");
        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
            viewManager->view(Ac::SceneType(i))->setParent(q);

        Core::MainWindow *mw = Core::ICore::instance()->mainWindow();

        // Track View Dock Widget
        trackViewDock->setObjectName("Track View Dock Widget");
        trackViewDock->setWidget(trackView);
        mw->addDockWidget(Qt::LeftDockWidgetArea, trackViewDock);

        // Property View Dock Widget
        propertyViewDock->setObjectName("Property View Dock Widget");
        mw->addDockWidget(Qt::LeftDockWidgetArea, propertyViewDock);

        gripView->setModel(gripModel);
    }

    int separatorHeight() const
    {
        return q->style()->pixelMetric(QStyle::PM_SplitterWidth);
    }

    QRect separatorRect() const
    {
        int offset = 0;
        if (controlViewHeight()) {
            offset = separatorHeight();
            if (pitchViewHeight()) {
                offset /= 2;
#               ifdef Q_OS_WIN
                {   offset += 1;
                }
#               endif
            }
        }
        return QRect(0, q->height() - controlViewHeight() - separatorHeight(), q->width(), separatorHeight()).translated(0, offset);
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
        int leftWidth = q->width() - LABELVIEW_WIDTH;
        if (leftWidth < 1)
            leftWidth = 1;
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
        q->update(separatorRect());
    }

    void moveSeparator(const QPoint &pos)
    {
        qreal height = q->height() - LABELVIEW_HEIGHT;
        controlHeightPercentage = (height - (qreal(pos.y()) - LABELVIEW_HEIGHT)) / height;
        controlHeightPercentage = qBound(qreal(0.0f), controlHeightPercentage, qreal(1.0f));
        updateViewHeights();
    }
};

static MainWidget *instance = 0;

MainWidget::MainWidget(QWidget *parent)
    :   QFrame(parent)
    ,   d(new MainWidgetPrivate(this))
{
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 0px solid palette(shadow);"
                  "border-left: 0px solid palette(shadow);"
                  "border-right: 0px solid palette(shadow);"
                  "}");
    setCursor(Qt::SplitVCursor);
    setMouseTracking(true);

    connect(d->gripModel, SIGNAL(gripsSelected()), SLOT(showGripView()));
    connect(d->gripModel, SIGNAL(gripsDeselected()), SLOT(showPropertyView()));
    showPropertyView();

    ::instance = this;
}

MainWidget::~MainWidget()
{
    ::instance = 0;
    delete d;
}

MainWidget *MainWidget::instance()
{
    return ::instance;
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    d->draggingSeparator =
            Qt::LeftButton == event->button()
            && d->separatorRect().contains(event->pos());
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    const uint wasHoveringOverSeparator = d->hoveringOverSeparator;
    d->hoveringOverSeparator = d->separatorRect().contains(event->pos());
    if (d->hoveringOverSeparator != wasHoveringOverSeparator)
        update(d->separatorRect());

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

void MainWidget::leaveEvent(QEvent *)
{
    d->hoveringOverSeparator = false;
    update(d->separatorRect());
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    d->updateViewHeights();
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QStyleOption opt(0);
    opt.rect = d->separatorRect().adjusted(0, 1, 0, 0);
    opt.palette = palette();
    opt.state = QStyle::State_None;
    if (d->hoveringOverSeparator)
        opt.state |= QStyle::State_MouseOver;
    if (d->draggingSeparator)
        opt.state |= QStyle::State_Sunken;
    if (isEnabled())
        opt.state |= QStyle::State_Enabled;
    parentWidget()->style()->drawControl(QStyle::CE_Splitter, &opt, &p, this);
}

void MainWidget::showGripView()
{
    d->propertyView->hide();
    d->propertyViewDock->setWidget(d->gripView);
    d->gripView->show();
}

void MainWidget::showPropertyView()
{
    d->gripView->hide();
    d->propertyViewDock->setWidget(d->propertyView);
    d->propertyView->show();
}
