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

#include "ac_scenemanager.h"
#include <ac_barline.h>
#include <ac_controllerscene.h>
#include <ac_graphicsbarlineitem.h>
#include <ac_graphicstuninglineitem.h>
#include <ac_pitchscene.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_timescene.h>
#include <ac_tuningline.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <mi_list.h>
#include <QFont>
#include <QFontMetrics>

using namespace Private;

namespace Private {

class AcSceneManagerData
{
public:
    AcSceneManager *q;
    AcScoreScene *scoreScene;
    AcControllerScene *controllerScene;
    AcTimeScene *timeScene;
    AcPitchScene *pitchScene;
    QList<AcGraphicsBarLineItem*> barItems;
    QList<AcGraphicsTuningLineItem*> tuningItems;
    QFontMetrics fontMetrics;

    AcSceneManagerData(AcSceneManager *q)
        :   q(q)
        ,   scoreScene(new AcScoreScene(q))
        ,   controllerScene(new AcControllerScene(q))
        ,   timeScene(new AcTimeScene(q))
        ,   pitchScene(new AcPitchScene(q))
        ,   fontMetrics(font())
    {}

    QFont font() const
    {
        const MiFont *fontSettings = AcScore::instance()->fontSettings();
        return QFont(fontSettings->family(), fontSettings->pointSize());
    }

    void init()
    {
        updateBarItems();
        updateTuningItems();
        updateFontMetrics();
        updateBarItemVisibilities();
        updateTuningItemVisibilities();
    }

    void updateBarItems()
    {
        const QList<AcBarLine*> &barLines = AcScore::instance()->barLines().list();
        for (int i = 0;  i < barLines.count();  ++i) {
            if (barItems.count() <= i) {
                AcGraphicsBarLineItem *barItem = new AcGraphicsBarLineItem(barLines[i]);
                barItems.append(barItem);
            } else
                barItems[i]->setGridLine(barLines[i]);
        }
        while (barLines.count() < barItems.count()) {
            delete barItems.last();
            barItems.removeLast();
        }
    }

    void updateTuningItems()
    {
        const QList<AcTuningLine*> &tuningLines = AcScore::instance()->tuningLines().list();
        for (int i = 0;  i < tuningLines.count();  ++i) {
            if (tuningItems.count() <= i)
                tuningItems.append(new AcGraphicsTuningLineItem(tuningLines[i]));
            else
                tuningItems[i]->setGridLine(tuningLines[i]);
        }
        while (tuningLines.count() < tuningItems.count()) {
            delete tuningItems.last();
            tuningItems.removeLast();
        }
    }

    void updateFontMetrics()
    {
        fontMetrics = QFontMetrics(font());
    }

    void updateBarItemVisibilities()
    {
        int minPriority = 0x7fffffff;
        int prevPriority = 0;
        QRectF prevRect;
        foreach (AcGraphicsBarLineItem *barItem, barItems) {
            if (minPriority && minPriority < barItem->priority())
                continue;
            QRectF curRect = barItem->labelRect();
            curRect.setWidth(2.0f * curRect.width());
            if (prevRect.intersects(curRect))
                minPriority = qMax(prevPriority, barItem->priority());
            else {
                prevPriority = barItem->priority();
                prevRect = curRect;
            }
        }
        foreach (AcGraphicsBarLineItem *barItem, barItems) {
            if (barItem->priority() <= minPriority)
                barItem->show();
            else
                barItem->hide();
        }
    }

    void updateTuningItemVisibilities()
    {
        int minPriority = 0x7fffffff;
        int prevPriority = 0;
        QRectF prevRect;
        foreach (AcGraphicsTuningLineItem *tuningItem, tuningItems) {
            if (minPriority && minPriority <= tuningItem->priority())
                continue;
            QRectF curRect = tuningItem->labelRect();
            if (prevRect.intersects(curRect))
                minPriority = qMax(prevPriority, tuningItem->priority());
            else {
                prevPriority = tuningItem->priority();
                prevRect = curRect;
            }
        }
        foreach (AcGraphicsTuningLineItem *tuningItem, tuningItems) {
            if (tuningItem->priority() < minPriority)
                tuningItem->show();
            else
                tuningItem->hide();
        }
    }
};

} // namespace Private

AcSceneManager *instance = 0;

AcSceneManager::AcSceneManager(QObject *parent)
    :   QObject(parent)
    ,   d(new AcSceneManagerData(this))
{
    ::instance = this;
    d->init();
    AcScore *score = AcScore::instance();
    connect(score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
    connect(score->fontSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateFontSettingsProperty(QString)));
    connect(score->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
}

AcSceneManager::~AcSceneManager()
{
    delete d;
}

AcSceneManager *AcSceneManager::instance()
{
    return ::instance;
}

void AcSceneManager::updateScoreProperty(const QString &propertyName)
{
    if ("barLines" == propertyName) {
        d->updateBarItems();
        d->updateBarItemVisibilities();
    }
    else if ("tuningLines" == propertyName) {
        d->updateTuningItems();
        d->updateTuningItemVisibilities();
    }
}

void AcSceneManager::updateFontSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    d->updateFontMetrics();
    d->updateBarItemVisibilities();
    d->updateTuningItemVisibilities();
}

void AcSceneManager::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleX" == propertyName)
        d->updateBarItemVisibilities();
    else if ("scaleY" == propertyName)
        d->updateTuningItemVisibilities();
}

QGraphicsScene *AcSceneManager::scoreScene() const
{
    return d->scoreScene;
}

QGraphicsScene *AcSceneManager::controllerScene() const
{
    return d->controllerScene;
}

QGraphicsScene *AcSceneManager::timeScene() const
{
    return d->timeScene;
}

QGraphicsScene *AcSceneManager::pitchScene() const
{
    return d->pitchScene;
}

const QFontMetrics &AcSceneManager::fontMetrics() const
{
    return d->fontMetrics;
}
