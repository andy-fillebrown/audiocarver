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

#ifndef AC_TUNING_H
#define AC_TUNING_H

#include <ac_guideline.h>

class AC_DATABASE_EXPORT AcTuning : public AcGuideline
{
    Q_OBJECT

public:
    explicit AcTuning(QObject *parent = 0);
    virtual ~AcTuning();

private:
    Q_DISABLE_COPY(AcTuning)
};

#endif // AC_TUNING_H
