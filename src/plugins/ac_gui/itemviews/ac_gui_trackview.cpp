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

#include "ac_gui_trackview.h"
#include "ac_gui_colordelegate.h"
#include "ac_gui_togglebuttondelegate.h"
#include <ac_core_namespace.h>
#include <ac_core_trackmodel.h>
#include <idatabase.h>
#include <ieditor.h>
#include <igraphicsitem.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iselectionset.h>
#include <iundomanager.h>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QMimeData>

using namespace Ac;
using namespace Ac::Core;
using namespace Qt;

static const int buttonColumnWidth = 12;

class TrackViewPrivate
{
public:
    TrackView *q;
    QPoint dragStartPos;
    int dropRow;
    uint dragging : 1;

    TrackViewPrivate(TrackView *q)
        :   q(q)
        ,   dropRow(-1)
        ,   dragging(false)
    {}

    void updateDropRow(const QPoint &pos)
    {
        dropRow = q->indexAt(pos).row();

        // If the drop row is -1 then we've gone past the last track.
        if (dropRow < 0)
            dropRow = q->model()->rowCount(q->rootIndex());
    }
};

TrackView *instance = 0;

TrackView *TrackView::instance()
{
    return ::instance;
}

TrackView::TrackView(QWidget *parent)
    :   QTreeView(parent)
    ,   d(new TrackViewPrivate(this))
{
    ::instance = this;
    TrackModel *model = TrackModel::instance();
    setModel(model);
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(update()));
    connect(model, SIGNAL(rowsInserted(const QModelIndex&,int,int)), SLOT(update()));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)), SLOT(update()));
    setHeaderHidden(true);
    setRootIsDecorated(false);
    setAutoScroll(false);
    setHorizontalScrollBarPolicy(ScrollBarAlwaysOff);
    setSelectionMode(ExtendedSelection);
    setAcceptDrops(true);
    setDragEnabled(true);
    setAllColumnsShowFocus(true);
    ColorDelegate *color_delegate = new ColorDelegate(this);
    color_delegate->setCustomColumn(0);
    setItemDelegateForColumn(0, color_delegate);
    ToggleButtonDelegate *toggle_button_delegate = new ToggleButtonDelegate(this);
    toggle_button_delegate->setButtonColumnWidth(buttonColumnWidth);
    toggle_button_delegate->setCustomColumn(2);
    setItemDelegateForColumn(2, toggle_button_delegate);
}

void TrackView::mousePressEvent(QMouseEvent *event)
{
    // Save the event position.  We might be dragging tracks later.
    if (LeftButton == event->button())
        d->dragStartPos = event->pos();

    QModelIndex index = indexAt(event->pos());
    const int index_column = index.column();
    if (1 == index_column)
        // The mouse is over the "name" column.  Pass the event to the base
        // class to select the track.
        QTreeView::mousePressEvent(event);
    else if (0 == index_column) {
        // The mouse is over the "color" column.  Pass the event to the
        // delegate.
        QAbstractItemDelegate *delegate = itemDelegate(index);
        if (delegate)
            delegate->editorEvent(event, model(), QStyleOptionViewItem(), index);
    } else {
        // The mouse is over one of the toggle buttons.
        QModelIndexList selected_indexes = selectionModel()->selectedRows(index_column);
        QAbstractItemModel *model = this->model();
        if (selected_indexes.contains(index)) {
            // The mouse is over one of the selected tracks.  Pass the event to
            // each selected track's delegate.
            foreach (QModelIndex selected_index, selected_indexes) {
                QAbstractItemDelegate *delegate = itemDelegate(selected_index);
                if (delegate)
                    delegate->editorEvent(event, model, QStyleOptionViewItem(), selected_index);
            }
        } else {
            // The mouse is not over one of the selected tracks.  Pass the
            // event to the delegate.
            QAbstractItemDelegate *delegate = itemDelegate(index);
            if (delegate)
                delegate->editorEvent(event, model, QStyleOptionViewItem(), index);
        }
    }
}

void TrackView::mouseMoveEvent(QMouseEvent *event)
{
    // Do not start dragging if the mouse press was not over the "name" column.
    if (1 != indexAt(d->dragStartPos).column())
        return;

    // Start dragging tracks if we've dragged far enough.
    if (QApplication::startDragDistance() < (d->dragStartPos - event->pos()).manhattanLength())
        startDrag(MoveAction);
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
    // Turn off the dragging flag and redraw the view so the drop indicator
    // disappears.
    d->dragging = false;
    setDirtyRegion(rect());
}

void TrackView::dropEvent(QDropEvent *event)
{
    d->updateDropRow(event->pos());
    const QStringList formats = event->mimeData()->formats();
    const QString mime_type = model()->mimeTypes().last();
    if (formats.contains(mime_type)) {
        QByteArray mime_data = event->mimeData()->data(mime_type);
        QDataStream mime_stream(&mime_data, QIODevice::ReadOnly);
        int from_row = -1;
        QList<int> from_rows;
        while (!mime_stream.atEnd()) {
            mime_stream >> from_row;
            from_rows.append(from_row);
        }
        int to_row = d->dropRow;
        IUndoManager *undo_manager = IUndoManager::instance();
        if (!from_rows.contains(to_row)) {
            IModelItem *track_list = IDatabase::instance()->rootItem()->findItem(TrackListItem);
            QList<IModelItem*> items;
            foreach (int row, from_rows) {
                if (row == to_row)
                    continue;
                if (!undo_manager->isInCommand())
                    undo_manager->beginCommand();
                items.append(track_list->takeItemAt(row));
                if (row < to_row)
                    --to_row;
            }
            foreach (IModelItem *item, items)
                track_list->insertItem(to_row, item);
            if (undo_manager->isInCommand())
                undo_manager->endCommand();
        }
    }
    d->dragging = false;

    // Clear the current index, and redraw.
    setCurrentIndex(QModelIndex());
    setDirtyRegion(rect());
}

void TrackView::resizeEvent(QResizeEvent *event)
{
    const QAbstractItemModel *model = this->model();
    const QModelIndex root_index = rootIndex();

    // Get the first row's height.
    const int row_height = rowHeight(model->index(0, 0, root_index));

    // Update the vertical scrollbar range assuming every row is the same
    // height.
    const QWidget *viewport = this->viewport();
    if (row_height)
        verticalScrollBar()->setRange(0, (((model->rowCount(root_index) + 1) * row_height) - viewport->height()) / row_height);

    // Set the column widths.
    const int color_column_width = row_height;
    setColumnWidth(0, color_column_width);
    setColumnWidth(1, viewport->width() - (color_column_width + buttonColumnWidth));
    setColumnWidth(2, buttonColumnWidth);
}

void TrackView::paintEvent(QPaintEvent *event)
{
    QTreeView::paintEvent(event);

    // Draw the drop indicator if a track is being dragged.
    if (!d->dragging)
        return;
    QWidget *viewport = this->viewport();
    QPainter painter(viewport);
    const int y = d->dropRow * rowHeight(model()->index(0, 0, rootIndex()));
    painter.drawLine(0, y, viewport->width(), y);
}

void TrackView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Key_Right:
        // Do nothing here to keep the view from moving to the left when the
        // right arrow key is pressed.
        return;
    case Key_Escape:
        IEditor::instance()->currentSelection()->clear();
        selectionModel()->clearSelection();
        break;
    default:
        break;
    }
    QTreeView::keyPressEvent(event);
}

void TrackView::update()
{
    setDirtyRegion(rect());
    resizeEvent(0);
}

void TrackView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    IEditor *editor = IEditor::instance();
    if (!selected.indexes().isEmpty())
        editor->currentSelection()->clear();
    ISelectionSet *track_ss = editor->currentSelection(TrackItem);
    IModelItem *tracks = IDatabase::instance()->rootItem()->findItem(TrackListItem);
    foreach (QModelIndex index, selected.indexes())
        track_ss->append(query<IGraphicsItem>(tracks->itemAt(index.row())));
    foreach (QModelIndex index, deselected.indexes())
        track_ss->remove(query<IGraphicsItem>(tracks->itemAt(index.row())));
    QTreeView::selectionChanged(selected, deselected);
}
