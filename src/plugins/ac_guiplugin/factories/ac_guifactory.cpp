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

#include "ac_guifactory.h"
#include <ac_graphicsitem.h>
#include <ac_scenemanager.h>
#include <ac_score.h>
#include <ac_viewsettings.h>
#include <mi_fontsettings.h>
#include <QVariant>

static AcGuiFactory *instance = 0;

AcGuiFactory::AcGuiFactory(QObject *parent)
    :   QObject(parent)
    ,   d_ptr(new AcGuiFactoryPrivate(this))
{
    ::instance = this;
}

AcGuiFactory *AcGuiFactory::instance()
{
    return ::instance;
}

AcSceneManager *AcGuiFactory::createSceneManager(QObject *parent)
{
    AcSceneManager *sm = new AcSceneManager(parent ? parent : this);
    Q_D(AcGuiFactory);
    AcScore *score = d->score();
    AcViewSettings *viewSettings = score->viewSettings();
    MiFontSettings *fontSettings = score->fontSettings();
    Q_CONNECT(score, SIGNAL(changed(int,QVariant)), sm, SLOT(updateScore(int,QVariant)));
    Q_CONNECT(viewSettings, SIGNAL(changed(int,QVariant)), sm, SLOT(updateViewSettings(int)));
    Q_CONNECT(fontSettings, SIGNAL(changed(int,QVariant)), sm, SLOT(updateFontSettings(int,QVariant)));
    for (int i = 0;  i < score->propertyCount();  ++i)
        sm->updateScore(i, score->propertyValue(i));
    for (int i = 0;  i < viewSettings->propertyCount();  ++i)
        sm->updateViewSettings(i);
    for (int i = 0;  i < fontSettings->propertyCount();  ++i)
        sm->updateFontSettings(i, fontSettings->propertyValue(i));
    return sm;
}

AcScore *AcGuiFactoryPrivate::score()
{
    return AcScore::instance();
}

void AcGuiFactoryPrivate::connectGraphicsItem(AcGraphicsItem *item, MiObject *object)
{
    Q_CONNECT(object, SIGNAL(changed(int,QVariant)), item, SLOT(updateDataObject(int,QVariant)));
}
