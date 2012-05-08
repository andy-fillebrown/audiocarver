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

#include <mi_database_object.h>

namespace Database {

class ScopedDataChange
{
    Object *_object;
    int _role;
    Mi::NotificationFlags _notificationFlags;

public:
    ScopedDataChange(Object *object, int role, Mi::NotificationFlags notificationFlags = Mi::NotifyModel)
        :   _object(object)
        ,   _role(role)
        ,   _notificationFlags(notificationFlags)
    {
        _object->dataAboutToBeChanged(_object, _role, _notificationFlags);
    }

    ~ScopedDataChange()
    {
        _object->dataChanged(_object, _role, _notificationFlags);
    }
};

} // namespace Database

#endif // MI_SCOPEDDATACHANGE_H
