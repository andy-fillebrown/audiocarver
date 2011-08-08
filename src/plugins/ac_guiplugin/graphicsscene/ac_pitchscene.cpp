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

class AcPitchScenePrivate
{
public:
    AcPitchScene *q;

    AcPitchScenePrivate(AcPitchScene *q)
        :   q(q)
    {}

    void init()
    {
        updateSceneRect();
    }

    void updateSceneRect()
    {
        q->setSceneRect(0.0f, 0.0f, AcScore::instance()->length(), 127.0f);
    }
};

static AcPitchScene *instance = 0;

AcPitchScene::AcPitchScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcPitchScenePrivate(this))
{
    ::instance = this;
    d->init();
    Q_CONNECT(AcScore::instance(), SIGNAL(changed(int,QVariant)), this, SLOT(updateScore(int,QVariant)));
}

AcPitchScene::~AcPitchScene()
{
    delete d;
}

AcPitchScene *AcPitchScene::instance()
{
    return ::instance;
}

void AcPitchScene::updateScore(int i, const QVariant &value)
{
    if (AcScore::LengthIndex == i)
        d->updateSceneRect();
}
