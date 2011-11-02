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

#include "ac_labelview.h"

#include <ac_viewmanager.h>

#include <ac_model.h>

#include <mi_idatabase.h>

#include <QMouseEvent>

static const QCursor &zoomCursor()
{
    static const QCursor cursor(QPixmap(":/ac_guiplugin/images/zoom-v-cursor.png"));
    return cursor;
}

class LabelViewPrivate
{
public:
    LabelView *q;
    QCursor zoomCursor;
    quint32 updatesDisabled : 32;

    LabelViewPrivate(LabelView *q)
        :   q(q)
        ,   zoomCursor(QPixmap(":/ac_guiplugin/images/zoom-v-cursor.png"))
        ,   updatesDisabled(quint32(false))
    {}

    virtual ~LabelViewPrivate()
    {}

    void updateGridLineVisibilites()
    {
        const qreal padding = 50.0f / q->paddingScale();
        const QModelIndex gridLines = q->gridLineListIndex();
        Model *model = ViewManager::instance()->model();
        const int n = model->rowCount(gridLines);
        int minPriority = INT_MAX;
        int prevPriority = 0;
        qreal prevLocation = -1.0f;
        for (int i = 0;  i < n;  ++i) {
            const QModelIndex line = model->index(i, gridLines);
            int curPriority = line.data(Ac::PriorityRole).toInt();
            if (minPriority && (minPriority < curPriority))
                continue;
            const qreal curLocation = line.data(Ac::LocationRole).toReal();
            if (curLocation < prevLocation)
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
                    updatesDisabled = quint32(true);
                    model->setData(line, true, Ac::VisibilityRole);
                }
            } else {
                if (line.data(Ac::VisibilityRole).toBool()) {
                    q->setUpdatesEnabled(false);
                    updatesDisabled = quint32(true);
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
        d->updatesDisabled = quint32(false);
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

void LabelView::dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft)
{
    Q_UNUSED(bottomLeft);
    if (IDatabase::instance()->isReading())
        return;
    QModelIndex index = gridLineListIndex();
    if (topRight == gridLineListIndex())
        d->updateGridLineVisibilites();
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
    QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), Qt::RightButton, event->buttons(), event->modifiers());
    GraphicsView::mousePressEvent(e);
    delete e;
}

void LabelView::mouseReleaseEvent(QMouseEvent *event)
{
    QMouseEvent *e = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), Qt::RightButton, event->buttons(), event->modifiers());
    GraphicsView::mouseReleaseEvent(e);
    delete e;
}

QPointF LabelVView::sceneCenter() const
{
    return QPointF(0.5f, -ViewManager::instance()->position(positionRoleY()));
}

void LabelVView::zoomStarting()
{
    setCursor(zoomCursor());
}
