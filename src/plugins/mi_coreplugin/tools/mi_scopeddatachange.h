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

#ifndef MI_SCOPEDDATACHANGE_H
#define MI_SCOPEDDATACHANGE_H

#include <mi_dataobject.h>

class DataObject;

class ScopedDataChange
{
    DataObject *_dataObject;
    int _role;
    Mi::NotificationFlags _notificationFlags;

public:
    ScopedDataChange(DataObject *dataObject)
        :   _dataObject(dataObject)
    {}

    void init(int role, Mi::NotificationFlags notificationFlags = Mi::NotifyModel)
    {
        _role = role;
        _notificationFlags = notificationFlags;

        _dataObject->dataAboutToBeChanged(_dataObject, _role, _notificationFlags);
    }

    ~ScopedDataChange()
    {
        _dataObject->dataChanged(_dataObject, _role, _notificationFlags);
    }
};

#define Q_SCOPED_DATA_CHANGE(Params) \
    ScopedDataChange data_change_notifier(this); \
    data_change_notifier.init Params ;

#endif // MI_SCOPEDDATACHANGE_H
