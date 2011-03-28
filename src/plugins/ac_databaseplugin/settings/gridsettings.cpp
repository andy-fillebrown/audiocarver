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

#include "gridsettings.h"

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class GridSettingsData
{
public:
    bool visible;

    GridSettingsData()
        :   visible(false)
    {}
};

} // namespace Internal
} // namespace AudioCarver

GridSettings::GridSettings(QObject *parent)
    :   Database::Object(parent)
    ,   d(new GridSettingsData)
{}

GridSettings::~GridSettings()
{
    delete d;
}

bool GridSettings::visible() const
{
    return d->visible;
}

void GridSettings::setVisible(bool visible)
{
    if (d->visible == visible)
        return;
    d->visible = visible;
    emit propertyChanged(propertyIndex("visible"));
}
