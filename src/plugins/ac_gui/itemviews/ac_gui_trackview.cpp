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

#include "ac_gui_trackview.h"
#include "ac_gui_colordelegate.h"
#include "ac_gui_recordbuttondelegate.h"
//#include "ac_noteselectionmodel.h"
//#include "ac_trackselectionmodel.h"
#include <ac_core_namespace.h>
#include <ac_core_trackmodel.h>
#include <idatabase.h>
#include <ieditor.h>
#include <imodel.h>
#include <imodelitemlist.h>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

using namespace Core;
using namespace Ac;
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

TrackView::TrackView(QWidget *parent)
    :   QTreeView(parent)
    ,   d(new TrackViewPrivate(this))
{
    TrackModel *model = TrackModel::instance();
    setModel(model);
    connect(model, SIGNAL(rowsInserted(const QModelIndex&,int,int)), SLOT(rowsChanged()));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex&,int,int)), SLOT(rowsChanged()));
//    setSelectionModel(TrackSelectionModel::instance());
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
    RecordButtonDelegate *record_button_delegate = new RecordButtonDelegate(this);
    record_button_delegate->setButtonColumnWidth(buttonColumnWidth);
    record_button_delegate->setCustomColumn(3);
    setItemDelegateForColumn(3, record_button_delegate);
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
        IEditor *editor = IEditor::instance();
        if (!from_rows.contains(to_row)) {
            IModelItemList *track_list = IDatabase::instance()->rootItem()->findList(TrackItem);
            QList<IModelItem*> items;
            foreach (int row, from_rows) {
                if (row == to_row)
                    continue;
                if (!editor->isInCommand())
                    editor->beginCommand();
                items.append(track_list->takeAt(row));
                if (row < to_row)
                    --to_row;
            }
            foreach (IModelItem *item, items)
                track_list->insert(to_row, item);
            if (editor->isInCommand())
                editor->endCommand();
        }
    }
    d->dragging = false;

    // Clear the current index and redraw.
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
    setColumnWidth(1, viewport->width() - (color_column_width + buttonColumnWidth + buttonColumnWidth));
    setColumnWidth(2, buttonColumnWidth);
    setColumnWidth(3, buttonColumnWidth);
}

void TrackView::paintEvent(QPaintEvent *event)
{
    QTreeView::paintEvent(event);

    // Draw the drop indicator if we're dragging a track.
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
    case Qt::Key_Right:
        // Doing nothing here keeps the view from moving to the left when the
        // right arrow key is pressed.
        return;
    case Qt::Key_Escape:
//        NoteSelectionModel::instance()->clear();
//        TrackSelectionModel::instance()->clear();
        break;
    default:
        break;
    }
    QTreeView::keyPressEvent(event);
}

void TrackView::rowsChanged()
{
    setDirtyRegion(rect());
    resizeEvent(0);
}