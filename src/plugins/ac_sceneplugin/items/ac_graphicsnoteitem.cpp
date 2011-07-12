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

#include "ac_graphicsnoteitem.h"
#include <ac_note.h>
#include <QGraphicsPathItem>

using namespace Private;

namespace Private {

class AcGraphicsNoteItemData
{
public:
    AcGraphicsNoteItem *q;
    AcNote *note;
    QGraphicsPathItem *scoreItem;
    QGraphicsPathItem *controlItem;

    AcGraphicsNoteItemData(AcGraphicsNoteItem *q)
        :   q(q)
        ,   note(0)
        ,   scoreItem(new QGraphicsPathItem)
        ,   controlItem(new QGraphicsPathItem)
    {}

    virtual ~AcGraphicsNoteItemData()
    {
        delete controlItem;
        delete scoreItem;
    }
};

} // namespace Private

AcGraphicsNoteItem::AcGraphicsNoteItem(AcNote *note, QObject *parent)
    :   QObject(parent)
    ,   d(new AcGraphicsNoteItemData(this))
{
    setDatabaseObject(note);
}

AcGraphicsNoteItem::~AcGraphicsNoteItem()
{
    delete d;
}

void AcGraphicsNoteItem::setDatabaseObject(AcNote *note)
{
    if (d->note == note)
        return;
    d->note = note;
}

bool AcGraphicsNoteItem::isVisible() const
{
    return d->scoreItem->isVisible();
}

void AcGraphicsNoteItem::show()
{
    d->scoreItem->show();
    d->controlItem->show();
}

void AcGraphicsNoteItem::hide()
{
    d->scoreItem->hide();
    d->controlItem->hide();
}

void AcGraphicsNoteItem::updateNoteProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
