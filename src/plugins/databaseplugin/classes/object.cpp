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

#include "object.h"

#include "list.h"
#include "root.h"

#include <QtCore/QChildEvent>
#include <QtCore/QMetaProperty>
#include <QtCore/QVariant>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

using namespace Database;

Object::Object(QObject *parent)
    :   QObject(parent)
{}

QString Object::className() const
{
    QString className = metaObject()->className();
    return root()->normalizeClassName(className);
}

Root *Object::root() const
{
    if (isRoot())
        return qobject_cast<Root*>(const_cast<Object*>(this));
    Object *parent = qobject_cast<Object*>(this->parent());
    if (parent)
        return parent->root();
    return 0;
}

void Object::setId(const QString &id)
{
    if (this->id() == id && !id.isEmpty())
        return;
    Root *root = this->root();
    if (root && !id.startsWith("~"))
        setObjectName(root->getUniqueId(this, id));
    else
        setObjectName(id);
}

void Object::erase()
{
    if (isErased())
        return;
    QString id = this->id();
    id.prepend("~");
    setId(id);
    emit erased();
}

void Object::unerase()
{
    if (!isErased())
        return;
    QString id = this->id();
    if (id.at(0) == '~')
        id.remove(0, 1);
    setId(id);
    emit unerased();
}

/*!
  \todo Document.
  */
int Object::propertyCount() const
{
    return metaObject()->propertyCount();
}

/*!
  \todo Document.
  */
int Object::propertyIndex(const QString &name) const
{
    return metaObject()->indexOfProperty(qPrintable(name));
}

/*!
  \todo Document.
  */
QString Object::propertyType(int i) const
{
    return metaObject()->property(i).typeName();
}

/*!
  \todo Document.
  */
QString Object::propertyName(int i) const
{
    return QString(metaObject()->property(i).name());
}

/*!
  \todo Document.
  */
QVariant Object::propertyValue(int i) const
{
    return metaObject()->property(i).read(this);
}

/*!
  \todo Document.
  */
void Object::setPropertyValue(int i, const QVariant &value)
{
    const QMetaObject *metaObject = this->metaObject();
    bool ok = metaObject->property(i).write(this, value);
    if (!ok && value.isValid())
        metaObject->property(i).write(this, QVariant());
}

Object *Object::ioParent(QXmlStreamReader &in) const
{
    Object *root = this->root();
    if (!root || root == this)
        return 0;
    return root->ioParent(in);
}

/*!
  \todo Document.
  */
bool Object::read(QXmlStreamReader &in)
{
    Root *root = this->root();
    Q_ASSERT(root);

    Q_ASSERT(in.name() == className());

    // Read properties.
    QXmlStreamAttributes atts = in.attributes();
    foreach (QXmlStreamAttribute att, atts) {
        QString name = att.name().toString();
        if (name == "id")
            name = "objectName";
        const int i = propertyIndex(name);
        QString type = propertyType(i);
        if (type == "Database::List*")
            continue;
        if (type.endsWith("*")) {
            Object *object = root->findChild<Object*>(att.value().toString());
            Q_ASSERT(object);
            setPropertyValue(i, QVariant::fromValue(object));
        }
        else
            setPropertyValue(i, root->stringToVariant(att.value(), type));
    }

    // Read lists.
    const int count = propertyCount();
    for (int i = 1;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type != "Database::List*")
            continue;
        List *list = propertyValue(i).value<List*>();
        Q_ASSERT(list);
        if (!list)
            return false;
        list->deleteAll();
        while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());
        QString currentListName = in.name().toString();
        while (!in.atEnd()) {
            QXmlStreamReader::TokenType tokenType = in.readNext();
            if (tokenType == QXmlStreamReader::Characters)
                continue;
            const QString currentClassName = in.name().toString();
            if (tokenType == QXmlStreamReader::EndElement && currentClassName == currentListName)
                break;
            if (tokenType == QXmlStreamReader::StartElement) {
                Object *object = root->createObject(currentClassName);
                Q_ASSERT(object);
                if (!object)
                    return false;
                object->setParent(this);
                if (!object->read(in))
                    return false;
                list->append(object);
            }
        }
    }

    return true;
}

/*!
  \todo Document.
  */
void Object::write(QXmlStreamWriter &out) const
{
    Root *root = this->root();
    Q_ASSERT(root);

    out.writeStartElement(className());

    // Write properties.
    const int count = this->propertyCount();
    for (int i = 0;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type == "Database::List*")
            continue;
        QVariant value = propertyValue(i);
        if (type.endsWith("*")) {
            Object *object = value.value<Object*>();
            value = object->id();
        }
        QString name = propertyName(i);
        if (name == "objectName")
            name = "id";
        out.writeAttribute(name, root->variantToString(value));
    }

    // Write lists.
    for (int i = 1;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type != "Database::List*")
            continue;
        QVariant value = propertyValue(i);
        List *list = value.value<List*>();
        out.writeStartElement(propertyName(i));
        for (int i = 0;  i < list->count();  ++i)
            list->at(i)->write(out);
        out.writeEndElement();
    }

    out.writeEndElement();
}

/*!
  \todo Document.
  */
void Object::update(bool recursive)
{
    if (!recursive)
        return;
    const QObjectList &children = this->children();
    foreach (QObject *child, children) {
        Object *object = qobject_cast<Object*>(child);
        if (object)
            object->update(recursive);
    }
}

void Object::childEvent(QChildEvent *event)
{
    if (event->type() == QChildEvent::ChildAdded) {
        Object *object = qobject_cast<Object*>(event->child());
        if (object)
            object->setId();
    }
}
