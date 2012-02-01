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

#include "ac_trackview.h"

#include <ac_colordelegate.h>
#include <ac_noteselectionmodel.h>
#include <ac_recordbuttondelegate.h>
#include <ac_trackmodel.h>
#include <ac_trackselectionmodel.h>

#include <mi_ieditor.h>

#include <mi_imodel.h>

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

static const int buttonColumnWidth = 12;

class TrackViewPrivate
{
public:
    TrackView *q;
    QPoint dragStartPos;
    uint dragging : bitsizeof(uint);
    int dropRow;

    TrackViewPrivate(TrackView *q)
        :   q(q)
        ,   dragging(false)
        ,   dropRow(-1)
    {}

    void updateDropRow(const QPoint &pos)
    {
        dropRow = q->indexAt(pos).row();

        // If the drop row is -1 then we've gone past the last track.
        if (dropRow < 0)
            dropRow = q->model()->rowCount(q->rootIndex());
    }
};

TrackView::TrackView(QWidget *parent)
    :   QTreeView(parent)
    ,   d(new TrackViewPrivate(this))
{
    setModel(TrackModel::instance());
    setSelectionModel(TrackSelectionModel::instance());
    setHeaderHidden(true);
    setRootIsDecorated(false);
    setAutoScroll(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(ExtendedSelection);
    setAcceptDrops(true);
    setDragEnabled(true);
    setAllColumnsShowFocus(true);

    ColorDelegate *colorDelegate = new ColorDelegate(this);
    colorDelegate->setCustomColumn(0);
    setItemDelegateForColumn(0, colorDelegate);

    ToggleButtonDelegate *toggleButtonDelegate = new ToggleButtonDelegate(this);
    toggleButtonDelegate->setButtonColumnWidth(buttonColumnWidth);
    toggleButtonDelegate->setCustomColumn(2);
    setItemDelegateForColumn(2, toggleButtonDelegate);

    RecordButtonDelegate *recordButtonDelegate = new RecordButtonDelegate(this);
    recordButtonDelegate->setButtonColumnWidth(buttonColumnWidth);
    recordButtonDelegate->setCustomColumn(3);
    setItemDelegateForColumn(3, recordButtonDelegate);
}

void TrackView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);

    // We're currently only getting invalid indexes for topLeft and bottomRight
    // even when track data is changed.  It might be an issue in the proxy
    // models.  Regardless, we need to redraw the entire window and call resize
    // to update the scrollbar and set the column widths.
    setDirtyRegion(rect());
    resizeEvent(0);
}

void TrackView::mousePressEvent(QMouseEvent *event)
{
    // Save the event position.  We might be dragging tracks later.
    if (Qt::LeftButton == event->button())
        d->dragStartPos = event->pos();

    // Pass the event to the base class so selecting items still works.
    QTreeView::mousePressEvent(event);
}

void TrackView::mouseMoveEvent(QMouseEvent *event)
{
    // Start dragging tracks if we've dragged far enough.
    if (QApplication::startDragDistance() < (d->dragStartPos - event->pos()).manhattanLength())
        startDrag(Qt::MoveAction);
}

void TrackView::dragEnterEvent(QDragEnterEvent *event)
{
    // Accept all proposed actions from this widget.  The track model will
    // filter out unacceptable actions later.
    if (this == event->source()) {
        d->dragging = true;
        event->acceptProposedAction();
    }
}

void TrackView::dragMoveEvent(QDragMoveEvent *event)
{
    // Update drop row and redraw.
    d->updateDropRow(event->pos());
    setDirtyRegion(rect());
}

void TrackView::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);

    // Turn off the dragging flag and redraw so the drop indicator goes away.
    d->dragging = false;
    setDirtyRegion(rect());
}

void TrackView::dropEvent(QDropEvent *event)
{
    // Drop mime data into the track model.
    d->updateDropRow(event->pos());
    const QStringList formats = event->mimeData()->formats();
    const QString mimeType = model()->mimeTypes().last();
    if (formats.contains(mimeType)) {
        IModel *model = IModel::instance();
        QByteArray b = event->mimeData()->data(mimeType);
        QDataStream stream(&b, QIODevice::ReadOnly);
        int fromRow = -1;
        QList<int> fromRows;
        while (!stream.atEnd()) {
            stream >> fromRow;
            fromRows.append(fromRow);
        }
        int toRow = d->dropRow;
        if (!fromRows.contains(toRow)) {
            const QModelIndex trackListIndex = model->listIndex(Ac::TrackItem);
            QList<IModelItem*> items;
            bool commandBegun = false;
            foreach (int row, fromRows) {
                if (row == toRow)
                    continue;
                if (!commandBegun) {
                    IEditor::instance()->beginCommand();
                    commandBegun = true;
                }
                items.append(model->takeItem(row, trackListIndex));
                if (row < toRow)
                    --toRow;
            }
            foreach (IModelItem *item, items)
                model->insertItem(item, toRow, trackListIndex);
            if (commandBegun)
                IEditor::instance()->endCommand();
        }
    }

    d->dragging = false;

    // Clear current index and redraw.
    setCurrentIndex(QModelIndex());
    setDirtyRegion(rect());
}

void TrackView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    const QAbstractItemModel *m = model();
    const QModelIndex root_index = rootIndex();

    // Get the row height (assuming all rows are the same height).
    const int row_h = rowHeight(m->index(0, 0, root_index));

    // Update the vertical scrollbar range.
    const QWidget *vport = viewport();
    if (row_h)
        verticalScrollBar()->setRange(0, (((m->rowCount(root_index) + 1) * row_h) - vport->height()) / row_h);

    // Set the column widths.
    const int colorColumnWidth = row_h;
    setColumnWidth(0, colorColumnWidth);
    setColumnWidth(1, vport->width() - (colorColumnWidth + buttonColumnWidth + buttonColumnWidth));
    setColumnWidth(2, buttonColumnWidth);
    setColumnWidth(3, buttonColumnWidth);
}

void TrackView::paintEvent(QPaintEvent *event)
{
    QTreeView::paintEvent(event);

    // Draw the drop indicator if we're dragging track(s).
    if (!d->dragging)
        return;
    QWidget *vport = viewport();
    QPainter painter(vport);
    const int y = d->dropRow * rowHeight(model()->index(0, 0, rootIndex()));
    painter.drawLine(0, y, vport->width(), y);
}

void TrackView::keyReleaseEvent(QKeyEvent *event)
{
    if (Qt::Key_Escape == event->key()) {
        NoteSelectionModel::instance()->clear();
        TrackSelectionModel::instance()->clear();
    }

    QTreeView::keyReleaseEvent(event);
}
