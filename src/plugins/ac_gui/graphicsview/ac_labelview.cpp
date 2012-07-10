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

#include "ac_labelview.h"

#include <ac_viewmanager.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>

#include <QMouseEvent>

#include <QModelIndex>

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/zoom-v-cursor.png"));
    return cursor;
}

class LabelViewPrivate
{
public:
    LabelView *q;
    uint updatesDisabled : bitsizeof(uint);

    LabelViewPrivate(LabelView *q)
        :   q(q)
        ,   updatesDisabled(false)
    {}

    virtual ~LabelViewPrivate()
    {}

    void updateGridLineVisibilites()
    {
        const qreal padding = qreal(30.0f) / q->paddingScale();
        const QModelIndex gridLines = q->gridLineListIndex();
        IModel *model = IModel::instance();
        const int n = model->rowCount(gridLines);
        int minPriority = INT_MAX;
        int prevPriority = 0;
        qreal prevLocation = qreal(-1.0f);
        for (int i = 0;  i < n;  ++i) {
            const QModelIndex line = model->index(i, gridLines);
            int curPriority = line.data(Ac::PriorityRole).toInt();
            if (minPriority && (minPriority < curPriority))
                continue;
            const qreal curLocation = line.data(Ac::LocationRole).toReal();
            if (curPriority && (curLocation < prevLocation))
                minPriority = qMin(minPriority, qMax(prevPriority, curPriority));
            else {
                prevPriority = curPriority;
                prevLocation = curLocation + padding;
            }
        }
        for (int i = 0;  i < n;  ++i) {
            const QModelIndex line = model->index(i, gridLines);
            if (line.data(Ac::PriorityRole).toInt() <= minPriority) {
                if (!line.data(Ac::VisibilityRole).toBool()) {
                    q->setUpdatesEnabled(false);
                    updatesDisabled = true;
                    model->setData(line, true, Ac::VisibilityRole);
                }
            } else {
                if (line.data(Ac::VisibilityRole).toBool()) {
                    q->setUpdatesEnabled(false);
                    updatesDisabled = true;
                    model->setData(line, false, Ac::VisibilityRole);
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
    setCursor(Qt::OpenHandCursor);
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
    Q_UNUSED(bottomLeft);
    if (IDatabase::instance()->isReading())
        return;
    if (topRight == gridLineListIndex()) {
        d->updateGridLineVisibilites();
        updateView();
    }
}

void LabelView::panFinished()
{
    setCursor(Qt::OpenHandCursor);
}

void LabelView::zoomFinished()
{
    setCursor(Qt::OpenHandCursor);
}

void LabelView::updateViewSettings()
{
    GraphicsView::updateViewSettings();
    d->updateGridLineVisibilites();
}

void LabelView::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
        if (selectPlayCursor(event->pos()))
            return;
    QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), Qt::RightButton, event->buttons(), event->modifiers());
    GraphicsView::mousePressEvent(e);
    delete e;
}

void LabelView::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()) {
        if (isPlayCursorSelected()) {
            finishDraggingPlayCursor(event->pos());
            return;
        }
    }
    QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), Qt::RightButton, event->buttons(), event->modifiers());
    GraphicsView::mouseReleaseEvent(e);
    delete e;
}

void LabelView::mouseDoubleClickEvent(QMouseEvent *event)
{
    GraphicsView::mouseDoubleClickEvent(event);
    setCursor(Qt::OpenHandCursor);
}

QPointF LabelVView::sceneCenter() const
{
    return QPointF(qreal(0.5f), -ViewManager::instance()->position(positionRoleY()));
}

void LabelVView::zoomStarting()
{
    setCursor(zoomCursor());
}
