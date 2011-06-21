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
    AcScoreView *q;
    QPointF center;

    AcScoreViewData(AcScoreView *q)
        :   q(q)
    {}

    void updateCenter()
    {
        center = q->mapToScene(q->rect().center());
    }

    void updateTransform()
    {
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        q->setTransform(QTransform::fromScale(viewSettings->scaleX(), viewSettings->scaleY()));
    }
};

} // namespace Private

AcScoreView::AcScoreView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcScoreViewData(this))
{}

AcScoreView::~AcScoreView()
{
    delete d;
}

const QPointF &AcScoreView::center() const
{
    return d->center;
}

void AcScoreView::setCenter(const QPointF &center)
{
    QPointF prevCtr = d->center;
    centerOn(center);
    d->updateCenter();
    if (d->center != prevCtr) {
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        viewSettings->setPositionX(center.x());
        viewSettings->setPositionY(center.y());
    }
}

void AcScoreView::setCenter(qreal x, qreal y)
{
    setCenter(QPointF(x, y));
}

void AcScoreView::updateCenter()
{
    setCenter(mapToScene(rect().center()));
}

void AcScoreView::updateTransform()
{
    d->updateTransform();
}
