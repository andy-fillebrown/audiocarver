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

#ifndef AC_SCENEOBJECT_H
#define AC_SCENEOBJECT_H

#include <QtCore/QObject>

namespace Database {
class Object;
} // namespace Database

namespace AudioCarver {

namespace Internal {
class SceneObjectPrivate;
} // namespace Internal

class SceneObject : public QObject
{
    Q_OBJECT

public:
    SceneObject(Database::Object *databaseObject, QObject *parent);
    virtual ~SceneObject();

    Database::Object *databaseObject() const;

public slots:
    virtual void updateProperty(int index);

private:
    Q_DISABLE_COPY(SceneObject)
    Internal::SceneObjectPrivate *d;
};

} // namespace AudioCarver

template <typename T>
QList<T*> ac_updateSceneList_helper(QList<T*> &sceneList,
                                    const QList<Database::Object*> &databaseList,
                                    QObject *parent)
{
    QList<T*> oldSceneList = sceneList;
    sceneList.clear();

    for (int i = 0;  i < databaseList.count();  ++i) {
        Database::Object *dbObj = databaseList.at(i);

        T *sceneObj = 0;

        if (i < oldSceneList.count())
            sceneObj = oldSceneList.at(i);

        if (sceneObj && sceneObj->databaseObject() != dbObj) {
            sceneObj = 0;

            for (int j = 0;  j < oldSceneList.count();  ++j) {
                if (oldSceneList.at(j)->databaseObject() == dbObj) {
                    sceneObj = oldSceneList.at(j);
                    oldSceneList.removeAt(j);
                    break;
                }
            }
        }

        if (!sceneObj)
            sceneObj = new T(dbObj, parent);

        sceneList.append(sceneObj);
    }

    qDeleteAll(oldSceneList);

    return oldSceneList;
}

#endif // AC_SCENEOBJECT_H
