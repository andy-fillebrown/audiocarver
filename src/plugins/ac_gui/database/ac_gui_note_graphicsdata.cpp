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

#include "ac_gui_note_graphicsdata.h"
#include "ac_gui_namespace.h"
#include <idatabaseobjectfactory.h>
#include <imodeldata.h>
#include <imodelitemlist.h>
#include <mi_core_utilities.h>

using namespace Ac;
using namespace Mi;

namespace Note {

QList<IGraphicsEntity*> GraphicsData::subentities() const
{
    QList<IGraphicsEntity*> subents;

    IModelItem *this_item = QUERY(IModelItem, this);
    if (!this_item)
        return subents;
    IModelItem *pitch_item = this_item->findItem(PitchCurveItem);
    IGraphicsEntity *pitch_entity = QUERY(IGraphicsEntity, pitch_item);
    if (pitch_entity)
        subents.append(pitch_entity);
//    IModelItemList *control_list = this_item->findList(ControlCurveItem);
//    IModelItem *volume_item = control_list->at(-1);
//    IGraphicsEntity *volume_entity = QUERY(IGraphicsEntity, volume_item);
//    if (volume_entity)
//        subents.append(volume_entity);
    IModelItem *velocity_item = this_item->findItem(VelocityItem);
    IGraphicsEntity *velocity_entity = QUERY(IGraphicsEntity, velocity_item);
    if (velocity_entity)
        subents.append(velocity_entity);

    return subents;
}

void GraphicsData::highlight(bool on)
{
    QList<IGraphicsEntity*> subents = subentities();
    foreach (IGraphicsEntity *subent, subents)
        subent->highlight(on);
}

void GraphicsData::update(int role, const QVariant &value)
{
    if (ColorRole == role
            || VolumeRole == role) {
        QList<IGraphicsEntity*> subents = subentities();
        foreach (IGraphicsEntity *subent, subents)
            subent->update(role, value);
    }
}

}
