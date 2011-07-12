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

class AcGraphicsNoteItemPrivate : public AcGraphicsItemData
{
public:
    QGraphicsPathItem *scoreItem;
    QGraphicsPathItem *controlItem;

    AcGraphicsNoteItemPrivate(AcNote *note)
        :   scoreItem(new QGraphicsPathItem)
        ,   controlItem(new QGraphicsPathItem)
    {
        databaseObject = note;
    }

    virtual ~AcGraphicsNoteItemPrivate()
    {
        delete controlItem;
        delete scoreItem;
    }
};

} // namespace Private

AcGraphicsNoteItem::AcGraphicsNoteItem(AcNote *note, QObject *parent)
    :   AcGraphicsItem(*(new AcGraphicsNoteItemPrivate(note)), parent)
{}

AcGraphicsNoteItem::~AcGraphicsNoteItem()
{}

QGraphicsItem *AcGraphicsNoteItem::sceneItem(SceneType sceneType) const
{
    Q_D(const AcGraphicsNoteItem);
    switch (sceneType) {
    case ScoreScene:
        return d->scoreItem;
    case ControlScene:
        return d->controlItem;
    default:
        break;
    }
    return 0;
}

void AcGraphicsNoteItem::updateDatabaseObjectProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
