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

#ifndef AC_GRIDSETTINGS_H
#define AC_GRIDSETTINGS_H

#include <databaseplugin/classes/object.h>

#include <ac_databaseplugin/ac_database_global.h>

namespace AudioCarver {
namespace Internal {

class GridSettingsData;

} // namespace Internal

class AC_DATABASE_EXPORT GridSettings : public Database::Object
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible WRITE setVisible)

public:
    GridSettings(QObject *parent = 0);
private:
    virtual ~GridSettings();
    Q_DISABLE_COPY(GridSettings)

public:
    bool visible() const;
    void setVisible(bool visible);

private:
    Internal::GridSettingsData *d;
};

} // namespace AudioCarver

#endif // AC_GRIDSETTINGS_H
