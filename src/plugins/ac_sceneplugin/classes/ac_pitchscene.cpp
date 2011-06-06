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

using namespace Private;

namespace Private {

class AcPitchSceneData
{
public:
    AcPitchSceneData()
    {}
};

} // namespace Private

AcPitchScene::AcPitchScene(QObject *parent)
    :   AcGraphicsScene(parent)
    ,   d(new AcPitchSceneData)
{
}

AcPitchScene::~AcPitchScene()
{
    delete d;
}

void AcPitchScene::updateScoreProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
