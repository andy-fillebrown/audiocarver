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

#ifndef AC_NODE_H
#define AC_NODE_H

#include <glsceneplugin/classes/node.h>

namespace Database {
class Object;
} // namespace Database

namespace AudioCarver {

namespace Internal {
class NodePrivate;
} // namespace Internal

class Node : public GL::Node
{
    Q_OBJECT

public:
    Node(Database::Object *databaseObject, QObject *parent);
    virtual ~Node();

    Database::Object *databaseObject() const;

public slots:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(Node)
    Internal::NodePrivate *d;
};

} // namespace AudioCarver

template <typename T>
QList<T*> ac_updateNodeList_helper(QList<T*> &nodeList,
                                   const QList<Database::Object*> &databaseList,
                                   QObject *parent)
{
    QList<T*> oldNodeList = nodeList;
    nodeList.clear();

    for (int i = 0;  i < databaseList.count();  ++i) {
        Database::Object *dbObj = databaseList.at(i);

        T *node = 0;

        if (i < oldNodeList.count())
            node = oldNodeList.at(i);

        if (node && node->databaseObject() != dbObj) {
            node = 0;

            for (int j = 0;  j < oldNodeList.count();  ++j) {
                if (oldNodeList.at(j)->databaseObject() == dbObj) {
                    node = oldNodeList.at(j);
                    oldNodeList.removeAt(j);
                    break;
                }
            }
        }

        if (!node)
            node = new T(dbObj, parent);

        nodeList.append(node);
    }

    qDeleteAll(oldNodeList);

    return oldNodeList;
}

#endif // AC_NODE_H
