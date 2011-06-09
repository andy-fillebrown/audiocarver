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
#include <ac_barline.h>
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
    QList<QGraphicsLineItem*> barlineItems;
    QList<QGraphicsLineItem*> tuningItems;

    AcScoreSceneData(AcScoreScene *q)
        :   q(q)
        ,   scoreRectItem(q->addRect(0.0f, 0.0f, 0.0f, 0.0f))
    {
        updateLength();
    }

    void updateLength()
    {
        qreal scoreLength = q->score()->length();
        scoreRectItem->setRect(0.0f, 0.0f, scoreLength, 127.0f);
        q->setSceneRect(scoreRectItem->rect());
        foreach (QGraphicsLineItem *tuningItem, tuningItems) {
            QLineF line = tuningItem->line();
            line.setLength(scoreLength);
            tuningItem->setLine(line);
        }
    }

    void updateBarlineItem(int index, AcBarline *barline)
    {
        while (barlineItems.count() < index + 1)
            barlineItems.append(q->addLine(QLineF()));
        QGraphicsLineItem *barlineItem = barlineItems.at(index);
        const qreal x = barline->location();
        barlineItem->setLine(x, 0.0f, x, 127.0f);
        barlineItem->setPen(QPen(barline->color()));
    }

    void removeUnusedBarlineItems()
    {
        while (q->score()->barlines().count() < barlineItems.count()) {
            delete barlineItems.last();
            barlineItems.removeLast();
        }
    }

    void updateTuningItem(int index, AcTuning *tuning)
    {
        while (tuningItems.count() < index + 1)
            tuningItems.append(q->addLine(QLineF()));
        QGraphicsLineItem *tuningItem = tuningItems.at(index);
        const qreal y = 127.0f - tuning->location();
        const qreal scoreLength = q->score()->length();
        tuningItem->setLine(0.0f, y, scoreLength, y);
        tuningItem->setPen(QPen(tuning->color()));
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

AcScoreScene::AcScoreScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcScoreSceneData(this))
{
    updateBarlines();
    updateTunings();
}

AcScoreScene::~AcScoreScene()
{
    delete d;
}

void AcScoreScene::updateScoreProperty(const QString &propertyName)
{
    if ("barlines" == propertyName)
        updateBarlines();
    else if ("tunings" == propertyName)
        updateTunings();
    else if ("length" == propertyName)
        d->updateLength();
}

void AcScoreScene::updateBarlines()
{
    for (int i = 0;  i < score()->barlines().count();  ++i) {
        AcBarline *barline = score()->barlines().at(i);
        connect(barline, SIGNAL(propertyChanged(QString)), SLOT(updateBarlineProperties()), Qt::UniqueConnection);
        d->updateBarlineItem(i, barline);
    }
    d->removeUnusedBarlineItems();
}

void AcScoreScene::updateBarlineProperties()
{
    for (int i = 0;  i < score()->barlines().count();  ++i)
        d->updateBarlineItem(i, score()->barlines().at(i));
}

void AcScoreScene::updateTunings()
{
    for (int i = 0;  i < score()->tunings().count();  ++i) {
        AcTuning *tuning = score()->tunings().at(i);
        connect(tuning, SIGNAL(propertyChanged(QString)), SLOT(updateTuningProperties()), Qt::UniqueConnection);
        d->updateTuningItem(i, tuning);
    }
    d->removeUnusedTuningItems();
}

void AcScoreScene::updateTuningProperties()
{
    for (int i = 0;  i < score()->tunings().count();  ++i)
        d->updateTuningItem(i, score()->tunings().at(i));
}
