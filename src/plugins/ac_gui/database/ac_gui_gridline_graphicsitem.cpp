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

#include "ac_gui_gridline_graphicsitem.h"
#include "ac_gui_graphicstextnode.h"
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <QApplication>
#include <QFont>

using namespace Ac;
using namespace Mi;

namespace GridLine {

const QFont &GraphicsItem::gridLabelFont()
{
    static QFont font;
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        font = QApplication::font();
    }
    return font;
}

Qt::PenStyle GraphicsItem::gridLinePenStyle()
{
    return Qt::DotLine;
}

Qt::PenStyle GraphicsItem::gridLineExtensionPenStyle()
{
    return Qt::DotLine;
}

IUnknown *GraphicsItem::initialize()
{
    _labelSceneRootNode = new GraphicsNode;
    _labelSceneTextNode = new GraphicsTextNode(_labelSceneRootNode);
    _labelSceneTextNode->setFont(gridLabelFont());
    return Object::GraphicsEntity::initialize();
}

GraphicsItem::~GraphicsItem()
{
    delete _labelSceneTextNode;
    delete _labelSceneRootNode;
}

void GraphicsItem::setColor(int color)
{
    labelSceneTextNode()->setColor(color);
}

void GraphicsItem::update(int role)
{
    switch (role) {
    case VisibilityRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        _labelSceneRootNode->setVisible(data->get<bool>(VisibilityRole));
    }   break;
    case LabelRole: {
        IModelData *data = query<IModelData>(this);
        if (!data)
            return;
        _labelSceneTextNode->setText(data->get<QString>(LabelRole));
    }   break;
    }
}

}
