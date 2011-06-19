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

#include "mi_object.h"
#include <mi_objectlist.h>
#include <mi_root.h>
#include <QChildEvent>
#include <QMetaProperty>
#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

MiObject::MiObject(QObject *parent)
    :   QObject(parent)
{}

QString MiObject::className() const
{
    QString className = metaObject()->className();
    return root()->normalizeClassName(className);
}

MiRoot *MiObject::root() const
{
    if (isRoot())
        return qobject_cast<MiRoot*>(const_cast<MiObject*>(this));
    MiObject *parent = qobject_cast<MiObject*>(this->parent());
    if (parent)
        return parent->root();
    return 0;
}

void MiObject::setId(const QString &id)
{
    if (this->id() == id && !id.isEmpty())
        return;
    MiRoot *root = this->root();
    if (root && !id.startsWith("~"))
        setObjectName(root->getUniqueId(this, id));
    else
        setObjectName(id);
}

void MiObject::erase()
{
    if (isErased())
        return;
    QString id = this->id();
    id.prepend("~");
    setId(id);
    emit erased();
}

void MiObject::unerase()
{
    if (!isErased())
        return;
    QString id = this->id();
    if (id.at(0) == '~')
        id.remove(0, 1);
    setId(id);
    emit unerased();
}

int MiObject::propertyCount() const
{
    return metaObject()->propertyCount();
}

int MiObject::propertyIndex(const QString &name) const
{
    return metaObject()->indexOfProperty(qPrintable(name));
}

bool MiObject::propertyIsReadOnly(int i) const
{
    return !metaObject()->property(i).isWritable();
}

QString MiObject::propertyType(int i) const
{
    return metaObject()->property(i).typeName();
}

QString MiObject::propertyName(int i) const
{
    return QString(metaObject()->property(i).name());
}

QVariant MiObject::propertyValue(int i) const
{
    return metaObject()->property(i).read(this);
}

void MiObject::setPropertyValue(int i, const QVariant &value)
{
    const QMetaObject *metaObject = this->metaObject();
    bool ok = metaObject->property(i).write(this, value);
    if (!ok && value.isValid())
        metaObject->property(i).write(this, QVariant());
}

MiObject *MiObject::ioParent(QXmlStreamReader &in) const
{
    MiObject *root = this->root();
    if (!root || root == this)
        return 0;
    return root->ioParent(in);
}

bool MiObject::read(QXmlStreamReader &in)
{
    MiRoot *root = this->root();
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
        if (type == "MiObjectList*")
            continue;
        if (type.endsWith("*")) {
            MiObject *object = root->findChild<MiObject*>(att.value().toString());
            if (object)
                setPropertyValue(i, QVariant::fromValue(object));
        }
        else
            setPropertyValue(i, root->stringToVariant(att.value(), type));
    }

    // Read constant read-only objects.
    foreach (QXmlStreamAttribute att, atts) {
        QString name = att.name().toString();
        const int i = propertyIndex(name);
        QString type = propertyType(i);
        if (type.endsWith("*")) {
            if (type == "MiObjectList*")
                continue;
            if (propertyIsReadOnly(i)) {
                MiObject *object = propertyValue(i).value<MiObject*>();
                if (!object->read(in))
                    return false;
            }
        }
    }

    // Read lists.
    const int count = propertyCount();
    for (int i = 1;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type != "MiObjectList*")
            continue;
        while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());
        QString currentListName = in.name().toString();
        MiObjectList *list = propertyValue(i).value<MiObjectList*>();
        Q_ASSERT(list);
        if (!list)
            return false;
        blockSignals(true);
        if (!list->isConstant())
            list->deleteAll();
        while (!in.atEnd()) {
            QXmlStreamReader::TokenType tokenType = in.readNext();
            if (tokenType == QXmlStreamReader::Characters)
                continue;
            const QString currentClassName = in.name().toString();
            if (tokenType == QXmlStreamReader::EndElement && currentClassName == currentListName)
                break;
            if (tokenType == QXmlStreamReader::StartElement) {
                MiObject *object = 0;
                if (list->isConstant())
                    object = findObject(currentClassName);
                else
                    object = createObject(currentClassName);
                Q_ASSERT(object);
                if (!object)
                    return false;
                if (!list->isConstant())
                    object->setParent(this);
                if (!object->read(in))
                    return false;
            }
        }
        blockSignals(false);
        emit propertyChanged(currentListName);
    }
    return true;
}

void MiObject::write(QXmlStreamWriter &out) const
{
    MiRoot *root = this->root();
    Q_ASSERT(root);
    out.writeStartElement(className());

    // Write properties.
    const int count = this->propertyCount();
    for (int i = 0;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type == "MiObjectList*")
            continue;
        QVariant value = propertyValue(i);
        if (type.endsWith("*")) {
            MiObject *object = value.value<MiObject*>();
            if (propertyIsReadOnly(i))
                continue;
            if (object)
                value = object->id();
            else
                value = "";
        }
        QString name = propertyName(i);
        if (name == "objectName") {
            if (value.toString().isEmpty())
                continue;
            name = "id";
        }
        out.writeAttribute(name, root->variantToString(value));
    }

    // Write constant read-only objects.
    for (int i = 0;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type.endsWith("*")) {
            if (type == "MiObjectList*")
                continue;
            if (propertyIsReadOnly(i)) {
                QVariant value = propertyValue(i);
                MiObject *object = value.value<MiObject*>();
                object->write(out);
            }
        }
    }

    // Write lists.
    for (int i = 1;  i < count;  ++i) {
        QString type = propertyType(i);
        if (type != "MiObjectList*")
            continue;
        QVariant value = propertyValue(i);
        MiObjectList *list = value.value<MiObjectList*>();
        QString name = propertyName(i);
        out.writeStartElement(name);
        for (int i = 0;  i < list->count();  ++i)
            list->at(i)->write(out);
        out.writeEndElement();
    }
    out.writeEndElement();
}

void MiObject::update(bool recursive)
{
    if (!recursive)
        return;
    const QObjectList &children = this->children();
    foreach (QObject *child, children) {
        MiObject *object = qobject_cast<MiObject*>(child);
        if (object)
            object->update(recursive);
    }
}

MiObject *MiObject::createObject(const QString &className)
{
    Q_UNUSED(className);
    return 0;
}

MiObject *MiObject::findObject(const QString &className) const
{
    Q_UNUSED(className);
    return 0;
}

void MiObject::childEvent(QChildEvent *event)
{
    if (event->type() == QChildEvent::ChildAdded) {
        MiObject *object = qobject_cast<MiObject*>(event->child());
        if (object)
            object->setId();
    }
}
