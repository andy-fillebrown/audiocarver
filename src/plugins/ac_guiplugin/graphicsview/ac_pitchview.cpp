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

#include "ac_scoreview.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcScoreViewData
{
public:
    AcScoreViewData()
    {}
};

} // namespace Private

AcScoreView::AcScoreView(QGraphicsScene *scene, QWidget *parent)
    :   AcEditorView(scene, parent)
    ,   d(new AcScoreViewData)
{}

AcScoreView::~AcScoreView()
{
    delete d;
}

void AcScoreView::updateTransform()
{
    AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
    setTransform(QTransform::fromScale(viewSettings->timeScale(), viewSettings->pitchScale()));
}

void AcScoreView::updateViewSettings() const
{
    AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
    viewSettings->setTimePosition(center().x());
    viewSettings->setPitchPosition(center().y());
}
