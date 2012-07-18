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

#ifndef AC_CORE_DATABASE_H
#define AC_CORE_DATABASE_H

#include "mi_core_database.h"

#include <ac_core_global.h>

namespace Ac {

class CorePlugin;

namespace Core {

class Model;

class AC_CORE_EXPORT Database : public Mi::Core::Database
{
    friend class Ac::CorePlugin;
    friend class Model;

    QString _fileName;
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

} // namespace Core
} // namespace Ac

#endif // AC_CORE_DATABASE_H
