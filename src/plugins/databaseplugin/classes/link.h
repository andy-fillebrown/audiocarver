/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef LINK_H
#define LINK_H

#include "object.h"

namespace Database {

namespace Internal {
class LinkPrivate;
} // namespace Internal

class DATABASE_EXPORT Link : public Object
{
    typedef Object BaseClassT;
    Q_OBJECT

public:
    Link(QObject *parent = 0);
    virtual ~Link();

    virtual bool isLink() const { return true; }

    quint64 linkId() const;
    void setLinkId(quint64 id);

private:
    Q_DISABLE_COPY(Link)
    Internal::LinkPrivate *d;
};

} // namespace Database

Q_DECLARE_METATYPE(Database::Link*);

#endif // LINK_H
