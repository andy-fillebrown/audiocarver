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
#include <mi_core_global.h>

class MiDatabase;
class MiObject;

namespace Private {

class MiObjectPrivate
{
public:
    MiObject *q_ptr;
    bool erased;

    MiObjectPrivate(MiObject *q = 0)
        :   q_ptr(q)
        ,   erased(false)
    {}

    virtual ~MiObjectPrivate()
    {}

    virtual void erase()
    {
        erased = true;
    }

    virtual void unerase()
    {
        erased = false;
    }
};

} // namespace Private

class MI_CORE_EXPORT MiObject : public QObject
{
    Q_OBJECT

public:
    MiObject(QObject *parent = 0)
        :   QObject(parent)
        ,   d_ptr(new Private::MiObjectPrivate(this))
    {}

protected:
    MiObject(Private::MiObjectPrivate &dd, QObject *parent)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

public:
    virtual ~MiObject()
    {
        delete d_ptr;
    }

    MiDatabase *database() const;

    virtual bool isDatabase() const
    {
        return false;
    }

    virtual bool isWritable() const
    {
        return true;
    }

    bool isErased() const
    {
        return d_ptr->erased;
    }

    virtual void erase()
    {
        if (isErased())
            return;
        beginErase();
        d_ptr->erase();
        endErase();
    }

    virtual void unerase()
    {
        if (!isErased())
            return;
        beginUnerase();
        d_ptr->unerase();
        endUnerase();
    }

    virtual QString className() const;
    int propertyCount() const;
    int propertyIndex(const QString &name) const;
    QString propertyName(int i) const;
    QString propertyType(int i) const;
    bool isPropertyWritable(int i) const;
    QVariant propertyValue(int i) const;
    void setPropertyValue(int i, const QVariant &value);

signals:
    void aboutToBeErased();
    void erased();
    void aboutToBeUnerased();
    void unerased();
    void propertyAboutToBeChanged(const QVariant &value, int i);
    void propertyChanged(const QVariant &value, int i);

protected:
    void beginErase()
    {
        emit aboutToBeErased();
    }

    void endErase()
    {
        emit erased();
    }

    void beginUnerase()
    {
        emit aboutToBeUnerased();
    }

    void endUnerase()
    {
        emit unerased();
    }

private:
    Q_DISABLE_COPY(MiObject)

protected:
    Private::MiObjectPrivate *d_ptr;
};

#endif // MI_OBJECT_H
