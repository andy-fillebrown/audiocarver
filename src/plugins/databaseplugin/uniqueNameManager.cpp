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

#include "uniqueNameManager.h"

#include <QtCore/QList>

namespace Database {
namespace Internal {

struct NameSet
{
    QString name;
    QList<uint> ids;
};

static NameSet invalidNameSet;

class UniqueNameManagerPrivate
{
public:
    UniqueNameManagerPrivate() {}
    ~UniqueNameManagerPrivate() {}

    bool contains(const QString &name)
    {
        foreach (const NameSet &ns, nameSets) {
            if (ns.name == name) {
                return true;
            }
        }
        return false;
    }

    void add(const QString &name, uint &id)
    {
        if (contains(name)) {
            NameSet ns = nameSet(name);
            if (ns.ids.contains(id))
            {
                id = ns.ids.last() + 1;
                ns.ids.append(id);
            } else {
                for (int i = 0;  i < ns.ids.size();  ++i) {
                    if (id < ns.ids.at(i)) {
                        ns.ids.insert(i, id);
                        return;
                    }
                }
            }
        } else {
            NameSet ns;
            ns.name = name;
            ns.ids.append(id);
        }
    }

    void remove(const QString &name, uint id)
    {
        for (int i = 0;  i < nameSets.size();  ++i) {
            NameSet &ns = nameSets[i];
            if (name == ns.name) {
                ns.ids.removeOne(id);
                if (ns.ids.isEmpty()) {
                    nameSets.removeAt(i);
                    return;
                }
            }
        }
    }

protected:
    const NameSet &nameSet(const QString &name) const
    {
        foreach (const NameSet &nameSet, nameSets) {
            if (nameSet.name == name) {
                return nameSet;
            }
        }
        Q_ASSERT(false && "Name set not found");
        return invalidNameSet;
    }

private:
    QList<NameSet> nameSets;
};

} // namespace Internal
} // namespace Database

using namespace Database;
using namespace Database::Internal;

UniqueNameManager::UniqueNameManager()
    :   d(new UniqueNameManagerPrivate)
{
}

UniqueNameManager::~UniqueNameManager()
{
    delete d;
    d = 0;
}

void UniqueNameManager::addName(QString &name)
{
    QStringList split = name.split(".");
    name = split.first();
    bool idOk = false;
    uint id = split.last().toUInt(&idOk);
    if (!idOk)
        id = 1;
    d->add(name, id);
    name = name + "." + QString(id);
}

void UniqueNameManager::removeName(const QString &name)
{
    const uint id = name.split(".").last().toUInt();
    d->remove(name, id);
}
