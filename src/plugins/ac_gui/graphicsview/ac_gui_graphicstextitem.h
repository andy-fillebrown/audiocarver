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

#ifndef AC_GUI_GRAPHICSTEXTITEM_H
#define AC_GUI_GRAPHICSTEXTITEM_H

#include "ac_gui_graphicsitem.h"

class GraphicsTextItem : public GraphicsItem
{
    QGraphicsTextItem *_textItem;

public:
    GraphicsTextItem(QGraphicsItem *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);
    QFont font() const;
    void setFont(const QFont &font);
    QString text() const;
    void setText(const QString &text);
};

#endif
