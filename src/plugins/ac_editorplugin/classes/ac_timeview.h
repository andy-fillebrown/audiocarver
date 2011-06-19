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

#ifndef AC_TIMEVIEW_H
#define AC_TIMEVIEW_H

#include <ac_graphicsview.h>
#include <ac_editor_global.h>

namespace Private {

class AcTimeViewData;

} // namespace Private

class AcTimeView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcTimeView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcTimeView();

    void updateCenter();
    void updateLength();
    void updateScaleX();

private:
    Q_DISABLE_COPY(AcTimeView)
    Private::AcTimeViewData *d;
};

#endif // AC_TIMEVIEW_H
