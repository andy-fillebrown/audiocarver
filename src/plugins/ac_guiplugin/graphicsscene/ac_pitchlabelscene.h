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

#ifndef AC_PITCHLABELSCENE_H
#define AC_PITCHLABELSCENE_H

#include <ac_labelscene.h>

class AcPitchLabelScenePrivate;

class AcPitchLabelScene : public AcLabelScene
{
    Q_OBJECT

public:
    AcPitchLabelScene(QObject *parent = 0);
    virtual ~AcPitchLabelScene();

    static AcPitchLabelScene *instance();

protected:
    virtual void updateViewSettings(int i);

private:
    Q_DISABLE_COPY(AcPitchLabelScene)
    AcPitchLabelScenePrivate *d;
};

#endif // AC_PITCHLABELSCENE_H
