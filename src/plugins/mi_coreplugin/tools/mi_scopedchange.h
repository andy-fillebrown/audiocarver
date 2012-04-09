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

#ifndef MI_SCOPEDCHANGE_H
#define MI_SCOPEDCHANGE_H

class DataObject;

class IModel;
class IModelData;

class ScopedChange
{
    IModelData *_modelData;
    int _role;

public:
    ScopedChange(DataObject *dataObject, int role);
    ~ScopedChange();
};

#define Q_MI_SCOPED_CHANGE(role) ScopedChange scoped_change(this, role);

#endif // MI_SCOPEDCHANGE_H
