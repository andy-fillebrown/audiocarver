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

#ifndef MI_UTILITIES_H
#define MI_UTILITIES_H

#include "mi_core_global.h"
#include <QString>

MI_CORE_EXPORT QString applicationTreeDirectory();

inline QString intToColorString(int color)
{
    return QString("#%1").arg(color, 6, 16, QChar('0'));
}

inline int colorStringToInt(QString color)
{
    return color.remove("#").toInt(0, 16);
}

#endif
