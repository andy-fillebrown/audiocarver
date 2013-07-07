/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_CORE_DATABASE_H
#define AC_CORE_DATABASE_H

#include <mi_core_base_database.h>
#include "ac_core_global.h"
#include <QString>

class IAggregate;

namespace Ac {
namespace Core {

class AC_CORE_EXPORT Database : public Base::Database
{
    QString _fileName;
    IAggregate *_score;
    uint _reading : 1;
    uint _dirty : 1;

public:
    Database();
    ~Database();

protected:
    IModelItem *rootItem() const;
    const QString &fileExtension() const;
    const QString &fileFilter() const;
    QString fileName() const;
    void read(const QString &fileName);
    void write(const QString &fileName);
    bool isReading() const;
    void setDirty(bool dirty);
    bool isDirty() const;
    void reset();
};

}
}

#endif
