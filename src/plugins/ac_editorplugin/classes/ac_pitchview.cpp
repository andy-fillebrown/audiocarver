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

#include "ac_pitchview.h"
#include <ac_pitchscene.h>
#include <ac_score.h>
#include <ac_scoreview.h>
#include <ac_viewsettings.h>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcPitchViewData
{
public:
    AcPitchViewData()
    {}

    void updatePitchScene()
    {
//        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
//        AcPitchScene *pitchScene = AcPitchScene::instance();
//        AcPitchView *pitchView = AcPitchView::instance();
//        AcScoreView *scoreView = AcScoreView::instance();
//        const qreal scaleX = viewSettings->scaleX();
//        const qreal scaleY = viewSettings->scaleY();
//        QPointF topLeft = scoreView->mapToScene(scoreView->rect().topLeft());
//        QPointF bottomRight = scoreView->mapToScene(scoreView->rect().bottomRight());
//        topLeft.rx() *= scaleX;
//        topLeft.ry() *= scaleY;
//        bottomRight.rx() *= scaleX;
//        bottomRight.ry() *= scaleY;
//        pitchScene->setSceneRect(0.0f, topLeft.y(), 10.0f, bottomRight.y() - topLeft.y());
//        pitchView->centerOn(5.0f, scoreView->center().y() * scaleY);
    }
};

} // namespace Private

AcPitchView::AcPitchView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcPitchViewData)
{}

AcPitchView::~AcPitchView()
{
    delete d;
}

void AcPitchView::update()
{
    d->updatePitchScene();
}

void AcPitchView::updateViewSettings(const QString &propertyName)
{
    d->updatePitchScene();
}
