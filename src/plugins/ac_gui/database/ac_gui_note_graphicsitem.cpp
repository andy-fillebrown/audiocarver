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

#include "ac_gui_note_graphicsitem.h"
#include "ac_gui_namespace.h"
#include <idatabaseobjectfactory.h>
#include <imodeldata.h>
#include <imodelitemlist.h>
#include <mi_core_utilities.h>

using namespace Ac;
using namespace Mi;

namespace Note {

IUnknown *GraphicsItem::initialize()
{
    return Object::GraphicsEntity::initialize();
}

QList<IGraphicsEntity*> GraphicsItem::subentities() const
{
    QList<IGraphicsEntity*> subents;

    IModelItem *this_item = query<IModelItem>(this);
    if (!this_item)
        return subents;
    IModelItem *pitch_item = this_item->findItem(PitchCurveItem);
    IGraphicsEntity *pitch_entity = query<IGraphicsEntity>(pitch_item);
    if (pitch_entity)
        subents.append(pitch_entity);
//    IModelItemList *control_list = this_item->findList(ControlCurveItem);
//    IModelItem *volume_item = control_list->at(-1);
//    IGraphicsEntity *volume_entity = query<IGraphicsEntity>(volume_item);
//    if (volume_entity)
//        subents.append(volume_entity);
    IModelItem *velocity_item = this_item->findItem(VelocityItem);
    IGraphicsEntity *velocity_entity = query<IGraphicsEntity>(velocity_item);
    if (velocity_entity)
        subents.append(velocity_entity);

    return subents;
}

void GraphicsItem::setColor(int color)
{
    QList<IGraphicsEntity*> subents = subentities();
    foreach (IGraphicsEntity *subent, subents)
        subent->setColor(color);
}

void GraphicsItem::highlight(bool on)
{
    QList<IGraphicsEntity*> subents = subentities();
    foreach (IGraphicsEntity *subent, subents)
        subent->highlight(on);
    Object::GraphicsEntity::highlight(on);
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case ColorRole: {
        IModelItem *this_item = query<IModelItem>(this);
        IModelItem *list_item = this_item ? this_item->parent() : 0;
        IModelItem *parent_item = list_item ? list_item->parent() : 0;
        IModelData *parent_data = query<IModelData>(parent_item);
        if (parent_data)
            setColor(intFromColor(parent_data->get<QString>(ColorRole)));
    }   break;
    default: {
        QList<IGraphicsEntity*> subents = subentities();
        foreach (IGraphicsEntity *subent, subents)
            subent->update(role);
    } break;
    }
}

}
