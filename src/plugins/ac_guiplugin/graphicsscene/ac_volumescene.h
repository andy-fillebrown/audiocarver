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

#ifndef AC_VOLUMESCENE_H
#define AC_VOLUMESCENE_H

#include <ac_graphicsscene.h>

class AcVolumeScenePrivate;

class AcVolumeScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcVolumeScene(QObject *parent = 0);
    ~AcVolumeScene();

    static AcVolumeScene *instance();

protected slots:
    virtual void updateScore(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcVolumeScene)
    AcVolumeScenePrivate *d;
};

#endif // AC_VOLUMESCENE_H
