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

#ifndef AC_IMODEL_H
#define AC_IMODEL_H

#include <mi_iunknown.h>
#include <mi_namespace.h>

class IModelItem;

class QModelIndex;

class IModel : public IUnknown
{
public:
    enum { Type = Mi::ModelInterface };

    virtual IModelItem *itemFromIndex(const QModelIndex &index) const = 0;
};

#endif // AC_IMODEL_H
