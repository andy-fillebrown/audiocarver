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

#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

static const int colorColumnWidth = 16;
static const int visibilityColumnWidth = 12;
static const int recordingColumnWidth = 12;

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

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QColor color = index.data().value<QColor>();
        painter->save();
        painter->setPen(color);
        painter->setBrush(QBrush(color));
        painter->drawRect(option.rect.adjusted(1, 1, -1, -1));
        painter->restore();
    }
};

class VisibilityDelegate : public Delegate
{
public:
    explicit VisibilityDelegate(QObject *parent = 0)
        :   Delegate(parent)
    {}

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        Q_UNUSED(option);
        if (QEvent::MouseButtonPress != event->type())
            return false;
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (Qt::LeftButton == e->button())
            model->setData(index, !index.data().toBool(), Qt::DisplayRole);
        return true;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // Early out if track is not visible.
        if (!index.data().toBool())
            return;

        // Draw black dot if track is visible.
        painter->save();
        painter->setBrush(Qt::SolidPattern);
        painter->drawEllipse(option.rect.center(), 2, 2);
        painter->restore();
    }
};

class RecordingDelegate : public Delegate
{
public:
    explicit RecordingDelegate(QObject *parent = 0)
        :   Delegate(parent)
    {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // Early out if track is not visible.
        if (!index.data().toBool())
            return;

        // Draw red dot if track is recording.
        painter->save();
        painter->setPen(Qt::red);
        painter->setBrush(QBrush(Qt::red));
        painter->drawEllipse(option.rect.center(), 2, 2);
        painter->restore();
    }
};

TrackView::TrackView(QWidget *parent)
    :   QTreeView(parent)
{
    setHeaderHidden(true);
    setRootIsDecorated(false);
    setAutoScroll(false);
    setItemDelegateForColumn(0, new ColorDelegate(this));
    setItemDelegateForColumn(2, new VisibilityDelegate(this));
    setItemDelegateForColumn(3, new RecordingDelegate(this));
    setSelectionMode(NoSelection);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TrackView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    setColumnWidth(0, colorColumnWidth);
    setColumnWidth(1, width() - (colorColumnWidth + visibilityColumnWidth + recordingColumnWidth) - 12);
    setColumnWidth(2, visibilityColumnWidth);
    setColumnWidth(3, recordingColumnWidth);
    QAbstractItemModel *m = model();
    QModelIndex root_index = rootIndex();
    const int row_h = rowHeight(m->index(0, 0, root_index));
    if (row_h)
        verticalScrollBar()->setRange(0, (((m->rowCount(root_index) + 1) * row_h) - viewport()->height()) / row_h);
}
