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
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcPitchSceneData
{
public:
    AcPitchScene *q;
    qreal width;

    AcPitchSceneData(AcPitchScene *q)
        :   q(q)
        ,   width(10.0f)
    {}

    void init()
    {
        updateSceneRect();
    }

    void updateSceneRect()
    {
        const qreal height = 127.0f * AcScore::instance()->viewSettings()->scaleY();
        q->setSceneRect(0.0f, 0.0f, width, height);
    }
};

} // namespace Private

AcPitchScene::AcPitchScene(QObject *parent)
    :   AcScaledScene(parent)
    ,   d(new AcPitchSceneData(this))
{
    d->init();
}

AcPitchScene::~AcPitchScene()
{
    delete d;
}

void AcPitchScene::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleY" == propertyName)
        d->updateSceneRect();
}
