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

#include "ac_gui_model_databaseupdater.h"
#include <idatabase.h>

namespace Model {

DatabaseUpdater::DatabaseUpdater()
    :   Base::ModelWatcher(ISession::instance())
{}

void DatabaseUpdater::beginChangeData(IModelItem *item, int role)
{
    IDatabase::instance()->setDirty(true);
}

void DatabaseUpdater::endChangeData(IModelItem *item, int role)
{
    IDatabase::instance()->setDirty(true);
}

void DatabaseUpdater::endInsertItem(IModelItem *list, int index)
{
    IDatabase::instance()->setDirty(true);
}

void DatabaseUpdater::endRemoveItem(IModelItem *list, int index)
{
    IDatabase::instance()->setDirty(true);
}

}
