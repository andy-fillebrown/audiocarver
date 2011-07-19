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

#ifndef AC_PITCHLINE_H
#define AC_PITCHLINE_H

#include <ac_gridline.h>

class AC_CORE_EXPORT AcPitchLine : public AcGridLine
{
    Q_OBJECT
    Q_DISABLE_COPY(AcPitchLine)

public:
    typedef AcGridLine::Properties Properties;

    explicit AcPitchLine(QObject *parent = 0)
        :   AcGridLine(parent)
    {}

    virtual ~AcPitchLine()
    {}
};

#endif // AC_PITCHLINE_H
