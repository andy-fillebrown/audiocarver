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

#include <mi_ieditor.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>

#include <QApplication>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QStyledItemDelegate>

static const int buttonColumnWidth = 12;

static IEditor *editor()
{
    return IEditor::instance();
}

class Delegate : public QStyledItemDelegate
{
public:
    explicit Delegate(QObject *parent = 0)
        :   QStyledItemDelegate(parent)
    {}

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // Return an empty size.  We're not using it.
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

        // We're only interested in left button mouse clicks.
        if (QEvent::MouseButtonPress != event->type())
            return false;
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (Qt::LeftButton != e->button())
            return false;

        // Open a color dialog at the event's position and set the track's
        // color if the user didn't cancel the dialog.
        QColorDialog *dlg = new QColorDialog(index.data().value<QColor>(), object_cast<QWidget>(parent()));
        dlg->move(dlg->parentWidget()->mapToGlobal(e->pos()));
        dlg->exec();
        QColor color = dlg->selectedColor();
        if (color.isValid())
            model->setData(index, color, Qt::DisplayRole);

        return true;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // Pass a bogus index so "true" or "false" doesn't get painted under
        // the color box.
        Delegate::paint(painter, option, index.model()->index(0, 0));

        // Draw the color box.
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

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        Q_UNUSED(option);

        // Toggle the model data if we got a left button mouse click.
        if (QEvent::MouseButtonPress != event->type())
            return false;
        const QMouseEvent *e = static_cast<const QMouseEvent*>(event);
        if (Qt::LeftButton == e->button()) {
            editor()->beginCommand();
            model->setData(index, !index.data().toBool(), Qt::DisplayRole);
            editor()->endCommand();
        }

        return true;
    }

    virtual void setPainterColors(QPainter *painter, const QModelIndex &index) const
    {
        if (index.data().toBool())
            painter->setBrush(QBrush(Qt::SolidPattern));
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        // Pass a bogus index so "true" or "false" doesn't get painted under
        // the button.
        Delegate::paint(painter, option, index.model()->index(0, 0));

        // Draw a circle and fill it if the model data is true (i.e. the button
        // is pressed).
        painter->save();
        setPainterColors(painter, index);
        painter->setRenderHint(QPainter::Antialiasing);
        QRect rect = option.rect;
        rect.setWidth(buttonColumnWidth);
        painter->drawEllipse(rect.center(), 3, 3);
        painter->restore();
    }
};

class RecordButtonDelegate : public ToggleButtonDelegate
{
public:
    explicit RecordButtonDelegate(QObject *parent = 0)
        :   ToggleButtonDelegate(parent)
    {}

    void setPainterColors(QPainter *painter, const QModelIndex &index) const
    {
        painter->setPen(Qt::red);
        if (index.data().toBool())
            painter->setBrush(QBrush(Qt::red));
    }
};

class TrackViewPrivate
{
public:
    TrackView *q;
    IEditor *editor;
    QPoint dragStartPos;
    quint32 dragging : 32;
    int dropRow;

    TrackViewPrivate(TrackView *q)
        :   q(q)
        ,   editor(IEditor::instance())
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
    setModel(new TrackModel(interfaceToObject_cast<QAbstractItemModel>(IDatabase::instance()->model())));
    setHeaderHidden(true);
    setRootIsDecorated(false);
    setAutoScroll(false);
    setItemDelegateForColumn(0, new ColorDelegate(this));
    setItemDelegateForColumn(2, new ToggleButtonDelegate(this));
    setItemDelegateForColumn(3, new RecordButtonDelegate(this));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(ExtendedSelection);
    setAcceptDrops(true);
    setDragEnabled(true);
    setAllColumnsShowFocus(true);
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
    d->editor->beginCommand();
    model()->dropMimeData(event->mimeData(), event->dropAction(), d->dropRow, 0, QModelIndex());
    d->editor->endCommand();

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
