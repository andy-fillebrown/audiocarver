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

#include "ac_scorescene.h"

#include <ac_score.h>
#include <ac_tuning.h>

#include <mi_list.h>

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QPainterPath>

using namespace Private;

namespace Private {

class AcScoreSceneData
{
public:
    AcScoreScene *q;

    QGraphicsRectItem *scoreRectItem;
    QList<QGraphicsLineItem*> barLineItems;
    QList<QGraphicsLineItem*> tuningLineItems;

    AcScoreSceneData(AcScoreScene *q)
        :   q(q)
        ,   scoreRectItem(q->addRect(0.0f, 0.0f, 0.0f, 0.0f))
    {
        updateLength(q->score()->length());
    }

    void updateTuning(AcTuning *tuning, int index)
    {
        while (tuningLineItems.count() < index + 1)
            tuningLineItems.append(q->addLine(QLineF()));

        QGraphicsLineItem *tuningLineItem = tuningLineItems.at(index);
        const qreal y = 127.0f - tuning->cents();
        const qreal scoreLength = q->score()->length();
        tuningLineItem->setLine(0.0f, y, scoreLength, y);
        tuningLineItem->setPen(QPen(tuning->color()));
    }

    void removeUnusedTuningItems()
    {
        MiList *tunings = q->score()->tunings();
        while (tunings->count() < tuningLineItems.count())
            tuningLineItems.removeLast();
    }

    void updateLength(qreal scoreLength)
    {
        scoreRectItem->setRect(0.0f, 0.0f, scoreLength, 127.0f);

        foreach (QGraphicsLineItem *tuningLineItem, tuningLineItems) {
            QLineF line = tuningLineItem->line();
            line.setLength(scoreLength);
            tuningLineItem->setLine(line);
        }
    }
};

} // namespace Private

AcScoreScene::AcScoreScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcScoreSceneData(this))
{
    connect(score(), SIGNAL(lengthChanged(qreal)), SLOT(updateScoreLength(qreal)));

    updateTuningLineList();
}

AcScoreScene::~AcScoreScene()
{
    delete d;
}

void AcScoreScene::updateScoreProperty(const QString &propertyName)
{
    if ("tunings" == propertyName)
        updateTuningLineList();
}

void AcScoreScene::updateScoreLength(qreal scoreLength)
{
    d->updateLength(scoreLength);
}

void AcScoreScene::updateTuningLineList()
{
    MiList *tunings = score()->tunings();
    for (int i = 0;  i < tunings->count();  ++i) {
        AcTuning *tuning = tunings->at<AcTuning>(i);
        connect(tuning, SIGNAL(propertyChanged(int)), SLOT(updateTuningLineProperties()), Qt::UniqueConnection);
        d->updateTuning(tuning, i);
    }
    d->removeUnusedTuningItems();
}

void AcScoreScene::updateTuningLineProperties()
{
    MiList *tunings = score()->tunings();
    for (int i = 0;  i < tunings->count();  ++i)
        d->updateTuning(tunings->at<AcTuning>(i), i);
}
