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

#include "ac_mainwidget.h"
#include <ac_pitchscene.h>
#include <ac_pitchview.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_scoreview.h>
#include <ac_timescene.h>
#include <ac_timeview.h>
#include <ac_viewsettings.h>
#include <mi_graphicsview.h>
#include <QApplication>
#include <QGraphicsPathItem>
#include <QLayout>
#include <QWheelEvent>

using namespace Private;

namespace Private {

class AcMainWidgetData
{
public:
    AcMainWidget *q;
    AcScoreScene *scoreScene;
    AcTimeScene *timeScene;
    AcPitchScene *pitchScene;
    MiGraphicsScene *volumeScene;
    QGridLayout *layout;
    AcScoreView *scoreView;
    AcTimeView *timeView;
    AcPitchView *pitchView;
    MiGraphicsView *volumeView;
    MiGraphicsView *topLeft;
    MiGraphicsView *bottomLeft;

    AcMainWidgetData(AcMainWidget *q)
        :   q(q)
        ,   scoreScene(new AcScoreScene(q))
        ,   timeScene(new AcTimeScene(q))
        ,   pitchScene(new AcPitchScene(q))
        ,   volumeScene(new MiGraphicsScene(q))
        ,   layout(new QGridLayout(q))
        ,   scoreView(new AcScoreView(scoreScene, q))
        ,   timeView(new AcTimeView(timeScene, q))
        ,   pitchView(new AcPitchView(pitchScene, q))
        ,   volumeView(new MiGraphicsView(volumeScene, q))
        ,   topLeft(new MiGraphicsView(0, q))
        ,   bottomLeft(new MiGraphicsView(0, q))
    {
        const int sideWidth = 64;
        const int sideHeight = 64;
        const int volumeHeight = 192;
        layout->setContentsMargins(QMargins(0, 0, 0, 0));
        layout->setSpacing(0);
        layout->addWidget(topLeft, 0, 0);
        layout->addWidget(timeView, 0, 1);
        layout->addWidget(pitchView, 1, 0);
        layout->addWidget(scoreView, 1, 1);
        layout->addWidget(bottomLeft, 2, 0);
        layout->addWidget(volumeView, 2, 1);
        scoreView->setFrameShape(QFrame::Box);
        scoreView->setFrameShadow(QFrame::Sunken);
        scoreView->setLineWidth(1);
        scoreView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scoreView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeView->setFixedHeight(sideHeight);
        timeView->setFrameShape(QFrame::NoFrame);
        timeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        timeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pitchView->setFixedWidth(sideWidth);
        pitchView->setFrameShape(QFrame::NoFrame);
        pitchView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pitchView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        volumeView->setFixedHeight(volumeHeight);
        volumeView->setFrameShape(QFrame::Box);
        volumeView->setFrameShadow(QFrame::Sunken);
        volumeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        volumeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        topLeft->setFixedSize(sideWidth, sideHeight);
        topLeft->setFrameShape(QFrame::NoFrame);
        bottomLeft->setFixedSize(sideWidth, volumeHeight);
        bottomLeft->setFrameShape(QFrame::NoFrame);
        scoreView->updateCenter();
        pitchView->update();
        timeView->update();
    }

    void updateViews()
    {
        scoreView->updateCenter();
        pitchView->update();
    }
};

} // namespace Private

static AcMainWidget *instance = 0;

AcMainWidget::AcMainWidget(QWidget *parent)
    :   QWidget(parent)
    ,   d(new AcMainWidgetData(this))
{
    ::instance = this;
}

AcMainWidget::~AcMainWidget()
{
    delete d;
}

AcMainWidget *AcMainWidget::instance()
{
    return ::instance;
}

qreal AcMainWidget::positionX() const
{
    return d->scoreView->center().x();
}

void AcMainWidget::setPositionX(qreal positionX)
{
    d->scoreView->setCenter(positionX, d->scoreView->center().y());
}

qreal AcMainWidget::positionY() const
{
    return d->scoreView->center().y();
}

void AcMainWidget::setPositionY(qreal positionY)
{
    d->scoreView->setCenter(d->scoreView->center().x(), positionY);
}

qreal AcMainWidget::scaleX() const
{
    return AcScore::instance()->viewSettings()->scaleX();
}

void AcMainWidget::setScaleX(qreal scaleX)
{
    AcScore::instance()->viewSettings()->setScaleX(scaleX);
}

qreal AcMainWidget::scaleY() const
{
    return AcScore::instance()->viewSettings()->scaleY();
}

void AcMainWidget::setScaleY(qreal scaleY)
{
    AcScore::instance()->viewSettings()->setScaleY(scaleY);
}

void AcMainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    d->updateViews();
}

void AcMainWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    d->updateViews();
}

void AcMainWidget::wheelEvent(QWheelEvent *event)
{
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        qreal scale = event->delta() < 0 ? 0.8f : 1.25f;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            setScaleX(scale * scaleX());
        else
            setScaleY(scale * scaleY());
    } else {
        int offset = event->delta() < 0 ? 10 : -10;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            setPositionX(positionX() - offset);
        else
            setPositionY(positionY() + offset);
    }
    event->accept();
}
