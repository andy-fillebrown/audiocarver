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

#ifndef AC_PITCHSCENE_H
#define AC_PITCHSCENE_H

#include <ac_graphicsscene.h>

class AcPitchScenePrivate;

class AcPitchScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcPitchScene(QObject *parent = 0);
    ~AcPitchScene();

    static AcPitchScene *instance();

protected slots:
    virtual void updateScore(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcPitchScene)
    AcPitchScenePrivate *d;
};

#endif // AC_PITCHSCENE_H
