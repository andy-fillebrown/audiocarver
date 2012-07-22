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

#ifndef AC_IPLAYCURSOR_H
#define AC_IPLAYCURSOR_H

#include <ac_core_namespace.h>

#include <mi_iunknown.h>

class IPlayCursor : public IUnknown
{
public:
    enum { Type = I::IPlayCursor };

    virtual qreal playCursorPosition() const = 0;
    virtual void dragPlayCursorTo(qreal position) = 0;
    virtual void setPlayCursorPosition(qreal position) = 0;
};

#endif // AC_IPLAYCURSOR_H
