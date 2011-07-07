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
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcTimeSceneData
{
public:
    qreal height;

    AcTimeSceneData()
        :   height(10.0f)
    {}
};

} // namespace Private

AcTimeScene::AcTimeScene(QObject *parent)
    :   AcScaledScene(parent)
    ,   d(new AcTimeSceneData)
{}

AcTimeScene::~AcTimeScene()
{
    delete d;
}

void AcTimeScene::updateViewSettingsProperty(const QString &propertyName)
{
    if ("scaleX" == propertyName) {
        const AcScore *score = AcScore::instance();
        const qreal width = score->length() * score->viewSettings()->scaleX();
        setSceneRect(0.0f, 0.0f, width, d->height);
    }
}
