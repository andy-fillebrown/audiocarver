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

#include "ac_graphicsitem.h"
#include <mi_object.h>
#include <QGraphicsItem>

using namespace Private;

namespace Private {

class AcGraphicsItemPrivate : public AcGraphicsItemData
{};

} // namespace Private

AcGraphicsItem::AcGraphicsItem(AcGraphicsItemData &dd, QObject *parent)
    :   QObject(parent)
    ,   d_ptr(&dd)
{
    Q_D(AcGraphicsItem);
    setDatabaseObject(d->databaseObject);
}

AcGraphicsItem::~AcGraphicsItem()
{
    delete d_ptr;
}

void AcGraphicsItem::setDatabaseObject(MiObject *databaseObject)
{
    Q_D(AcGraphicsItem);
    if (d->databaseObject == databaseObject)
        return;
    if (d->databaseObject)
        d->databaseObject->disconnect(this);
    d->databaseObject = databaseObject;
    if (d->databaseObject) {
        connect(d->databaseObject, SIGNAL(propertyChanged(QString)), SLOT(updateDatabaseObjectProperty(QString)));
        for (int i = 0;  i < d->databaseObject->propertyCount();  ++i)
            updateDatabaseObjectProperty(d->databaseObject->propertyName(i));
    } else
        hide();
}

bool AcGraphicsItem::isVisible() const
{
    for (int i = 0;  i < SceneTypeCount;  ++i)
        if (sceneItem(SceneType(i))->isVisible())
            return true;
    return false;
}

void AcGraphicsItem::show()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = sceneItem(SceneType(i));
        if (item)
            item->show();
    }
}

void AcGraphicsItem::hide()
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *item = sceneItem(SceneType(i));
        if (item)
            item->hide();
    }
}

void AcGraphicsItem::addItem(AcGraphicsItem *item)
{
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        QGraphicsItem *parentSceneItem = sceneItem(SceneType(i));
        QGraphicsItem *sceneItem = item->sceneItem(SceneType(i));
        if (parentSceneItem && sceneItem)
            sceneItem->setParentItem(parentSceneItem);
    }
}
