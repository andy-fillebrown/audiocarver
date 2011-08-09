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

#include "ac_volumelabelscene.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

class AcVolumeLabelScenePrivate
{
public:
    AcVolumeLabelScene *q;

    AcVolumeLabelScenePrivate(AcVolumeLabelScene *q)
        :   q(q)
    {}

    virtual ~AcVolumeLabelScenePrivate()
    {}

    qreal height() const
    {
        return AcScore::instance()->viewSettings()->volumeScale();
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

static AcVolumeLabelScene *instance = 0;

AcVolumeLabelScene::AcVolumeLabelScene(QObject *parent)
    :   AcLabelScene(parent)
    ,   d(new AcVolumeLabelScenePrivate(this))
{
    ::instance = this;
    d->init();
}

AcVolumeLabelScene::~AcVolumeLabelScene()
{
    delete d;
}

AcVolumeLabelScene *AcVolumeLabelScene::instance()
{
    return ::instance;
}

void AcVolumeLabelScene::updateViewSettings(int i, const QVariant &value)
{
    if (ViewSettings::VolumeScale == i)
        d->updateSceneRect();
}
