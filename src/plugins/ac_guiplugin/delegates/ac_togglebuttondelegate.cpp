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

#include "ac_togglebuttondelegate.h"

#include <mi_ieditor.h>

#include <QMouseEvent>
#include <QPainter>

class ToggleButtonDelegatePrivate
{
public:
    int buttonColumnWidth;

    ToggleButtonDelegatePrivate()
        :   buttonColumnWidth(0)
    {}
};

ToggleButtonDelegate::ToggleButtonDelegate(QObject *parent)
    :   Delegate(parent)
    ,   d(new ToggleButtonDelegatePrivate)
{}

ToggleButtonDelegate::~ToggleButtonDelegate()
{
    delete d;
}

void ToggleButtonDelegate::setButtonColumnWidth(int width)
{
    d->buttonColumnWidth = width;
}

void ToggleButtonDelegate::setPainterColors(QPainter *painter, const QModelIndex &index) const
{
    if (index.data().toBool())
        painter->setBrush(QBrush(Qt::SolidPattern));
}

bool ToggleButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    if (customColumn() != index.column())
        return false;

    // Toggle the model data if we got a left button mouse double-click.
    if (QEvent::MouseButtonDblClick != event->type())
        return false;
    const QMouseEvent *e = static_cast<const QMouseEvent*>(event);
    if (Qt::LeftButton == e->button()) {
        IEditor *editor = IEditor::instance();
        editor->beginCommand();
        model->setData(index, !index.data().toBool(), Qt::DisplayRole);
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

    // Draw a circle and fill it if the model data is true (i.e. the button
    // is pressed).
    painter->save();

    setPainterColors(painter, index);

    QRect rect = option.rect;
    rect.setWidth(d->buttonColumnWidth);
    QPoint ctr = rect.center();
    ctr.ry() += 1;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(ctr, 2, 2);

    painter->restore();
}
