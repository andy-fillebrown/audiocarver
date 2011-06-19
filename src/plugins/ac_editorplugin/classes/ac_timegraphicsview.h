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

#ifndef AC_TIMEGRAPHICSVIEW_H
#define AC_TIMEGRAPHICSVIEW_H

#include <ac_graphicsview.h>
#include <ac_editor_global.h>

namespace Private {

class AcTimeGraphicsViewData;

} // namespace Private

class AcTimeGraphicsView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcTimeGraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcTimeGraphicsView();

    void update();

protected:
    virtual void updateViewSettings(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcTimeGraphicsView)
    Private::AcTimeGraphicsViewData *d;
};

#endif // AC_TIMEGRAPHICSVIEW_H
