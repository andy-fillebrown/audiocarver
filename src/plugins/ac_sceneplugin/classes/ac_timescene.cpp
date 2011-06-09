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

#include "ac_timescene.h"
#include <ac_barline.h>
#include <ac_score.h>
#include <ac_tuning.h>
#include <ac_viewsettings.h>
#include <mi_list.h>
#include <QGraphicsTextItem>

using namespace Private;

namespace Private {

class AcTimeSceneData
{
public:
    AcTimeScene *q;
    QFont font;
    QFontMetrics fontMetrics;
    QList<QGraphicsTextItem*> barlineItems;

    AcTimeSceneData(AcTimeScene *q)
        :   q(q)
        ,   font("Arial", 8)
        ,   fontMetrics(font)
    {}

    void updateBarlineItem(int index, AcBarline *barline)
    {
        while (barlineItems.count() < index + 1)
            barlineItems.append(q->addText("", font));
        QGraphicsTextItem *barlineItem = barlineItems.at(index);
        barlineItem->setPlainText(barline->text());
        QRect textRect = fontMetrics.boundingRect(barline->text());
        qreal scaleX = q->score()->viewSettings()->scaleX();
        barlineItem->setPos((barline->location() * scaleX) - (textRect.width() / 2), 10.0f);
    }

    void removeUnusedBarlineItems()
    {
        while (q->score()->barlines().count() <barlineItems.count()) {
            delete barlineItems.last();
            barlineItems.removeLast();
        }
    }
};

} // namespace Private

static AcTimeScene *instance = 0;

AcTimeScene::AcTimeScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcTimeSceneData(this))
{
    ::instance = this;
    connect(score()->viewSettings(), SIGNAL(propertyChanged(QString)), SLOT(updateViewSettingsProperty(QString)));
    updateBarlines();
}

AcTimeScene::~AcTimeScene()
{
    delete d;
}

AcTimeScene *AcTimeScene::instance()
{
    return ::instance;
}

void AcTimeScene::updateScoreProperty(const QString &propertyName)
{
    if ("barlines" == propertyName)
        updateBarlines();
}

void AcTimeScene::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleX" == propertyName)
        updateBarlineProperties();
}

void AcTimeScene::updateBarlines()
{
    for (int i = 0;  i < score()->barlines().count();  ++i) {
        AcBarline *barline = score()->barlines().at(i);
        connect(barline, SIGNAL(propertyChanged(QString)), SLOT(updateBarlineProperties()), Qt::UniqueConnection);
        d->updateBarlineItem(i, barline);
    }
    d->removeUnusedBarlineItems();
}

void AcTimeScene::updateBarlineProperties()
{
    for (int i = 0;  i < score()->barlines().count();  ++i)
        d->updateBarlineItem(i, score()->barlines().at(i));
}
