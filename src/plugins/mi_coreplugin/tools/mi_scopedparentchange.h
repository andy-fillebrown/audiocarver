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

#include <mi_dataobject.h>

class DataObject;

class ScopedParentChange
{
    DataObject *_dataObject;
    Mi::NotificationFlags _notificationFlags;

public:
    ScopedParentChange(DataObject *dataObject)
        :   _dataObject(dataObject)
    {}

    void init(Mi::NotificationFlags notificationFlags = Mi::NotifyModel)
    {
        _notificationFlags = notificationFlags;
        _dataObject->parentAboutToBeChanged(_dataObject, _notificationFlags);
    }

    ~ScopedParentChange()
    {
        _dataObject->parentChanged(_dataObject, _notificationFlags);
    }
};

#define Q_SCOPED_PARENT_CHANGE(Params) \
    ScopedParentChange parent_change_notifier(this); \
    parent_change_notifier.init Params ;

#endif // MI_SCOPEDPARENTCHANGE_H
