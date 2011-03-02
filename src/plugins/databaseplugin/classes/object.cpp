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

#include "object.h"
#include "rootobject.h"

#include <QtCore/QMetaProperty>
#include <QtCore/QVariant>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

using namespace Database;

Object::Object(QObject *parent)
    :   BaseClassT(parent)
{
}

Object::~Object()
{
}

QString Object::className() const
{
    QString className = metaObject()->className();
    return root()->normalizeClassName(className);
}

RootObject *Object::root() const
{
    if (this->isRoot())
        return qobject_cast<RootObject*>(const_cast<Object*>(this));

    Object *parent = qobject_cast<Object*>(this->parent());
    if (parent)
        return parent->root();

    return 0;
}

void Object::setId(const QString &id)
{
    if (this->id() == id || id.isEmpty())
        return;
    RootObject *root = this->root();
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

    emit erased(this);
}

void Object::unerase()
{
    if (!isErased())
        return;

    QString id = this->id();
    if (id.at(0) == '~')
        id.remove(0, 1);
    setId(id);

    emit unerased(this);
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
    return QString( metaObject()->property(i).name());
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
    RootObject *root = this->root();
    Q_ASSERT(root);

    Q_ASSERT(in.name() == className());

    // Read properties.
    QXmlStreamAttributes atts = in.attributes();

    foreach (QXmlStreamAttribute att, atts) {
        const int i = propertyIndex(att.name().toString());
        QString propertyName = this->propertyName(i);

        if (propertyName.endsWith("*")) {
            RootObject *root = this->root();
            Q_ASSERT(root);
            Object *object = root->findChild<Object*>(att.value().toString());
            Q_ASSERT(object);
            setPropertyValue(i, QVariant::fromValue(object));
        }
        else
            setPropertyValue(i, att.value().toString());
    }

    // Read children.
    while (!in.atEnd()) {
        QXmlStreamReader::TokenType tokenType = in.readNext();

        if (tokenType == QXmlStreamReader::Characters)
            continue;

        const QString currentClassName = in.name().toString();

        if (tokenType == QXmlStreamReader::EndElement && currentClassName == className())
            return true;

        if (tokenType == QXmlStreamReader::StartElement) {
            Object *object = root->createObject(currentClassName);
            Q_ASSERT(object);
            if (!object)
                return false;

            object->setParent(this);

            if (!object->read(in))
                return false;
        }
    }

    return true;
}

/*!
  \todo Document.
  */
void Object::write(QXmlStreamWriter &out) const
{
    RootObject *root = this->root();
    Q_ASSERT(root);

    out.writeStartElement(className());

    // Write properties.
    const int propertyCount = this->propertyCount();
    for (int i = 1;  i < propertyCount;  ++i) {
        QString name = propertyName(i);
        QVariant value = propertyValue(i);

        if (propertyName(i).endsWith("*")) {
            Object *object = value.value<Object*>();
            value = object->id();
        }
        out.writeAttribute(name, value.toString());
    }

    // Write children.
    const QObjectList &children = this->children();
    foreach (QObject *child, children) {
        Object *object = qobject_cast<Object*>(child);
        if (object)
            object->write(out);
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
