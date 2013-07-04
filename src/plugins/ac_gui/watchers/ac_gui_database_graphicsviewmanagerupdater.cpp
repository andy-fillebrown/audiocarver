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

#include "ac_gui_database_graphicsviewmanagerupdater.h"
#include "ac_gui_graphicsviewmanager.h"
#include <isession.h>

namespace Database {

GraphicsViewManagerUpdater::GraphicsViewManagerUpdater()
    :   Base::DatabaseWatcher(ISession::instance())
{}

void GraphicsViewManagerUpdater::beginRead(IDatabase *database)
{
    GraphicsViewManager::instance()->databaseAboutToBeRead();
}

void GraphicsViewManagerUpdater::endRead(IDatabase *database)
{
    GraphicsViewManager::instance()->databaseRead();
}

void GraphicsViewManagerUpdater::beginWrite(IDatabase *database)
{
    GraphicsViewManager::instance()->databaseAboutToBeWritten();
}

}
