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
    QList<AcGraphicsBarLineItem*> barLineItems;
    QList<AcGraphicsTuningLineItem*> tuningLineItems;
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
        updateTuningLineItems();
        updateBarLineItems();
        updateFontMetrics();
    }

    void updateTuningLineItems()
    {
        const QList<AcTuningLine*> &tuningLines = AcScore::instance()->tuningLines().list();
        for (int i = 0;  i < tuningLines.count();  ++i) {
            if (tuningLineItems.count() <= i)
                tuningLineItems.append(new AcGraphicsTuningLineItem(tuningLines[i]));
            else
                tuningLineItems[i]->setGridLine(tuningLines[i]);
        }
        while (tuningLines.count() < tuningLineItems.count()) {
            delete tuningLineItems.last();
            tuningLineItems.removeLast();
        }
    }

    void updateBarLineItems()
    {
        const QList<AcBarLine*> &barLines = AcScore::instance()->barLines().list();
        for (int i = 0;  i < barLines.count();  ++i) {
            if (barLineItems.count() <= i) {
                AcGraphicsBarLineItem *barLineItem = new AcGraphicsBarLineItem(barLines[i]);
                barLineItems.append(barLineItem);
            } else
                barLineItems[i]->setGridLine(barLines[i]);
        }
        while (barLines.count() < barLineItems.count()) {
            delete barLineItems.last();
            barLineItems.removeLast();
        }
    }

    void updateFontMetrics()
    {
        fontMetrics = QFontMetrics(font());
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
    if ("tuningLines" == propertyName)
        d->updateTuningLineItems();
    else if ("barLines" == propertyName)
        d->updateBarLineItems();
}

void AcSceneManager::updateFontSettingsProperty(const QString &propertyName)
{
    d->updateFontMetrics();
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
