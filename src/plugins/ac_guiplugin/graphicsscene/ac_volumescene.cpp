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

#include "ac_controlscene.h"
#include <ac_score.h>

using namespace Private;

namespace Private {

class AcControlSceneData
{
public:
    AcControlScene *q;

    AcControlSceneData(AcControlScene *q)
        :   q(q)
    {}

    void init()
    {
        updateSceneRect();
    }

    void updateSceneRect()
    {
        q->setSceneRect(0.0f, 0.0f, AcScore::instance()->length(), 1.0f);
    }
};

} // namespace Private

static AcControlScene *instance = 0;

AcControlScene::AcControlScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcControlSceneData(this))
{
    ::instance = this;
    d->init();
    connect(AcScore::instance(), SIGNAL(propertyChanged(int)), SLOT(updateScoreProperty(int)));
}

AcControlScene::~AcControlScene()
{
    delete d;
}

AcControlScene *AcControlScene::instance()
{
    return ::instance;
}

void AcControlScene::updateScoreProperty(int propertyIndex)
{
    if (AcScore::Length == propertyIndex)
        d->updateSceneRect();
}
