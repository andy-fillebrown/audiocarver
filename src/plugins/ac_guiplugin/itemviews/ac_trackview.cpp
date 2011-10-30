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

#include "ac_trackview.h"

#include <ac_trackmodel.h>

#include <mi_idatabase.h>

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

static const int colorColumnWidth = 16;
static const int buttonColumnWidth = 12;

class Delegate : public QAbstractItemDelegate
{
public:
    explicit Delegate(QObject *parent = 0)
        :   QAbstractItemDelegate(parent)
    {}

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize();
    }
};

class ColorDelegate : public Delegate
{
public:
    explicit ColorDelegate(QObject *parent = 0)
        :   Delegate(parent)
    {}

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        Q_UNUSED(option);
        if (QEvent::MouseButtonPress != event->type())
            return false;
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (Qt::LeftButton != e->button())
            return false;
        QColor color = QColorDialog::getColor(index.data().value<QColor>(), qobject_cast<QWidget*>(parent()));
        if (color.isValid())
            model->setData(index, color, Qt::DisplayRole);
        return true;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        const QColor color = index.data().value<QColor>();
        painter->save();
        painter->setPen(color);
        painter->setBrush(QBrush(color));
        painter->drawRect(option.rect.adjusted(1, 1, -2, -2));
        painter->restore();
    }
};

class ToggleButtonDelegate : public Delegate
{
public:
    explicit ToggleButtonDelegate(QObject *parent = 0)
        :   Delegate(parent)
    {}

    virtual void setPainterColors(QPainter *painter, const QModelIndex &index) const
    {
        if (index.data().toBool())
            painter->setBrush(Qt::SolidPattern);
    }

    QRect adjustedButtonRect(const QRect &optionRect) const
    {
        QRect adjusted = optionRect;
        adjusted.setWidth(buttonColumnWidth);
        return adjusted;
    }

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        Q_UNUSED(option);
        if (QEvent::MouseButtonPress != event->type())
            return false;
        const QMouseEvent *e = static_cast<const QMouseEvent*>(event);
        if (Qt::LeftButton == e->button())
            model->setData(index, !index.data().toBool(), Qt::DisplayRole);
        return true;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        painter->save();
        setPainterColors(painter, index);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(adjustedButtonRect(option.rect).center(), 3, 3);
        painter->restore();
    }
};

class RecordButtonDelegate : public ToggleButtonDelegate
{
public:
    explicit RecordButtonDelegate(QObject *parent = 0)
        :   ToggleButtonDelegate(parent)
    {}

    virtual void setPainterColors(QPainter *painter, const QModelIndex &index) const
    {
        painter->setPen(Qt::red);
        if (index.data().toBool())
            painter->setBrush(QBrush(Qt::red));
    }
};

TrackView::TrackView(QWidget *parent)
    :   QTreeView(parent)
{
    setModel(new TrackModel(IDatabase::instance()->model()));
    setHeaderHidden(true);
    setRootIsDecorated(false);
    setAutoScroll(false);
    setItemDelegateForColumn(0, new ColorDelegate(this));
    setItemDelegateForColumn(2, new ToggleButtonDelegate(this));
    setItemDelegateForColumn(3, new RecordButtonDelegate(this));
    setSelectionMode(SingleSelection);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    viewport()->setAcceptDrops(true);
}

void TrackView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
    setDirtyRegion(rect());
}

void TrackView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    const QAbstractItemModel *m = model();
    const QModelIndex root_index = rootIndex();
    const int row_h = rowHeight(m->index(0, 0, root_index));
    const QWidget *vport = viewport();
    if (row_h)
        verticalScrollBar()->setRange(0, (((m->rowCount(root_index) + 1) * row_h) - vport->height()) / row_h);
    setColumnWidth(0, colorColumnWidth);
    setColumnWidth(1, vport->width() - (colorColumnWidth + buttonColumnWidth + buttonColumnWidth));
    setColumnWidth(2, buttonColumnWidth);
    setColumnWidth(3, buttonColumnWidth);
}
