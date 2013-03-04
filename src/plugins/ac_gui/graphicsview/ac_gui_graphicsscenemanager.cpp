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

#include "ac_gui_graphicsscenemanager.h"
#include "ac_gui_graphicscontrolscene.h"
#include "ac_gui_graphicscontrollabelscene.h"
#include "ac_gui_namespace.h"
#include "ac_gui_graphicspitchscene.h"
#include "ac_gui_graphicspitchlabelscene.h"
#include "ac_gui_graphicstimelabelscene.h"
#include <idatabase.h>
#include <igraphicsdata.h>
#include <imodel.h>
#include <imodelitem.h>
#include <qdebug.h>

using namespace Ac;

static GraphicsSceneManager *instance = 0;

//GraphicsSceneManager *GraphicsSceneManager::instance()
//{
//    return ::instance;
//}

GraphicsSceneManager::GraphicsSceneManager(QObject *parent)
    :   QObject(parent)
    ,   _controlScene(new GraphicsControlScene(this))
    ,   _controlLabelScene(new GraphicsControlLabelScene(this))
    ,   _pitchScene(new GraphicsPitchScene(this))
    ,   _pitchLabelScene(new GraphicsPitchLabelScene(this))
    ,   _timeLabelScene(new GraphicsTimeLabelScene(this))
{
    // Add the root entity's main graphics items to the scenes.
    IGraphicsData *root_gdata = QUERY(IGraphicsData, IDatabase::instance()->rootItem());
    Q_ASSERT(root_gdata);
    if (!root_gdata)
        qDebug() << Q_FUNC_INFO << "The database root item was not found.";
    for (int i = 0;  i < SceneTypeCount;  ++i) {
        scene(i)->addItem(root_gdata->node(i, MainTransform));
    }
    ::instance = this;
}

QGraphicsScene *GraphicsSceneManager::scene(int type)
{
    switch (type) {
    case ControlScene:
        return _controlScene;
    case ControlLabelScene:
        return _controlLabelScene;
    case PitchScene:
        return _pitchScene;
    case PitchLabelScene:
        return _pitchLabelScene;
    case TimeLabelScene:
        return _timeLabelScene;
    default:
        return 0;
    }
}
