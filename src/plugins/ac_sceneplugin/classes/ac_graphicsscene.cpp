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

#include "ac_graphicsscene.h"

#include <ac_score.h>

#include <QGraphicsRectItem>

using namespace Private;

namespace Private {

class AcGraphicsSceneData
{
public:
    AcGraphicsScene *q;
    AcScore *score;
    QGraphicsRectItem *scoreRectItem;

    AcGraphicsSceneData(AcGraphicsScene *q)
        :   q(q)
        ,   score(AcScore::instance())
        ,   scoreRectItem(q->addRect(0.0f, 0.0f, 0.0f, 0.0f))
    {
        updateScoreRectItem();
    }

    void updateScoreRectItem()
    {
        scoreRectItem->setRect(0.0f, 0.0f, score->length(), 127.0f);
    }
};

} // namespace Private

AcGraphicsScene::AcGraphicsScene(QObject *parent)
    :   MiGraphicsScene(parent)
    ,   d(new AcGraphicsSceneData(this))
{
    connect(d->score, SIGNAL(propertyChanged(int)), SLOT(updateScoreProperty(int)));
}

AcGraphicsScene::~AcGraphicsScene()
{
    delete d;
}

void AcGraphicsScene::updateScoreProperty(int propertyIndex)
{
    const QString propName = d->score->propertyName(propertyIndex);
    if (propName == "length")
        d->updateScoreRectItem();
}
