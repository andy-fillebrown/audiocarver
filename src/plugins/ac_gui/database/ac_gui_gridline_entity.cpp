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

#include "ac_gui_gridline_entity.h"
#include "ac_gui_graphicsitem.h"
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <QApplication>
#include <QFont>

using namespace Ac;
using namespace Mi;

namespace GridLine {

const QFont &Entity::gridLabelFont()
{
    static QFont font;
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        font = QApplication::font();
    }
    return font;
}

Qt::PenStyle Entity::gridLinePenStyle()
{
    return Qt::DotLine;
}

Qt::PenStyle Entity::gridLineExtensionPenStyle()
{
    return Qt::DotLine;
}

Entity::~Entity()
{
    delete _labelSceneTextItem;
    delete _labelSceneRootItem;
}

IUnknown *Entity::initialize()
{
    _labelSceneRootItem = new GraphicsItem;
    _labelSceneTextItem = new GraphicsTextItem(_labelSceneRootItem);
    _labelSceneTextItem->setFont(gridLabelFont());
    return Object::Entity::initialize();
}

void Entity::update(int role)
{
    switch (role) {
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        _labelSceneRootItem->setVisible(data->get<bool>(VisibilityRole));
    }   break;
    case LabelRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        _labelSceneTextItem->setText(data->get<QString>(LabelRole));
    }   break;
    }
    Object::Entity::update(role);
}

bool Entity::isVisible() const
{
    return _labelSceneRootItem->isVisible();
}

}
