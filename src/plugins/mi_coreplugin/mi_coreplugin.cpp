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
#include <mi_object.h>
#include <mi_objectlist.h>
#include <pluginmanager.h>
#include <QtPlugin>
#include <QVariant>

using namespace Private;

bool MiCorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
//    qRegisterMetaType<MiObject*>();
//    qRegisterMetaType<MiObjectList*>();
    qRegisterMetaType<MiTestObjectList*>();

    MiTestDataObject *test = new MiTestDataObject(this);
    MiTestObjectList *list = test->property("list").value<MiTestObjectList*>();
    Q_ASSERT(list);
    list->append(new MiTestObject);
    list->append(new MiTestObject);
    qDebug() << list->asQList().count();
    int i = 0;
    foreach (MiTestObject *testObject, list->asQList()) {
        Q_ASSERT(testObject);
        qDebug() << i;
        ++i;
    }

    return true;
}

Q_EXPORT_PLUGIN(MiCorePlugin)
