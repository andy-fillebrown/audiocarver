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

#include "ac_volumescene.h"
//#include <ac_score.h>

class AcVolumeScenePrivate
{
public:
    AcVolumeScene *q;

    AcVolumeScenePrivate(AcVolumeScene *q)
        :   q(q)
    {}

    virtual ~AcVolumeScenePrivate()
    {}

    void init()
    {
        updateSceneRect();
    }

    void updateSceneRect()
    {
//        q->setSceneRect(0.0f, 0.0f, AcScore::instance()->length(), 1.0f);
        q->setSceneRect(0.0f, 0.0f, 128.0f, 1.0f);
    }
};

static AcVolumeScene *instance = 0;

AcVolumeScene::AcVolumeScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcVolumeScenePrivate(this))
{
    ::instance = this;
    d->init();
//    Q_CONNECT(AcScore::instance(), SIGNAL(changed(int,QVariant)), this, SLOT(updateScore(int,QVariant)));
}

AcVolumeScene::~AcVolumeScene()
{
    delete d;
}

AcVolumeScene *AcVolumeScene::instance()
{
    return ::instance;
}

//void AcVolumeScene::updateScore(int i, const QVariant &valuei)
//{
//    if (Score::Length == i)
//        d->updateSceneRect();
//}
