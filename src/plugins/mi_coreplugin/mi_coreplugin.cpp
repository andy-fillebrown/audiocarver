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

#include "mi_coreplugin.h"
#include <mi_objectlist.h>
#include <pluginmanager.h>
#include <QtPlugin>

using namespace Private;

bool MiCorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    qRegisterMetaType<MiObject*>();
    qRegisterMetaType<MiObjectList*>();

    qRegisterMetaType<Object*>();

    Parent *parent = new Parent;
    Child *child = new Child;
    parent->addChild(child);
    child->change();

    ParentB *parentB = new ParentB;
    ChildB *childB = new ChildB;
    parentB->addChild(childB);
    childB->change();

//    parentB->addChild(parent); // should print message and assert

    const QList<ChildB*> &childrenB = parentB->children();
    Q_UNUSED(childrenB);

    parent = parentB;
    const QList<Child*> &children = parent->children();
    Q_UNUSED(children);

    qDebug() << "childB property count ==" << childB->propertyCount();
    qDebug() << "childB property 1 name ==" << childB->propertyName(1);
    qDebug() << "childB property 1 value ==" << childB->propertyValue(1);

    return true;
}

Q_EXPORT_PLUGIN(MiCorePlugin)
