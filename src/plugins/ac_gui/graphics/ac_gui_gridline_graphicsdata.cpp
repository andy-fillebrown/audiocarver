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

#include "ac_gui_gridline_graphicsdata.h"
#include "ac_gui_graphicstextnode.h"
#include <ac_core_constants.h>
#include <mi_core_utilities.h>
#include <imodeldata.h>
#include <QApplication>
#include <QFont>

using namespace Ac;
using namespace Mi;

namespace GridLine {

const QFont &GraphicsData::gridLabelFont()
{
    static QFont font;
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        font = QApplication::font();
    }
    return font;
}

Qt::PenStyle GraphicsData::gridLinePenStyle()
{
    return Qt::DotLine;
}

Qt::PenStyle GraphicsData::gridLineExtensionPenStyle()
{
    return Qt::DotLine;
}

GraphicsData::GraphicsData(IAggregate *aggregate)
    :   Base::GraphicsEntity(aggregate)
    ,   _labelSceneRootNode(0)
    ,   _labelSceneTextNode(0)
{
    _labelSceneRootNode = new GraphicsNode;
    _labelSceneTextNode = new GraphicsTextNode(_labelSceneRootNode);
    _labelSceneTextNode->setFont(gridLabelFont());
}

GraphicsData::~GraphicsData()
{
    delete _labelSceneTextNode;
    delete _labelSceneRootNode;
}

void GraphicsData::update(int role, const QVariant &value)
{
    switch (role) {
    case VisibilityRole:
        _labelSceneRootNode->setVisible(qvariant_cast<bool>(value));
        break;
    case LabelRole:
        _labelSceneTextNode->setText(qvariant_cast<QString>(value));
        break;
    }
}

}
