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

#include "ac_valuescene.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcValueSceneData
{
public:
    AcValueScene *q;

    AcValueSceneData(AcValueScene *q)
        :   q(q)
    {}

    qreal height() const
    {
        return AcScore::instance()->viewSettings()->valueScale();
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

} // namespace Private

static AcValueScene *instance = 0;

AcValueScene::AcValueScene(QObject *parent)
    :   AcScaledScene(parent)
    ,   d(new AcValueSceneData(this))
{
    ::instance = this;
    d->init();
}

AcValueScene::~AcValueScene()
{
    delete d;
}

AcValueScene *AcValueScene::instance()
{
    return ::instance;
}

void AcValueScene::updateViewSettingsProperty(int propertyIndex)
{
    if (AcViewSettings::ValueScale == propertyIndex)
        d->updateSceneRect();
}
