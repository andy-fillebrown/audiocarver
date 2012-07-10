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

#ifndef AC_DATABASE_H
#define AC_DATABASE_H

#include "mi_database.h"

#include <ac_coreglobal.h>

namespace Core {
class Model;
} // namespace Database

namespace Ac {

class AC_CORE_EXPORT Database : public Mi::Database
{
    friend class CorePlugin;
    friend class Core::Model;

    IAggregator *_score;

protected:
    Database()
        :   _score(0)
    {}

    IAggregator *init();
    ~Database();

    IAggregator *score() const
    {
        return _score;
    }

    // IDatabase
    const QString &fileExtension() const;
    const QString &fileFilter() const;
    QString fileName() const;
    void reset();
    void read(const QString &fileName);
    void write(const QString &fileName);
    bool isReading() const;

    // IAggregator
    IAggregate *createAggregate(int interfaceType);
};

} // namespace Ac


#endif // AC_DATABASE_H
