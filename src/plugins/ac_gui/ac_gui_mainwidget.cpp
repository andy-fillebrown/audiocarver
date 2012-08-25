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

#include "ac_gui_mainwidget.h"
#include "ac_gui_trackview.h"
//#include "ac_gripitemspropertyview.h"
//#include "ac_gripselectionmodel.h"
//#include "ac_gui_viewmanager.h"
//#include "ac_selecteditemspropertyview.h"
//#include <mi_gui_graphicsview.h>
#include <mainwindow.h>
#include <icore.h>
#include <QDockWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QTableView>

#define LABELVIEW_WIDTH 48
#define LABELVIEW_HEIGHT 23

using namespace Core;
using namespace Qt;

class MainWidgetPrivate
{
public:
    MainWidget *q;
//    Mi::Gui::GraphicsView *topRightView;
    qreal controlHeightPercentage;
    QDockWidget *trackViewDock;
    TrackView *trackView;
//    QDockWidget *propertyViewDock;
//    SelectedItemsPropertyView *propertyView;
//    GripItemsPropertyView *gripView;
//    ViewManager *viewManager;
    uint hoveringOverSeparator : 1;
    uint draggingSeparator : 1;

    MainWidgetPrivate(MainWidget *q)
        :   q(q)
//        ,   topRightView(new Mi::Gui::GraphicsView)
        ,   controlHeightPercentage(0.25f)
        ,   trackViewDock(new QDockWidget("Track Editor", q))
        ,   trackView(new TrackView(trackViewDock))
//        ,   propertyViewDock(new QDockWidget("Property Editor", q))
//        ,   propertyView(new SelectedItemsPropertyView(propertyViewDock))
//        ,   gripView(new GripItemsPropertyView(propertyViewDock))
//        ,   viewManager(new ViewManager(q))
        ,   hoveringOverSeparator(false)
        ,   draggingSeparator(false)
    {
//        topRightView->setParent(q);
//        topRightView->setBackgroundRole(QPalette::Window);
//        topRightView->setCursor(Qt::ArrowCursor);
//        topRightView->setStyleSheet("QFrame {"
//                                    "border-top: 0px solid palette(shadow);"
//                                    "border-bottom: 1px solid palette(shadow);"
//                                    "border-left: 0px solid palette(shadow);"
//                                    "border-right: 1px solid palette(shadow);"
//                                    "}");
//        for (int i = 0;  i < Ac::SceneTypeCount;  ++i)
//            viewManager->view(Ac::SceneType(i))->setParent(q);

        MainWindow *main_window = ICore::instance()->mainWindow();

        // Track View Dock Widget
        trackViewDock->setObjectName("Track View Dock Widget");
        trackViewDock->setWidget(trackView);
        main_window->addDockWidget(Qt::LeftDockWidgetArea, trackViewDock);

//        // Property View Dock Widget
//        propertyViewDock->setObjectName("Property View Dock Widget");
//        mw->addDockWidget(Qt::LeftDockWidgetArea, propertyViewDock);
    }

    ~MainWidgetPrivate()
    {
//        delete viewManager;
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
//        const int rightWidth = LABELVIEW_WIDTH;
        const int topHeight = LABELVIEW_HEIGHT;
        int middleHeight = pitchViewHeight() - (separator_height / 2);
        if (middleHeight < 0)
            middleHeight = 0;
        if (q->height() < (topHeight + middleHeight + separator_height))
            middleHeight = q->height() - topHeight - separator_height;
//        const int bottomHeight = q->height() - (topHeight + middleHeight + separator_height);
//        const int bottomPosY = topHeight + middleHeight + separator_height;
//        viewManager->view(Ac::TimeLabelScene)->setGeometry(0, 0, leftWidth, topHeight);
//        topRightView->setGeometry(QRect(leftWidth, 0, rightWidth, topHeight));
//        viewManager->view(Ac::PitchScene)->setGeometry(QRect(0, topHeight, leftWidth, middleHeight));
//        viewManager->view(Ac::PitchLabelScene)->setGeometry(QRect(leftWidth, topHeight, rightWidth, middleHeight));
//        viewManager->view(Ac::ControlScene)->setGeometry(QRect(0, bottomPosY, leftWidth, bottomHeight));
//        viewManager->view(Ac::ControlLabelScene)->setGeometry(QRect(leftWidth, bottomPosY, rightWidth, bottomHeight));
//        viewManager->updateViews();
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
//    GripSelectionModel *grip_model = GripSelectionModel::instance();
//    connect(grip_model, SIGNAL(gripsSelected()), SLOT(showGripView()));
//    connect(grip_model, SIGNAL(gripsDeselected()), SLOT(showPropertyView()));
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
    if (wasHoveringOverSeparator != d->hoveringOverSeparator)
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
//    d->propertyView->hide();
//    d->propertyViewDock->setWidget(d->gripView);
//    d->gripView->show();
}

void MainWidget::showPropertyView()
{
//    d->gripView->hide();
//    d->propertyViewDock->setWidget(d->propertyView);
//    d->propertyView->show();
}
