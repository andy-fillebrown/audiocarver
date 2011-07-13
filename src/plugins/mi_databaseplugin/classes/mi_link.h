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

#ifndef MI_LINK_H
#define MI_LINK_H

#include <mi_object.h>

namespace Private {

class MiLinkData;

} // namespace Private

class MI_DATABASE_EXPORT MiLink : public MiObject
{
    Q_OBJECT
    Q_PROPERTY(QString linkId READ linkId WRITE setLinkId)

public:
    enum PropertyIndex
    {
        LinkId = MiObject::PropertyCount,
        PropertyCount
    };

    MiLink(QObject *parent = 0);
    virtual ~MiLink();

    const QString &linkId() const;
    void setLinkId(const QString &id);
    MiObject *linkedObject() const;
    void setLinkedObject(MiObject *object);

    virtual void update(bool recursive = false);

private:
    Q_DISABLE_COPY(MiLink)
    Private::MiLinkData *d;
};

Q_DECLARE_METATYPE(MiLink*);

#endif // MI_LINK_H
