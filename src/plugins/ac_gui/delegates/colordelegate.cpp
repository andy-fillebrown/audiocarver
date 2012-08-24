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

#include "colordelegate.h"
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>

bool ColorDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (customColumn() != index.column())
        return false;

    // We're only interested in left button mouse double-clicks.
    if (QEvent::MouseButtonDblClick != event->type())
        return false;
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    if (Qt::LeftButton != mouse_event->button())
        return false;

    // Open a color dialog and set the track's color if the user didn't cancel the dialog.
    QColorDialog *dialog = new QColorDialog(index.data().value<QColor>(), qobject_cast<QWidget*>(parent()));
    dialog->exec();
    QColor color = dialog->selectedColor();
    if (color.isValid())
        model->setData(index, color);
    return true;
}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (customColumn() != index.column()) {
        Delegate::paint(painter, option, index);
        return;
    }

    // Pass a bogus index to paint highlighting.
    Delegate::paint(painter, option, index.model()->index(0, 0));

    // Draw the color box.
    const QColor color = index.data().value<QColor>();
    QRect rect = option.rect;
    rect.setWidth(rect.height());
    painter->save();
    painter->setPen(color);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect.adjusted(1, 1, -2, -2));
    painter->restore();
}
