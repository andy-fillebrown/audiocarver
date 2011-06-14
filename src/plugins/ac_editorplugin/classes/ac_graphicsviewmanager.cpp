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

#include "ac_graphicsviewmanager.h"
#include <ac_mainwidget.h>
#include <ac_score.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcGraphicsViewManagerData
{
public:
    AcGraphicsViewManager *q;
    AcScore *score;
    AcViewSettings *viewSettings;

    AcGraphicsViewManagerData(AcGraphicsViewManager *q)
        :   q(q)
        ,   score(AcScore::instance())
        ,   viewSettings(score->viewSettings())
    {
        q->connect(score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
    }
};

} // namespace Private

AcGraphicsViewManager::AcGraphicsViewManager(AcMainWidget *mainWidget)
    :   QObject(mainWidget)
    ,   d(new AcGraphicsViewManagerData(this))
{
}

AcGraphicsViewManager::~AcGraphicsViewManager()
{
    delete d;
}

void AcGraphicsViewManager::updateScoreProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}

void AcGraphicsViewManager::updateViewSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
