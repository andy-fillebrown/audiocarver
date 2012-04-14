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

#include "mi_coreplugin.h"

#include <mi_corenamespace.h>

#include <pluginmanager.h>

#include <QMetaType>
#include <QtPlugin>

void test()
{
}

bool MiCorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    Mi::appendItemDataRole(Mi::ItemTypeRole, "type");
    Mi::appendItemDataRole(Mi::ListTypeRole, "listType");
    Mi::appendItemDataRole(Mi::NameRole, "name");

    test();

    return true;
}

Q_EXPORT_PLUGIN(MiCorePlugin)
