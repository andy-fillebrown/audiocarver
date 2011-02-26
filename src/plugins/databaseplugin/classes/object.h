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

#ifndef OBJECT_H
#define OBJECT_H

#include <databaseplugin/database_global.h>

#include <QtCore/QObject>

namespace Database {

class RootObject;

namespace Internal {
class ObjectPrivate;
} // namespace Internal

class DATABASE_EXPORT Object : public QObject
{
    typedef QObject BaseClassT;
    Q_OBJECT

public:
    Object(QObject *parent = 0);
    virtual ~Object();

    virtual QString classType() const;
    virtual bool isLink() const { return false; }
    virtual bool isRoot() const { return false; }

    bool hasRoot() const { return root() != 0; }
    virtual RootObject *root() const;

    quint64 id() const;
    void setId(quint64 id);

    bool isErased() const;
    virtual void erase();
    virtual void unerase();

    Object *owner() const;
    void setOwner(Object *owner);

    int objectCount() const;
    Object *objectAt(int i) const;
    int indexOfObject(Object *object) const;
    void appendObject(Object *object);
    Object *takeObject(int i);

    virtual void insertObject(int i, Object *object);
    virtual void removeObject(int i);
    virtual void removeAllObjects();
    virtual void moveObject(int from, int to);

    int propertyCount() const;
    int propertyIndex(const QString &name) const;
    QString propertyType(int i) const;
    QString propertyName(int i) const;
    QVariant propertyValue(int i) const;
    void setPropertyValue(int i, const QVariant &value);
    template<typename T> T propertyValue(int i) const { return qVariantValue<T>(propertyValue(i)); }

signals:
    void idChanged(quint64 from, quint64 to, Object *object = 0);

    void erased(Object *object = 0);
    void unerased(Object *object = 0);

    void objectAdded(int i, Object *owner);
    void objectRemoved(int i, Object *owner);
    void objectMoved(int from, int to, Object *owner);

    void propertyChanged(int index, Object *object = 0);

private:
    Q_DISABLE_COPY(Object)
    Internal::ObjectPrivate *d;
};

} // namespace Database

Q_DECLARE_METATYPE(Database::Object*);

#endif // OBJECT_H
