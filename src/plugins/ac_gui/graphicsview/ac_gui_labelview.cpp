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

#include "ac_gui_labelview.h"
#include "ac_gui_graphicsviewmanager.h"
#include <idatabase.h>
#include <imodel.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <QMouseEvent>
#include <QModelIndex>

using namespace Ac;
using namespace Qt;

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/zoom-v-cursor.png"));
    return cursor;
}

class LabelViewPrivate
{
public:
    LabelView *q;
    uint updatesDisabled : 1;

    LabelViewPrivate(LabelView *q)
        :   q(q)
        ,   updatesDisabled(false)
    {}

    virtual ~LabelViewPrivate()
    {}

    void updateGridLineVisibilites()
    {
        const qreal padding = qreal(30.0f) / q->paddingScale();
        IModelItem *grid_lines = q->gridLineList();
        const int n = grid_lines->count();
        int minPriority = INT_MAX;
        int prevPriority = 0;
        qreal prevLocation = qreal(-1.0f);
        for (int i = 0;  i < n;  ++i) {
            IModelData *line = query<IModelData>(grid_lines->at(i));
            int curPriority = line->get<int>(PriorityRole);
            if (minPriority && (minPriority < curPriority))
                continue;
            const qreal curLocation = line->get<qreal>(LocationRole);
            if (curPriority && (curLocation < prevLocation))
                minPriority = qMin(minPriority, qMax(prevPriority, curPriority));
            else {
                prevPriority = curPriority;
                prevLocation = curLocation + padding;
            }
        }
        for (int i = 0;  i < n;  ++i) {
            IModelData *line = query<IModelData>(grid_lines->at(i));
            if (line->get<int>(PriorityRole) <= minPriority) {
                if (!line->get<bool>(VisibilityRole)) {
                    q->setUpdatesEnabled(false);
                    updatesDisabled = true;
                    line->set(true, VisibilityRole);
                }
            } else {
                if (line->get<bool>(VisibilityRole)) {
                    q->setUpdatesEnabled(false);
                    updatesDisabled = true;
                    line->set(false, VisibilityRole);
                }
            }
        }
    }
};

LabelView::LabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsView(scene, parent)
    ,   d(new LabelViewPrivate(this))
{
    setBackgroundRole(QPalette::Window);
    setCursor(OpenHandCursor);
}

LabelView::~LabelView()
{
    delete d;
}

void LabelView::updateView()
{
    if (isDirty())
        updateViewSettings();
    if (d->updatesDisabled) {
        setUpdatesEnabled(true);
        d->updatesDisabled = false;
    } else
        GraphicsView::updateView();
}

void LabelView::viewScaleChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    GraphicsView::viewScaleChanged(role);
    if (scaleRole() == role)
        d->updateGridLineVisibilites();
}

void LabelView::scoreLengthChanged()
{
    if (IDatabase::instance()->isReading())
        return;
    GraphicsView::scoreLengthChanged();
    d->updateGridLineVisibilites();
    if (d->updatesDisabled) {
        setUpdatesEnabled(true);
        d->updatesDisabled = false;
    }
}

void LabelView::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    IDatabase *db = IDatabase::instance();
    if (db->isReading())
        return;
//    IModelList *top_right = query<IModelList>(query<IModel>(db)->itemFromIndex(topRight));
//    if (top_right == gridLineList()) {
//        d->updateGridLineVisibilites();
//        updateView();
//    }
}

void LabelView::panFinished()
{
    setCursor(OpenHandCursor);
}

void LabelView::zoomFinished()
{
    setCursor(OpenHandCursor);
}

void LabelView::updateViewSettings()
{
    GraphicsView::updateViewSettings();
    d->updateGridLineVisibilites();
}

void LabelView::mousePressEvent(QMouseEvent *event)
{
    if (LeftButton == event->button())
        if (selectPlayCursor(event->pos()))
            return;
    QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), RightButton, event->buttons(), event->modifiers());
    GraphicsView::mousePressEvent(e);
    delete e;
}

void LabelView::mouseReleaseEvent(QMouseEvent *event)
{
    if (LeftButton == event->button()) {
        if (isPlayCursorSelected()) {
            finishDraggingPlayCursor(event->pos());
            return;
        }
    }
    QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), RightButton, event->buttons(), event->modifiers());
    GraphicsView::mouseReleaseEvent(e);
    delete e;
}

void LabelView::mouseDoubleClickEvent(QMouseEvent *event)
{
    GraphicsView::mouseDoubleClickEvent(event);
    setCursor(OpenHandCursor);
}

QPointF LabelVView::sceneCenter() const
{
    return QPointF(qreal(0.5f), -GraphicsViewManager::instance()->position(positionRoleY()));
}

void LabelVView::zoomStarting()
{
    setCursor(zoomCursor());
}
