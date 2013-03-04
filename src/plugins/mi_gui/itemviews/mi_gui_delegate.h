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

#ifndef MI_GUI_DELEGATE_H
#define MI_GUI_DELEGATE_H

#include <QStyledItemDelegate>
#include "mi_gui_global.h"

namespace Base {

class MI_GUI_EXPORT Delegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    Delegate(QObject *parent = 0)
        :   QStyledItemDelegate(parent)
        ,   _customColumn(-1)
    {}

    int customColumn() const
    {
        return _customColumn;
    }

    void setCustomColumn(int column)
    {
        _customColumn = column;
    }

private:
    int _customColumn;
};

}

#endif
