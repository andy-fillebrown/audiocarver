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

#include "ac_pitchscene.h"
#include <ac_score.h>
#include <ac_tuning.h>
#include <ac_viewsettings.h>
#include <mi_font.h>
#include <mi_list.h>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcPitchSceneData
{
public:
    AcPitchScene *q;
    QList<QGraphicsTextItem*> tuningItems;

    AcPitchSceneData(AcPitchScene *q)
        :   q(q)
    {}

    void updateTuningItem(int index, AcTuning *tuning)
    {
        while (tuningItems.count() < index + 1)
            tuningItems.append(q->addText("", q->font()));
        QGraphicsTextItem *tuningItem = tuningItems.at(index);
        tuningItem->setPlainText(tuning->text());
        QRect textRect = q->fontMetrics().boundingRect(tuning->text());
        qreal scaleY = q->score()->viewSettings()->scaleY();
        tuningItem->setPos(20.0f - textRect.width(), ((127.0f - tuning->location()) * scaleY) - (textRect.height() / 1.5));
    }

    void removeUnusedTuningItems()
    {
        while (q->score()->tunings().count() < tuningItems.count()) {
            delete tuningItems.last();
            tuningItems.removeLast();
        }
    }
};

} // namespace Private

static AcPitchScene *instance = 0;

AcPitchScene::AcPitchScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcPitchSceneData(this))
{
    ::instance = this;
    updateTunings();
    connect(score()->fontSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateTuningProperties()));
    connect(score()->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
}

AcPitchScene::~AcPitchScene()
{
    delete d;
}

AcPitchScene *AcPitchScene::instance()
{
    return ::instance;
}

void AcPitchScene::updateScoreProperty(const QString &propertyName)
{
    if ("tunings" == propertyName)
        updateTunings();
}

void AcPitchScene::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleY" == propertyName)
        updateTuningProperties();
}

void AcPitchScene::updateTunings()
{
    for (int i = 0;  i < score()->tunings().count();  ++i) {
        AcTuning *tuning = score()->tunings().at(i);
        connect(tuning, SIGNAL(propertyChanged(QString)), SLOT(updateTuningProperties()), Qt::UniqueConnection);
        d->updateTuningItem(i, tuning);
    }
    d->removeUnusedTuningItems();
}

void AcPitchScene::updateTuningProperties()
{
    for (int i = 0;  i < score()->tunings().count();  ++i)
        d->updateTuningItem(i, score()->tunings().at(i));
}
