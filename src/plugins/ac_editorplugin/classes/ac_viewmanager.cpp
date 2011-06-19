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

#include "ac_viewmanager.h"
#include <ac_mainwidget.h>
#include <ac_pitchscene.h>
#include <ac_pitchview.h>
#include <ac_score.h>
#include <ac_scorescene.h>
#include <ac_scoreview.h>
#include <ac_timescene.h>
#include <ac_timeview.h>
#include <ac_viewsettings.h>

using namespace Private;

namespace Private {

class AcViewManagerData
{
public:
    AcViewManager *q;
    AcMainWidget *mainWidget;
    AcScoreScene *scoreScene;
    AcScoreView *scoreView;
    AcPitchScene *pitchScene;
    AcPitchView *pitchView;
    AcTimeScene *timeScene;
    AcTimeView *timeView;
    AcScore *score;
    AcViewSettings *viewSettings;

    AcViewManagerData(AcViewManager *q, AcMainWidget *mainWidget)
        :   q(q)
        ,   mainWidget(mainWidget)
        ,   scoreScene(new AcScoreScene(q))
        ,   scoreView(new AcScoreView(scoreScene, mainWidget))
        ,   pitchScene(new AcPitchScene(q))
        ,   pitchView(new AcPitchView(pitchScene, mainWidget))
        ,   timeScene(new AcTimeScene(q))
        ,   timeView(new AcTimeView(timeScene, mainWidget))
        ,   score(AcScore::instance())
        ,   viewSettings(score->viewSettings())
    {}
};

} // namespace Private

AcViewManager::AcViewManager(AcMainWidget *mainWidget)
    :   QObject(mainWidget)
    ,   d(new AcViewManagerData(this, mainWidget))
{
    connect(d->score, SIGNAL(propertyChanged(QString)), SLOT(updateScoreProperty(QString)));
}

AcViewManager::~AcViewManager()
{
    delete d;
}

void AcViewManager::updateScoreProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}

void AcViewManager::updateViewSettingsProperty(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}
