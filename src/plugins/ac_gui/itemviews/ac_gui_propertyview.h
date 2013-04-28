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

#ifndef AC_GUI_PROPERTYVIEW_H
#define AC_GUI_PROPERTYVIEW_H

#include <QTableView>

class PropertyView : public QTableView
{
    Q_OBJECT

public:
    PropertyView(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif
