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

#ifndef AC_GRAPHICSITEM_H
#define AC_GRAPHICSITEM_H

#include <QObject>
#include <ac_scene_common.h>
#include <ac_scene_global.h>

class MiObject;
class QGraphicsItem;

namespace Private {

class AcGraphicsItemData
{
public:
    MiObject *databaseObject;

    AcGraphicsItemData() : databaseObject(0) {}
    virtual ~AcGraphicsItemData() {}
};

class AcGraphicsItemPrivate;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsItem : public QObject
{
    Q_OBJECT

protected:
    AcGraphicsItem(Private::AcGraphicsItemData &dd, QObject *parent = 0);

public:
    virtual ~AcGraphicsItem();

    void setDatabaseObject(MiObject *object);

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const = 0;

    bool isVisible() const;
    void show();
    void hide();

    void addItem(AcGraphicsItem *item);
    template <typename T> void addItems(const QList<T*> &items) { foreach (AcGraphicsItem *item, items) addItem(item); }

protected slots:
    virtual void updateDatabaseObjectProperty(const QString &propertyName) = 0;

private:
    Q_DISABLE_COPY(AcGraphicsItem)
    Q_DECLARE_PRIVATE(Private::AcGraphicsItem)

protected:
    Private::AcGraphicsItemData *d_ptr;
};

#endif // AC_GRAPHICSITEM_H
