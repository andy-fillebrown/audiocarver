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

#ifndef MI_SCOPEDPARENTCHANGE_H
#define MI_SCOPEDPARENTCHANGE_H

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>
#include <mi_imodelitemwatcher.h>

namespace Database {

class ScopedParentChange
{
    const IModelItem *_item;
    const QList<IModelItemWatcher*> *_watchers;
    Mi::NotificationFlags _notificationFlags;

public:
    ScopedParentChange(const IAggregator *aggregator, Mi::NotificationFlags notificationFlags = Mi::NotifyModel)
        :   _item(const_query<IModelItem>(aggregator))
        ,   _watchers(_item ? _item->watchers() : 0)
        ,   _notificationFlags(notificationFlags)
    {
        if (!_item)
            return;
        if (_watchers) {
            foreach (IModelItemWatcher *watcher, *_watchers)
                watcher->parentAboutToBeChanged(_item);
        }
        if (Mi::NotifyModel & _notificationFlags) {
            IModel *model = query<IModel>(IDatabase::instance());
            if (model)
                model->beginChangeParent(_item);
        }
    }

    ~ScopedParentChange()
    {
        if (!_item)
            return;
        if (_watchers) {
            foreach (IModelItemWatcher *watcher, *_watchers)
                watcher->parentChanged(_item);
        }
        if (Mi::NotifyModel & _notificationFlags) {
            IModel *model = query<IModel>(IDatabase::instance());
            if (model)
                model->endChangeParent(_item);
        }
    }
};

} // namespace Database

#endif // MI_SCOPEDPARENTCHANGE_H
