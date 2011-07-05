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

#include "ac_viewmanager.h"
#include <ac_barline.h>
#include <ac_controllerscene.h>
#include <ac_controllerview.h>
#include <ac_graphicsbarlineitem.h>
#include <ac_graphicstuninglineitem.h>
#include <ac_pitchscene.h>
#include <ac_pitchview.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_scoreview.h>
#include <ac_timescene.h>
#include <ac_timeview.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <mi_list.h>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QWidget>

using namespace Private;

namespace Private {

class AcViewManagerData
{
public:
    AcViewManager *q;
    QWidget *widget;
    AcScoreScene *scoreScene;
    AcScoreView *scoreView;
    AcControllerScene *controllerScene;
    AcControllerView *controllerView;
    AcPitchScene *pitchScene;
    AcPitchView *pitchView;
    AcTimeScene *timeScene;
    AcTimeView *timeView;
    AcScore *score;
    MiFont *fontSettings;
    AcViewSettings *viewSettings;
    QFont font;
    QFontMetrics fontMetrics;
    QList<AcGraphicsBarLineItem*> graphicsBarLineItems;
    QList<AcGraphicsTuningLineItem*> graphicsTuningLineItems;

    AcViewManagerData(AcViewManager *q, QWidget *widget)
        :   q(q)
        ,   widget(widget)
        ,   scoreScene(new AcScoreScene(q))
        ,   scoreView(new AcScoreView(scoreScene, widget))
        ,   controllerScene(new AcControllerScene(q))
        ,   controllerView(new AcControllerView(controllerScene, widget))
        ,   pitchScene(new AcPitchScene(q))
        ,   pitchView(new AcPitchView(pitchScene, widget))
        ,   timeScene(new AcTimeScene(q))
        ,   timeView(new AcTimeView(timeScene, widget))
        ,   score(AcScore::instance())
        ,   fontSettings(score->fontSettings())
        ,   viewSettings(score->viewSettings())
        ,   font(fontSettings->family(), fontSettings->pointSize())
        ,   fontMetrics(font)
    {}

    void init()
    {
        updateScoreViewLength();
        synchronizeTuningLineLists();
        updateTuningLinePositions();
        updateTuningLabelPositions();
        synchronizeBarLineLists();
        updateBarLinePositions();
        updateBarLabelPositions();
    }

    void updateScoreViewLength()
    {
        scoreScene->setSceneRect(0.0f, 0.0f, score->length(), 127.0f);
    }

    void updateViewRects()
    {
        pitchScene->setSceneRect(0.0f, 0.0f, 10.0f, 127.0f * viewSettings->scaleY());
        timeScene->setSceneRect(0.0f, 0.0f, score->length() * viewSettings->scaleX(), 10.0f);
    }

    void updateViewCenters()
    {
        pitchView->centerOn(5.0f, scoreView->center().y() * viewSettings->scaleY());
        timeView->centerOn(scoreView->center().x() * viewSettings->scaleX(), 5.0f);
    }

    void synchronizeTuningLineLists()
    {
    }

    void updateTuningLinePositions()
    {
    }

    void updateTuningLabelPositions()
    {
    }

    void synchronizeBarLineLists()
    {
//        const MiList<AcBarLine> &barLines = score->barLines();
        QList<AcBarLine*> *barLines = score->barLines().list();
        for (int i = 0;  i < barLines->count();  ++i) {
            if (graphicsBarLineItems.count() <= i) {
                AcGraphicsBarLineItem *graphicsBarLineItem = new AcGraphicsBarLineItem(barLines->at(i));
                scoreScene->addItem(graphicsBarLineItem->qGraphicsScoreLineItem());
                timeScene->addItem(graphicsBarLineItem->qGraphicsTimeTextItem());
                graphicsBarLineItems.append(graphicsBarLineItem);
            } else
                graphicsBarLineItems.at(i)->setGridLine(barLines->at(i));
        }

        // Remove unused graphics bar line items.
        while (barLines->count() < graphicsBarLineItems.count()) {
            AcGraphicsBarLineItem *graphicsBarLineItem = graphicsBarLineItems.last();
            timeScene->removeItem(graphicsBarLineItem->qGraphicsTimeTextItem());
            scoreScene->removeItem(graphicsBarLineItem->qGraphicsScoreLineItem());
            graphicsBarLineItems.removeLast();
            delete graphicsBarLineItem;
        }
    }

    void updateBarLinePositions()
    {
        foreach (AcGraphicsBarLineItem *graphicsBarLineItem, graphicsBarLineItems) {
            const qreal location = graphicsBarLineItem->location();
            graphicsBarLineItem->qGraphicsScoreLineItem()->setLine(location, 0.0f, location, 127.0f);
        }
    }

    void updateBarLabelPositions()
    {
        qreal scaleX = viewSettings->scaleX();
        foreach (AcGraphicsBarLineItem *graphicsBarLineItem, graphicsBarLineItems) {
            const qreal location = graphicsBarLineItem->location();
            const QRect labelRect = fontMetrics.boundingRect(graphicsBarLineItem->label());
            graphicsBarLineItem->qGraphicsTimeTextItem()->setPos((location * scaleX) - (labelRect.width() / 2), 10.0f);
        }
    }

    void updateFont()
    {
        font = QFont(fontSettings->family(), fontSettings->pointSize());
        fontMetrics = QFontMetrics(font);
    }
};

} // namespace Private

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerData(this, widget))
{
    connect(d->score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
    connect(d->fontSettings, SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
    connect(d->viewSettings, SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));

    d->init();
}

AcViewManager::~AcViewManager()
{
    delete d;
}

qreal AcViewManager::positionX() const
{
    return d->scoreView->center().x();
}

void AcViewManager::setPositionX(qreal positionX)
{
    d->scoreView->setCenter(positionX, positionY());
}

qreal AcViewManager::positionY() const
{
    return d->scoreView->center().y();
}

void AcViewManager::setPositionY(qreal positionY)
{
    d->scoreView->setCenter(positionX(), positionY);
}

qreal AcViewManager::scaleX() const
{
    return d->viewSettings->scaleX();
}

void AcViewManager::setScaleX(qreal scaleX)
{
    d->viewSettings->setScaleX(scaleX);
}

qreal AcViewManager::scaleY() const
{
    return d->viewSettings->scaleY();
}

void AcViewManager::setScaleY(qreal scaleY)
{
    d->viewSettings->setScaleY(scaleY);
}

void AcViewManager::updateScoreProperty(const QString &propertyName)
{
    if ("tuningLines" == propertyName) {
        d->synchronizeTuningLineLists();
        d->updateTuningLinePositions();
        d->updateTuningLabelPositions();
    }
    else if ("barLines" == propertyName) {
        d->synchronizeBarLineLists();
        d->updateBarLinePositions();
        d->updateBarLabelPositions();
    }
}

void AcViewManager::updateFontSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);

    d->updateFont();
    d->updateBarLabelPositions();
}

void AcViewManager::updateViewSettingsProperty(const QString &propertyName)
{
    if (propertyName.startsWith("position")) {
        d->scoreView->updateCenter();
        d->updateViewCenters();
    } else if (propertyName.startsWith("scale")) {
        d->scoreView->updateTransform();
        d->scoreView->updateCenter();
        d->updateViewRects();
        d->updateViewCenters();
    }
    if (propertyName.endsWith("Y")) {
        d->updateTuningLinePositions();
        d->updateTuningLabelPositions();
    } else {
        d->updateBarLinePositions();
        d->updateBarLabelPositions();
    }
}

AcScoreView *AcViewManager::scoreView() const
{
    return d->scoreView;
}

AcControllerView *AcViewManager::controllerView() const
{
    return d->controllerView;
}

AcPitchView *AcViewManager::pitchView() const
{
    return d->pitchView;
}

AcTimeView *AcViewManager::timeView() const
{
    return d->timeView;
}

void AcViewManager::updateViews()
{
    d->scoreView->updateTransform();
    d->updateScoreViewLength();
    d->updateViewRects();
    d->updateViewCenters();
}
