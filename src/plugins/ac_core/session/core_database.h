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

#ifndef CORE_DATABASE_H
#define CORE_DATABASE_H

#include <base/database.h>
#include "ac_core_global.h"
#include <QString>

namespace Core {

class AC_CORE_EXPORT Database : public Base::Database
{
    QString _fileName;
    IAggregate *_score;

public:
    Database()
        :   _score(0)
    {}

    IUnknown *initialize();
    ~Database();

protected:
    IAggregate *score() const
    {
        return _score;
    }

    IModelItem *rootItem() const;
    const QString &fileExtension() const;
    const QString &fileFilter() const;
    QString fileName() const;
    void reset();
    void read(const QString &fileName);
    void write(const QString &fileName);
    bool isReading() const;
};

}

#endif
