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

#include "ac_scoregraphicsview.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcScoreGraphicsViewData
{
public:
    AcScoreGraphicsView *q;
    QPointF center;

    AcScoreGraphicsViewData(AcScoreGraphicsView *q)
        :   q(q)
    {}

    void updateViewTransform()
    {
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        q->setTransform(QTransform::fromScale(viewSettings->scaleX(), viewSettings->scaleY()));
    }
};

} // namespace Private

AcScoreGraphicsView::AcScoreGraphicsView(QGraphicsScene *scene, QWidget *parent)
    :   AcGraphicsView(scene, parent)
    ,   d(new AcScoreGraphicsViewData(this))
{
    connect(AcScore::instance(), SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
}

AcScoreGraphicsView::~AcScoreGraphicsView()
{
    delete d;
}

const QPointF &AcScoreGraphicsView::center() const
{
    return d->center;
}

void AcScoreGraphicsView::setCenter(const QPointF &center)
{
    QPointF prevCtr = d->center;
    centerOn(center);
    updateCenter();
    if (d->center != prevCtr) {
        AcViewSettings *viewSettings = AcScore::instance()->viewSettings();
        viewSettings->setPositionX(center.x());
        viewSettings->setPositionY(center.y());
    }
}

void AcScoreGraphicsView::setCenter(qreal x, qreal y)
{
    setCenter(QPointF(x, y));
}

void AcScoreGraphicsView::updateScoreProperty(const QString &propertyName)
{
    if ("length" == propertyName)
        setCenter(mapToScene(rect().center()));
}

void AcScoreGraphicsView::updateCenter()
{
    d->center = mapToScene(rect().center());
}

void AcScoreGraphicsView::updateViewSettings(const QString &propertyName)
{
    if (propertyName.startsWith("scale"))
        d->updateViewTransform();
}
