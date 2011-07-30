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

#include <ac_scaledscene.h>

namespace Private {

class AcPitchSceneData;

} // namespace Private

class AcPitchScene : public AcScaledScene
{
    Q_OBJECT

public:
    AcPitchScene(QObject *parent = 0);
    virtual ~AcPitchScene();

    static AcPitchScene *instance();

protected:
    virtual void updateViewSettingsProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcPitchScene)
    Private::AcPitchSceneData *d;
};

#endif // AC_PITCHSCENE_H
