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

#include "ac_timeview.h"
#include <ac_timescene.h>
#include <ac_score.h>
#include <ac_scoreview.h>
#include <ac_viewsettings.h>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcTimeViewData
{
public:
    AcTimeViewData()
    {}
};

} // namespace Private

AcTimeView::AcTimeView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcTimeViewData)
{}

AcTimeView::~AcTimeView()
{
    delete d;
}
