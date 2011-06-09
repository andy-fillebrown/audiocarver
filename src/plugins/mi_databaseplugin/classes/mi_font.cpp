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

#include "mi_font.h"
#include <QFont>

using namespace Private;

namespace Private {

class MiFontData
{
public:
    QFont font;

    MiFontData()
        :   font("Arial", 8)
    {}
};

}

MiFont::MiFont(QObject *parent)
    :   MiObject(parent)
    ,   d(new MiFontData)
{}

MiFont::~MiFont()
{
    delete d;
}

QString MiFont::family() const
{
    return d->font.family();
}

void MiFont::setFamily(const QString &family)
{
    if (d->font.family() == family)
        return;
    d->font.setFamily(family);
    emit propertyChanged("family");
}

int MiFont::pointSize() const
{
    return d->font.pointSize();
}

void MiFont::setPointSize(int size)
{
    if (d->font.pointSize() == size)
        return;
    d->font.setPointSize(size);
    emit propertyChanged("pointSize");
}
