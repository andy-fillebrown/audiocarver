/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#ifndef MI_QIMODEL_H
#define MI_QIMODEL_H

#include <QAbstractItemModel>

#include <mi_core_namespace.h>

class MI_CORE_EXPORT QIModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum { InterfaceType = I::QIModel };

    static QIModel *instance();

    QIModel(QObject *parent)
        :   QAbstractItemModel(parent)
    {}

    virtual int interfaceType() const
    {
        return InterfaceType;
    }

    virtual bool isTypeOfInterface(int interfaceType) const
    {
        return InterfaceType == interfaceType;
    }

    virtual void *queryInterface(int interfaceType) const = 0;
};

#endif // MI_QIMODEL_H
