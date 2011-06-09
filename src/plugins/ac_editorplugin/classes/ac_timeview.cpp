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

    void updateTimeScene()
    {
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        AcTimeScene *timeScene = AcTimeScene::instance();
        AcTimeView *timeView = AcTimeView::instance();
        AcScoreView *scoreView = AcScoreView::instance();
        const qreal scaleX = viewSettings->scaleX();
        const qreal scaleY = viewSettings->scaleY();
        QPointF topLeft = scoreView->mapToScene(scoreView->rect().topLeft());
        QPointF bottomRight = scoreView->mapToScene(scoreView->rect().bottomRight());
        topLeft.rx() *= scaleX;
        topLeft.ry() *= scaleY;
        bottomRight.rx() *= scaleX;
        bottomRight.ry() *= scaleY;
        timeScene->setSceneRect(topLeft.x(), 0.0f, bottomRight.x() - topLeft.x(), 10.0f);
        timeView->centerOn(scoreView->center().x() * scaleX, 5.0f);
    }
};

} // namespace Private

static AcTimeView *instance = 0;

AcTimeView::AcTimeView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcTimeViewData)
{
    ::instance = this;
}

AcTimeView::~AcTimeView()
{
    delete d;
}

AcTimeView *AcTimeView::instance()
{
    return ::instance;
}

void AcTimeView::update()
{
    d->updateTimeScene();
}

void AcTimeView::updateViewSettings(const QString &propertyName)
{
    d->updateTimeScene();
}