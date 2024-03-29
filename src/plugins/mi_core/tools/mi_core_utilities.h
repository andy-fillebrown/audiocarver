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

#ifndef MI_CORE_UTILITIES_H
#define MI_CORE_UTILITIES_H

#include "mi_core_global.h"
#include <QVariant>

namespace Mi {

MI_CORE_EXPORT QString applicationTreeDirectory();

inline QString colorFromInt(int color)
{
    return QString("#%1").arg(color, 6, 16, QChar('0'));
}

inline int intFromColor(QVariant colorStringVariant)
{
    return qBound(0x000000, colorStringVariant.toString().remove("#").toInt(0, 16), 0xffffff);
}

inline int colorIntFromVariant(const QVariant &variant)
{
    if (QVariant::String == variant.type())
        return intFromColor(variant);
    return qBound(0x000000, qvariant_cast<int>(variant), 0xffffff);
}

}

#endif
