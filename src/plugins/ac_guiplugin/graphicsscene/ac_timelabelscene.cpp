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

#include "ac_timelabelscene.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

class AcTimeLabelScenePrivate
{
public:
    AcTimeLabelScene *q;

    AcTimeLabelScenePrivate(AcTimeLabelScene *q)
        :   q(q)
    {}

    virtual ~AcTimeLabelScenePrivate()
    {}

    qreal width() const
    {
        const AcScore *score = AcScore::instance();
        return score->length() * score->viewSettings()->timeScale();
    }

    void init()
    {
        initSceneRect();
    }

    void initSceneRect()
    {
        q->setSceneRect(0.0f, 0.0f, width(), 10.0f);
    }

    void updateSceneRect()
    {
        q->setSceneRect(0.0f, 0.0f, width(), q->height());
    }
};

static AcTimeLabelScene *instance = 0;

AcTimeLabelScene::AcTimeLabelScene(QObject *parent)
    :   AcLabelScene(parent)
    ,   d(new AcTimeLabelScenePrivate(this))
{
    ::instance = this;
    d->init();
}

AcTimeLabelScene::~AcTimeLabelScene()
{
    delete d;
}

AcTimeLabelScene *AcTimeLabelScene::instance()
{
    return ::instance;
}

void AcTimeLabelScene::updateViewSettings(int i)
{
    if (AcViewSettings::TimeScaleIndex == i)
        d->updateSceneRect();
}

void AcTimeLabelScene::updateScore(int i)
{
    if (AcScore::LengthIndex == i)
        d->updateSceneRect();
}
