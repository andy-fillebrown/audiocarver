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

#include <mi_core_global.h>
#include <QObject>
#include <QVariant>

class MiObject;

class MI_CORE_EXPORT MiObjectPrivate
{
public:
    MiObject *q_ptr;
    quint32 updateFlags;

    MiObjectPrivate(MiObject *q)
        :   q_ptr(q)
        ,   updateFlags(0)
    {}

    virtual ~MiObjectPrivate()
    {}

    void addChild(MiObject *child);
    void removeChild(MiObject *child);
};

class MI_CORE_EXPORT MiObject : protected QObject
{
    Q_OBJECT

public:
    enum UpdateFlag {
        UpdateObject = 0x1,
        UpdateChildren = 0x2,
        UpdateAll = 0xf
    };
    Q_DECLARE_FLAGS(UpdateFlags, UpdateFlag)

    MiObject()
        :   d_ptr(new MiObjectPrivate(this))
    {}

    virtual ~MiObject()
    {
        delete d_ptr;
    }

    QString className() const
    {
        return metaObject()->className();
    }

    int propertyCount() const
    {
        return metaObject()->propertyCount();
    }

    int propertyIndex(const QString propertyName) const
    {
        return metaObject()->indexOfProperty(qPrintable(propertyName));
    }

    QString propertyType(int i) const;
    bool isPropertyWritable(int i) const;
    QString propertyName(int i) const;
    QVariant propertyValue(int i) const;
    void setPropertyValue(int i, const QVariant &value);

    UpdateFlags updateFlags() const
    {
        return UpdateFlags(d_ptr->updateFlags);
    }

public slots:
    void setUpdateFlag(UpdateFlag flag = UpdateAll, bool enabled = true)
    {
        if (enabled)
            setUpdateFlags(UpdateFlags(d_ptr->updateFlags) | flag);
        else
            setUpdateFlags(UpdateFlags(d_ptr->updateFlags) & ~flag);
    }

    virtual void setUpdateFlags(const UpdateFlags &flags = UpdateAll)
    {
        if (flags == UpdateFlags(d_ptr->updateFlags))
            return;
        d_ptr->updateFlags = flags;
        emit updateFlagsChanged(UpdateFlags(d_ptr->updateFlags));
    }

signals:
    void aboutToChange(int i = -1, const QVariant &value = QVariant());
    void changed(int i = -1, const QVariant &value = QVariant());
    void updateFlagsChanged(const UpdateFlags &flags = UpdateAll);

protected:
    MiObject(MiObjectPrivate &dd)
        :   d_ptr(&dd)
    {}

    MiObjectPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(MiObject)
    Q_DISABLE_COPY(MiObject)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MiObject::UpdateFlags)

inline void MiObjectPrivate::addChild(MiObject *child)
{
    child->setParent(q_ptr);
}

inline void MiObjectPrivate::removeChild(MiObject *child)
{
    Q_ASSERT(q_ptr == child->parent());
    child->setParent(0);
}

#endif // MI_OBJECT_H
