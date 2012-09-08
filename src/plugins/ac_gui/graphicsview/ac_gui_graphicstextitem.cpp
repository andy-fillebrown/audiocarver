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

#include "ac_gui_graphicstextitem.h"
#include <QFont>

GraphicsTextItem::GraphicsTextItem(QGraphicsItem *parent)
    :   GraphicsItem(parent)
    ,   _textItem(new QGraphicsTextItem(this))
{
    _textItem->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    _textItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

QColor GraphicsTextItem::color() const
{
    return _textItem->defaultTextColor();
}

void GraphicsTextItem::setColor(const QColor &color)
{
    _textItem->setDefaultTextColor(color);
}

QFont GraphicsTextItem::font() const
{
    return _textItem->font();
}

void GraphicsTextItem::setFont(const QFont &font)
{
    _textItem->setFont(font);
}

QString GraphicsTextItem::text() const
{
    return _textItem->toPlainText();
}

void GraphicsTextItem::setText(const QString &text)
{
    _textItem->setPlainText(text);
}
