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

//#include <QObject>
//#include <mi_core_global.h>
//#include <QVariant>

//class MiObjectList;
//class MiRoot;
//class QXmlStreamReader;
//class QXmlStreamWriter;

//class MI_CORE_EXPORT MiObject : public QObject
//{
//    Q_OBJECT

//public:
//    enum PropertyIndex
//    {
//        Id = 0,
//        PropertyCount
//    };

//    MiObject(QObject *parent = 0);
//    virtual ~MiObject() {}

//    virtual QString className() const;
//    virtual bool isRoot() const { return false; }
//    virtual MiRoot *root() const;

//    QString id() const { return objectName(); }
//    virtual void setId(const QString &id = "");

//    bool isErased() const { return id().startsWith("~"); }
//    virtual void erase();
//    virtual void unerase();

//    int propertyCount() const;
//    int propertyIndex(const QString &name) const;
//    bool propertyIsReadOnly(int i) const;
//    QString propertyType(int i) const;
//    QString propertyName(int i) const;
//    QVariant propertyValue(int i) const;
//    void setPropertyValue(int i, const QVariant &value);
//    template<typename T> T propertyValue(int i) const { return qVariantValue<T>(propertyValue(i)); }

//    virtual MiObject *ioParent(QXmlStreamReader &in) const;
//    virtual bool read(QXmlStreamReader &in);
//    virtual void write(QXmlStreamWriter &out) const;
//    virtual void update(bool recursive = false);

//    virtual MiObject *createObject(const QString &className);
//    virtual MiObject *findObject(const QString &className) const;

//protected:
//    virtual void childEvent(QChildEvent *event);

//signals:
//    void erased();
//    void unerased();
//    void propertyChanged(int propertyIndex);

//private:
//    Q_DISABLE_COPY(MiObject)
//    friend class MiObjectList;
//};

//Q_DECLARE_METATYPE(MiObject*);

//namespace Private {

//class MI_CORE_EXPORT MiLinkableObjectData
//{
//public:
//    MiLinkableObjectData(MiObject *q) { q->setId(); }
//};

//} // namespace Private

#endif // MI_OBJECT_H
