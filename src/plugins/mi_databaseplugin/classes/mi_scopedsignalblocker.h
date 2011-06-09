/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#ifndef MI_SCOPEDSIGNALBLOCKER_H
#define MI_SCOPEDSIGNALBLOCKER_H

#include <QObject>

#include <mi_database_global.h>

class MI_DATABASE_EXPORT MiScopedSignalBlocker
{
public:
    MiScopedSignalBlocker(QObject *object) : object(object) { object->blockSignals(true); }
    virtual ~MiScopedSignalBlocker() { object->blockSignals(false); }

private:
    QObject *object;
};

#endif // MI_SCOPEDSIGNALBLOCKER_H
