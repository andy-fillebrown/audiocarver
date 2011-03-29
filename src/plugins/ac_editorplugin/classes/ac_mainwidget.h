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

#ifndef AC_MAINWIDGET_H
#define AC_MAINWIDGET_H

#include <QWidget>

#include <ac_editor_global.h>

namespace Private {

class AcMainWidgetData;

class AcMainWidget : public QWidget
{
public:
    AcMainWidget(QWidget *parent = 0);
private:
    ~AcMainWidget();
    Q_DISABLE_COPY(AcMainWidget)

public:
    static AcMainWidget *instance();

private:
    AcMainWidgetData *d;
};

} // namespace Private

#endif // AC_MAINWIDGET_H
