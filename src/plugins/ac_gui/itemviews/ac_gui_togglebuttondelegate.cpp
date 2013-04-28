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

#include "ac_gui_togglebuttondelegate.h"
#include <ieditor.h>
#include <QMouseEvent>
#include <QPainter>

using namespace Qt;

void ToggleButtonDelegate::setPainterColors(QPainter *painter, const QModelIndex &index) const
{
    if (index.data().toBool())
        painter->setBrush(QBrush(SolidPattern));
}

bool ToggleButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (customColumn() != index.column())
        return false;
    if (QEvent::MouseButtonDblClick != event->type())
        return false;
    const QMouseEvent *mouse_event = static_cast<const QMouseEvent*>(event);
    if (LeftButton == mouse_event->button()) {
        IEditor *editor = IEditor::instance();
        editor->beginCommand();
        model->setData(index, !index.data().toBool(), DisplayRole);
        editor->endCommand();
    }
    return true;
}

void ToggleButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (customColumn() != index.column()) {
        Delegate::paint(painter, option, index);
        return;
    }

    // Pass a bogus index to paint highlighting.
    Delegate::paint(painter, option, index.model()->index(0, 0));

    QRect rect = option.rect;
    painter->save();
    QVariant data = index.data();
    if ("<varies>" == data.value<QString>()) {
        painter->setPen(QPen(black));
        QPoint pos = rect.bottomLeft();
        int offset = (rect.height() - painter->fontMetrics().height());
        pos.ry() -= offset;
        painter->drawText(pos, "<varies>");
    } else {
        // Draw a circle and fill it if the model data is true (i.e. the button
        // is pressed).
        setPainterColors(painter, index);
        rect.setWidth(_buttonColumnWidth);
        QPoint ctr = rect.center();
        ctr.ry() += 1;
        const int radius = rect.width() / 4;
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawEllipse(ctr, radius, radius);
    }
    painter->restore();
}
