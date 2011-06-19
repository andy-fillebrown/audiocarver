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

#ifndef AC_CONTROLLERVIEW_H
#define AC_CONTROLLERVIEW_H

#include <ac_graphicsview.h>
#include <ac_editor_global.h>

namespace Private {

class AcControllerViewData;

} // namespace Private

class AcControllerView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcControllerView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcControllerView();

    void updateCenter();
    void updateLength();
    void updateScaleX();
    void updateScaleY();

private:
    Q_DISABLE_COPY(AcControllerView)
    Private::AcControllerViewData *d;
};

#endif // AC_CONTROLLERVIEW_H
