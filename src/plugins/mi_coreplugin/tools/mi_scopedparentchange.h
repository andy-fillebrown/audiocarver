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

#include <mi_database_object.h>

namespace Database {

class ScopedParentChange
{
    Object *_object;
    Mi::NotificationFlags _notificationFlags;

public:
    ScopedParentChange(Object *object, Mi::NotificationFlags notificationFlags = Mi::NotifyModel)
        :   _object(object)
        ,   _notificationFlags(notificationFlags)
    {
        _object->parentAboutToBeChanged(_object, _notificationFlags);
    }

    ~ScopedParentChange()
    {
        _object->parentChanged(_object, _notificationFlags);
    }
};

} // namespace Database

#endif // MI_SCOPEDPARENTCHANGE_H
