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

#include <ac_guideline.h>
#include <ac_score.h>

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
        updateLength(q->score()->length());
    }

    void updateLength(qreal scoreLength)
    {
        scoreRectItem->setRect(0.0f, 0.0f, scoreLength, 127.0f);

        foreach (QGraphicsLineItem *tuningItem, tuningItems) {
            QLineF line = tuningItem->line();
            line.setLength(scoreLength);
            tuningItem->setLine(line);
        }
    }

    void updateBarlineItem(int index, AcGuideline *barline)
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
        MiList *barlines = q->score()->barlines();
        while (barlines->count() < barlineItems.count())
            barlineItems.removeLast();
    }

    void updateTuningItem(int index, AcGuideline *tuning)
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
        MiList *tunings = q->score()->tunings();
        while (tunings->count() < tuningItems.count())
            tuningItems.removeLast();
    }
};

} // namespace Private

AcScoreScene::AcScoreScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcScoreSceneData(this))
{
    connect(score(), SIGNAL(lengthChanged(qreal)), SLOT(updateScoreLength(qreal)));

    updateBarlines();
    updateTunings();
}

AcScoreScene::~AcScoreScene()
{
    delete d;
}

void AcScoreScene::updateScoreProperty(const QString &propertyName)
{
    if ("barlines" == propertyName) {
        updateBarlines();
        return;
    }
    if ("tunings" == propertyName) {
        updateTunings();
        return;
    }
}

void AcScoreScene::updateScoreLength(qreal scoreLength)
{
    d->updateLength(scoreLength);
}

void AcScoreScene::updateBarlines()
{
    MiList *barlines = score()->barlines();
    for (int i = 0;  i < barlines->count();  ++i) {
        AcGuideline *barline = barlines->at<AcGuideline>(i);
        connect(barline, SIGNAL(propertyChanged(int)), SLOT(updateBarlineProperties()), Qt::UniqueConnection);
        d->updateBarlineItem(i, barline);
    }
    d->removeUnusedBarlineItems();
}

void AcScoreScene::updateBarlineProperties()
{
    MiList *barlines = score()->barlines();
    for (int i = 0;  i < barlines->count();  ++i)
        d->updateBarlineItem(i, barlines->at<AcGuideline>(i));
}

void AcScoreScene::updateTunings()
{
    MiList *tunings = score()->tunings();
    for (int i = 0;  i < tunings->count();  ++i) {
        AcGuideline *tuning = tunings->at<AcGuideline>(i);
        connect(tuning, SIGNAL(propertyChanged(int)), SLOT(updateTuningProperties()), Qt::UniqueConnection);
        d->updateTuningItem(i, tuning);
    }
    d->removeUnusedTuningItems();
}

void AcScoreScene::updateTuningProperties()
{
    MiList *tunings = score()->tunings();
    for (int i = 0;  i < tunings->count();  ++i)
        d->updateTuningItem(i, tunings->at<AcGuideline>(i));
}
