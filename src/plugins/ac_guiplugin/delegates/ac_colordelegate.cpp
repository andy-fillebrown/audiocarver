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

#include "ac_colordelegate.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>

bool ColorDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    if (customColumn() != index.column())
        return false;

    // We're only interested in left button mouse double-clicks.
    if (QEvent::MouseButtonDblClick != event->type())
        return false;
    QMouseEvent *e = static_cast<QMouseEvent*>(event);
    if (Qt::LeftButton != e->button())
        return false;

    // Open a color dialog and set the track's color if the user didn't cancel the dialog.
    QColorDialog *dlg = new QColorDialog(index.data().value<QColor>(), object_cast<QWidget>(parent()));
    dlg->exec();
    QColor color = dlg->selectedColor();
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
    painter->save();
    painter->setPen(color);
    painter->setBrush(QBrush(color));
    painter->drawRect(option.rect.adjusted(1, 1, -2, -2));
    painter->restore();
}
