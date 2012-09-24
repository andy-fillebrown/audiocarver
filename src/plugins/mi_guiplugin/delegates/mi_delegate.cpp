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

#include "mi_delegate.h"

class DelegatePrivate
{
public:
    int customColumn;

    DelegatePrivate()
        :   customColumn(-1)
    {}
};

Delegate::Delegate(QObject *parent)
    :   QStyledItemDelegate(parent)
    ,   d(new DelegatePrivate)
{}

Delegate::~Delegate()
{
    delete d;
}

int Delegate::customColumn() const
{
    return d->customColumn;
}

void Delegate::setCustomColumn(int column)
{
    d->customColumn = column;
}
