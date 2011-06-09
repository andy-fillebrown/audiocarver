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

#include "ac_graphicsview.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcGraphicsViewData
{
public:
    AcGraphicsView *q;

    AcGraphicsViewData(AcGraphicsView *q)
        :   q(q)
    {}
};

} // namespace Private

AcGraphicsView::AcGraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   MiGraphicsView(scene, parent)
    ,   d(new AcGraphicsViewData(this))
{
    AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
    connect(viewSettings, SIGNAL(propertyChanged(QString)), SLOT(updateViewSettings(QString)));
}

AcGraphicsView::~AcGraphicsView()
{
    delete d;
}

void AcGraphicsView::updateViewSettings(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
