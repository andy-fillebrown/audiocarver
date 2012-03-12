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

#include "ac_gripmanager.h"

class GripManagerPrivate
{
public:
    GripManager *q;

    GripManagerPrivate(GripManager *q)
        :   q(q)
    {
    }

    void init()
    {
    }

    ~GripManagerPrivate()
    {
    }
};

static GripManager *instance = 0;

GripManager::GripManager(QObject *parent)
    :   QObject(parent)
    ,   d(new GripManagerPrivate(this))
{
    ::instance = this;
    d->init();
}

GripManager::~GripManager()
{
    delete d;
}

GripManager *GripManager::instance()
{
    return ::instance;
}
