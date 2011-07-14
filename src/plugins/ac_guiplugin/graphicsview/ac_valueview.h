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

#ifndef AC_VALUEVIEW_H
#define AC_VALUEVIEW_H

#include <ac_graphicsview.h>

namespace Private {

class AcValueViewData;

} // namespace Private

class AcValueView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcValueView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcValueView();

private:
    Q_DISABLE_COPY(AcValueView)
    Private::AcValueViewData *d;
};

#endif // AC_VALUEVIEW_H
