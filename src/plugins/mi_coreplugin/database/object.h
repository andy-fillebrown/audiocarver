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

#ifndef MI_OBJECT_H
#define MI_OBJECT_H

#include <QObject>
#include <aggregate.h>
#include <mi_core_global.h>
#include <QMetaType>

namespace Database {

class IComponent;

class Object : protected QObject
{
    Q_OBJECT

public:
    QString id() const
    {
        return objectName();
    }

    void setId(const QString &id_= QString());

    void addComponent(IComponent *component);

    template <typename T>
    T *query() const
    {
        return query<T>(const_cast<Object*>(this));
    }

    template <typename T>
    static T *query(Object *object)
    {
        return Aggregation::query<T>(object);
    }

signals:
    void idWillChange();
    void idChanged();

private:
    Q_DISABLE_COPY(Object)
    Q_ENABLE_QUERY(Object)
    friend class Component;
};

} // namespace Database

Q_DECLARE_METATYPE(Database::Object*)

#endif // MI_OBJECT_H
