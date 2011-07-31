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

#ifndef AC_SCENE_COMMON_H
#define AC_SCENE_COMMON_H

#include <QObject>

enum SceneType
{
    PitchScene = 0,
    VolumeScene,
    TimeLabelScene,
    PitchLabelScene,
    VolumeLabelScene,
    SceneTypeCount
};

template <typename ObjectType, typename ItemType>
inline void updateItemsHelper(const QList<ObjectType*> &objects, QList<ItemType*> &items, QObject *parent)
{
    for (int i = 0;  i < objects.count();  ++i) {
        if (items.count() <= i) {
            ItemType *item = new ItemType(objects[i], parent);
            items.append(item);
        } else
            items[i]->setDataObject(objects[i]);
    }
    while (objects.count() < items.count()) {
        delete items.last();
        items.removeLast();
    }
}

#endif // AC_SCENE_COMMON_H
