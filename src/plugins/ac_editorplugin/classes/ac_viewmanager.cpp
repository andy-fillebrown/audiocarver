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
        synchronizeGraphicsBarLineItems();
        updateBarLines();
        updateBarLabels();
    }

    void updateFont()
    {
        font = QFont(fontSettings->family(), fontSettings->pointSize());
        fontMetrics = QFontMetrics(font);
    }

    void synchronizeGraphicsBarLineItems()
    {
        const MiList<AcBarLine> &barLines = score->barLines();

        // Synchronize graphics bar line list with score bar line list.
        for (int i = 0;  i < barLines.count();  ++i) {
            if (graphicsBarLineItems.count() <= i) {
                AcGraphicsBarLineItem *graphicsBarLineItem = new AcGraphicsBarLineItem(barLines.at(i));
                scoreScene->addItem(graphicsBarLineItem->qGraphicsScoreLineItem());
                timeScene->addItem(graphicsBarLineItem->qGraphicsTimeTextItem());
                graphicsBarLineItems.append(graphicsBarLineItem);
            } else
                graphicsBarLineItems.at(i)->setGridLine(barLines.at(i));
        }

        // Remove unused graphics bar line items.
        while (barLines.count() < graphicsBarLineItems.count()) {
            AcGraphicsBarLineItem *graphicsBarLineItem = graphicsBarLineItems.last();
            timeScene->removeItem(graphicsBarLineItem->qGraphicsTimeTextItem());
            scoreScene->removeItem(graphicsBarLineItem->qGraphicsScoreLineItem());
            graphicsBarLineItems.removeLast();
            delete graphicsBarLineItem;
        }
    }

    void updateBarLines()
    {
        foreach (AcGraphicsBarLineItem *graphicsBarLineItem, graphicsBarLineItems) {
            const qreal location = graphicsBarLineItem->location();
            graphicsBarLineItem->qGraphicsScoreLineItem()->setLine(location, 0.0f, location, 127.0f);
        }
    }

    void updateBarLabels()
    {
        qreal scaleX = viewSettings->scaleX();
        foreach (AcGraphicsBarLineItem *graphicsBarLineItem, graphicsBarLineItems) {
            const qreal location = graphicsBarLineItem->location();
            const QRect labelRect = fontMetrics.boundingRect(graphicsBarLineItem->label());
            graphicsBarLineItem->qGraphicsTimeTextItem()->setPos((location * scaleX) - (labelRect.width() / 2), 10.0f);
        }
    }
};

} // namespace Private

AcViewManager::AcViewManager(QWidget *widget)
    :   QObject(widget)
    ,   d(new AcViewManagerData(this, widget))
{
    connect(d->score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
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
    if ("barLines" == propertyName) {
        updateBarLines();
        return;
    }
}

void AcViewManager::updateViewSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
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
}

void AcViewManager::updateBarLines()
{
    d->synchronizeGraphicsBarLineItems();
}
