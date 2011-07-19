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
#include <aggregate.h>
#include <mi_database.h>
#include <mi_ipropertybag.h>

using namespace Aggregation;
using namespace Private;

MiDatabase *MiObject::database() const
{
    if (isDatabase())
        return qobject_cast<MiDatabase*>(const_cast<MiObject*>(this));
    MiObject *parent = qobject_cast<MiObject*>(this->parent());
    if (parent)
        return parent->database();
    return 0;
}

void MiObject::emitPropertyAboutToBeChanged(int propertyIndex)
{
    IPropertyBag *pb = query<IPropertyBag>(this);
    if (!pb)
        return;
    pb->emit propertyAboutToBeChanged(pb->propertyValue(propertyIndex), propertyIndex);
}

void MiObject::emitPropertyChanged(int propertyIndex)
{
    IPropertyBag *pb = query<IPropertyBag>(this);
    if (!pb)
        return;
    pb->emit propertyChanged(pb->propertyValue(propertyIndex), propertyIndex);
}

//bool MiWritableObject::read(QXmlStreamReader &in)
//{
//    MiRoot *root = this->root();
//    Q_ASSERT(root);
//    Q_ASSERT(in.name() == className());

//    // Read properties.
//    QXmlStreamAttributes atts = in.attributes();
//    foreach (QXmlStreamAttribute att, atts) {
//        QString name = att.name().toString();
//        if (name == "id")
//            name = "objectName";
//        const int i = propertyIndex(name);
//        QString type = propertyType(i);
//        if (type == "MiObjectList*")
//            continue;
//        if (type.endsWith("*")) {
//            MiObject *object = root->findChild<MiObject*>(att.value().toString());
//            if (object)
//                setPropertyValue(i, QVariant::fromValue(object));
//        }
//        else
//            setPropertyValue(i, root->stringToVariant(att.value(), type));
//    }

//    // Read constant read-only objects.
//    const int count = propertyCount();
//    for (int i = 1;  i < count;  ++i) {
//        QString type = propertyType(i);
//        if (type.endsWith("*")) {
//            if (type == "MiObjectList*")
//                continue;
//            if (propertyIsReadOnly(i)) {
//                while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());
//                MiObject *object = propertyValue(i).value<MiObject*>();
//                if (!object->read(in))
//                    return false;
//            }
//        }
//    }

//    // Read lists.
//    for (int i = 1;  i < count;  ++i) {
//        QString type = propertyType(i);
//        if (type != "MiObjectList*")
//            continue;
//        while (in.readNext() != QXmlStreamReader::StartElement && !in.atEnd());
//        QString currentListName = in.name().toString();
//        MiObjectList *list = propertyValue(i).value<MiObjectList*>();
//        Q_ASSERT(list);
//        if (!list)
//            return false;
//        if (!list->isConstant())
//            list->deleteAll();
//        blockSignals(true);
//        while (!in.atEnd()) {
//            QXmlStreamReader::TokenType tokenType = in.readNext();
//            if (tokenType == QXmlStreamReader::Characters)
//                continue;
//            const QString currentClassName = in.name().toString();
//            if (tokenType == QXmlStreamReader::EndElement && currentClassName == currentListName)
//                break;
//            if (tokenType == QXmlStreamReader::StartElement) {
//                MiObject *object = 0;
//                if (list->isConstant())
//                    object = findObject(currentClassName);
//                else
//                    object = createObject(currentClassName);
//                Q_ASSERT(object);
//                if (!object)
//                    return false;
//                if (!object->read(in))
//                    return false;
//            }
//        }
//        blockSignals(false);
//        emit propertyChanged(i);
//    }
//    return true;
//}

//void MiWritableObject::write(QXmlStreamWriter &out) const
//{
//    MiRoot *root = this->root();
//    Q_ASSERT(root);
//    out.writeStartElement(className());

//    // Write properties.
//    const int count = this->propertyCount();
//    for (int i = 0;  i < count;  ++i) {
//        QString type = propertyType(i);
//        if (type == "MiObjectList*")
//            continue;
//        QVariant value = propertyValue(i);
//        if (type.endsWith("*")) {
//            MiObject *object = value.value<MiObject*>();
//            if (propertyIsReadOnly(i))
//                continue;
//            if (object)
//                value = object->id();
//            else
//                value = "";
//        }
//        QString name = propertyName(i);
//        if (name == "objectName") {
//            if (value.toString().isEmpty())
//                continue;
//            name = "id";
//        }
//        out.writeAttribute(name, root->variantToString(value));
//    }

//    // Write constant read-only objects.
//    for (int i = 0;  i < count;  ++i) {
//        QString type = propertyType(i);
//        if (type.endsWith("*")) {
//            if (type == "MiObjectList*")
//                continue;
//            if (propertyIsReadOnly(i)) {
//                QVariant value = propertyValue(i);
//                MiObject *object = value.value<MiObject*>();
//                object->write(out);
//            }
//        }
//    }

//    // Write lists.
//    for (int i = 1;  i < count;  ++i) {
//        QString type = propertyType(i);
//        if (type != "MiObjectList*")
//            continue;
//        QVariant value = propertyValue(i);
//        MiObjectList *list = value.value<MiObjectList*>();
//        QString name = propertyName(i);
//        out.writeStartElement(name);
//        for (int i = 0;  i < list->count();  ++i)
//            list->at(i)->write(out);
//        out.writeEndElement();
//    }
//    out.writeEndElement();
//}
