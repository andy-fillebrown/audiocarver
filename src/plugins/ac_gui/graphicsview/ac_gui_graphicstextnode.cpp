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

#include "ac_gui_graphicstextnode.h"
#include <QFont>

GraphicsTextNode::GraphicsTextNode(QGraphicsItem *parent)
    :   GraphicsNode(parent)
    ,   _text(new QGraphicsTextItem(this))
{
    _text->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    _text->setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

QColor GraphicsTextNode::color() const
{
    return _text->defaultTextColor();
}

void GraphicsTextNode::setColor(const QColor &color)
{
    _text->setDefaultTextColor(color);
}

QFont GraphicsTextNode::font() const
{
    return _text->font();
}

void GraphicsTextNode::setFont(const QFont &font)
{
    _text->setFont(font);
}

QString GraphicsTextNode::text() const
{
    return _text->toPlainText();
}

void GraphicsTextNode::setText(const QString &text)
{
    _text->setPlainText(text);
}
