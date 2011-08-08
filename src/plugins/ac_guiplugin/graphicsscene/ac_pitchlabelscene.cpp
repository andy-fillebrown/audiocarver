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

#include "ac_pitchlabelscene.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

class AcPitchLabelScenePrivate
{
public:
    AcPitchLabelScene *q;

    AcPitchLabelScenePrivate(AcPitchLabelScene *q)
        :   q(q)
    {}

    qreal height() const
    {
        return 127.0f * AcScore::instance()->viewSettings()->pitchScale();
    }

    void init()
    {
        initSceneRect();
    }

    void initSceneRect()
    {
        q->setSceneRect(0.0f, 0.0f, 10.0f, height());
    }

    void updateSceneRect()
    {
        q->setSceneRect(0.0f, 0.0f, q->width(), height());
    }
};

static AcPitchLabelScene *instance = 0;

AcPitchLabelScene::AcPitchLabelScene(QObject *parent)
    :   AcLabelScene(parent)
    ,   d(new AcPitchLabelScenePrivate(this))
{
    ::instance = this;
    d->init();
}

AcPitchLabelScene::~AcPitchLabelScene()
{
    delete d;
}

AcPitchLabelScene *AcPitchLabelScene::instance()
{
    return ::instance;
}

void AcPitchLabelScene::updateViewSettings(int i, const QVariant &value)
{
    if (AcViewSettings::PitchScaleIndex == i)
        d->updateSceneRect();
}
