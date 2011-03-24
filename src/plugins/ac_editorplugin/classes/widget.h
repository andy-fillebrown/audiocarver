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

#ifndef AC_WIDGET_H
#define AC_WIDGET_H

#include <gleditorplugin/classes/widget.h>

namespace AudioCarver {
namespace Internal {

class Widget : public GL::Widget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    virtual ~Widget();

    static Widget *instance();
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_WIDGET_H
