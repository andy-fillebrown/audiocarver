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

#include "ac_graphicsscene.h"
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcGraphicsSceneData
{
public:
    AcScore *score;

    AcGraphicsSceneData()
        :   score(AcScore::instance())
    {}
};

} // namespace Private

AcGraphicsScene::AcGraphicsScene(QObject *parent)
    :   MiGraphicsScene(parent)
    ,   d(new AcGraphicsSceneData)
{
    connect(d->score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
}

AcGraphicsScene::~AcGraphicsScene()
{
    delete d;
}

AcScore *AcGraphicsScene::score() const
{
    return d->score;
}

void AcGraphicsScene::updateScoreProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
