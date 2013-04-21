/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#include "ac_gui_graphicslabelview.h"
#include "ac_gui_graphicsviewmanager.h"
#include <ac_core_namespace.h>
#include <idatabase.h>
#include <imodel.h>
#include <imodelitem.h>
#include <QMouseEvent>
#include <QModelIndex>

using namespace Ac;
using namespace Qt;

GraphicsLabelView::GraphicsLabelView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsView(scene, parent)
    ,   _updatesDisabled(false)
{
    setBackgroundRole(QPalette::Window);
    setCursor(OpenHandCursor);
}

void GraphicsLabelView::updateGridLineVisibilities()
{
    const qreal padding = qreal(30.0f) / paddingScale();
    IModelItem *grid_lines = gridLineList();
    const int n = grid_lines->itemCount();
    int minPriority = INT_MAX;
    int prevPriority = 0;
    qreal prevLocation = qreal(-1.0f);
    for (int i = 0;  i < n;  ++i) {
        IModelItem *line = query<IModelItem>(grid_lines->itemAt(i));
        int curPriority = get<int>(line, PriorityRole);
        if (minPriority && (minPriority < curPriority))
            continue;
        const qreal curLocation = get<qreal>(line, LocationRole);
        if (curPriority && (curLocation < prevLocation))
            minPriority = qMin(minPriority, qMax(prevPriority, curPriority));
        else {
            prevPriority = curPriority;
            prevLocation = curLocation + padding;
        }
    }
    for (int i = 0;  i < n;  ++i) {
        IModelItem *line = query<IModelItem>(grid_lines->itemAt(i));
        if (get<int>(line, PriorityRole) <= minPriority) {
            if (!get<bool>(line, VisibilityRole)) {
                setUpdatesEnabled(false);
                _updatesDisabled = true;
                line->set(true, VisibilityRole);
            }
        } else {
            if (get<bool>(line, VisibilityRole)) {
                setUpdatesEnabled(false);
                _updatesDisabled = true;
                line->set(false, VisibilityRole);
            }
        }
    }
}

void GraphicsLabelView::updateView()
{
    if (isDirty())
        updateViewSettings();
    if (_updatesDisabled) {
        setUpdatesEnabled(true);
        _updatesDisabled = false;
    } else
        GraphicsView::updateView();
}

void GraphicsLabelView::viewScaleChanged(int role)
{
    if (IDatabase::instance()->isReading())
        return;
    GraphicsView::viewScaleChanged(role);
    if (scaleRole() == role)
        updateGridLineVisibilities();
}

void GraphicsLabelView::scoreLengthChanged()
{
    if (IDatabase::instance()->isReading())
        return;
    GraphicsView::scoreLengthChanged();
    updateGridLineVisibilities();
    if (_updatesDisabled) {
        setUpdatesEnabled(true);
        _updatesDisabled = false;
    }
}

void GraphicsLabelView::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    IDatabase *db = IDatabase::instance();
    if (db->isReading())
        return;
    IModelItem *top_right_item = IModel::instance()->itemFromIndex(topRight);
    if (top_right_item == gridLineList()) {
        updateGridLineVisibilities();
        updateView();
    }
}

void GraphicsLabelView::panFinished()
{
    setCursor(OpenHandCursor);
}

void GraphicsLabelView::zoomFinished()
{
    setCursor(OpenHandCursor);
}

void GraphicsLabelView::updateViewSettings()
{
    GraphicsView::updateViewSettings();
    updateGridLineVisibilities();
}

void GraphicsLabelView::mousePressEvent(QMouseEvent *event)
{
    if (LeftButton == event->button())
        if (selectPlayCursor(event->pos()))
            return;
    QMouseEvent mouse_event(QEvent::MouseButtonPress, event->pos(), RightButton, event->buttons(), event->modifiers());
    GraphicsView::mousePressEvent(&mouse_event);
}

void GraphicsLabelView::mouseReleaseEvent(QMouseEvent *event)
{
    if (LeftButton == event->button()) {
        if (isPlayCursorSelected()) {
            finishDraggingPlayCursor(event->pos());
            return;
        }
    }
    QMouseEvent mouse_event(QEvent::MouseButtonPress, event->pos(), RightButton, event->buttons(), event->modifiers());
    GraphicsView::mouseReleaseEvent(&mouse_event);
}

void GraphicsLabelView::mouseDoubleClickEvent(QMouseEvent *event)
{
    GraphicsView::mouseDoubleClickEvent(event);
    setCursor(OpenHandCursor);
}
