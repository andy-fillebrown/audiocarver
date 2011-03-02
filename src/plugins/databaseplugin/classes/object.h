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

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
class QXmlStreamWriter;
QT_END_NAMESPACE

namespace Database {

class RootObject;

class DATABASE_EXPORT Object : public QObject
{
    typedef QObject BaseClassT;

    Q_OBJECT

public:
    Object(QObject *parent = 0);
    virtual ~Object();

    virtual QString className() const;
    virtual bool isRoot() const { return false; }

    virtual RootObject *root() const;

    QString id() const { return objectName(); }
    virtual void setId(const QString &id);

    bool isErased() const { return id().startsWith("~"); }
    virtual void erase();
    virtual void unerase();

    int propertyCount() const;
    int propertyIndex(const QString &name) const;
    QString propertyType(int i) const;
    QString propertyName(int i) const;
    QVariant propertyValue(int i) const;
    void setPropertyValue(int i, const QVariant &value);
    template<typename T> T propertyValue(int i) const { return qVariantValue<T>(propertyValue(i)); }

    virtual Object *ioParent(QXmlStreamReader &in) const;
    virtual bool read(QXmlStreamReader &in);
    virtual void write(QXmlStreamWriter &out) const;
    virtual void update(bool recursive = false);

signals:
    void childAdded(Object *child, Object *parent);
    void childRemoved(Object *child, Object *parent);

    void erased(Object *object = 0);
    void unerased(Object *object = 0);

    void propertyChanged(int index, Object *object = 0);

private:
    Q_DISABLE_COPY(Object)
};

} // namespace Database

Q_DECLARE_METATYPE(Database::Object*);

#endif // OBJECT_H
