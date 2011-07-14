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

#include "mi_link.h"
#include <mi_root.h>

namespace Private {

class MiLinkData {
public:
    MiLink *q;
    QString linkId;
    MiObject *linkedObject;

    MiLinkData(MiLink *q)
        :   q(q)
        ,   linkedObject(0)
    {}

    void updateLinkedObject()
    {
        linkedObject = q->root()->findChild<MiObject*>(linkId);
    }
};

} // namespace Private

using namespace Private;

MiLink::MiLink(QObject *parent)
    :   MiObject(parent)
    ,   d(new MiLinkData(this))
{}

MiLink::~MiLink()
{
    delete d;
}

const QString &MiLink::linkId() const
{
    return d->linkId;
}

void MiLink::setLinkId(const QString &id)
{
    if (d->linkId == id)
        return;
    d->linkId = id;
    d->updateLinkedObject();
    emit propertyChanged(LinkId);
}

MiObject *MiLink::linkedObject() const
{
    return d->linkedObject;
}

void MiLink::setLinkedObject(MiObject *object)
{
    setLinkId(object->id());
}

void MiLink::update(bool recursive)
{
    Q_UNUSED(recursive);

    d->updateLinkedObject();
}
