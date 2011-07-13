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

#ifndef AC_VALUESCENE_H
#define AC_VALUESCENE_H

#include <ac_scaledscene.h>

namespace Private {

class AcValueSceneData;

} // namespace Private

class AC_SCENE_EXPORT AcValueScene : public AcScaledScene
{
    Q_OBJECT

public:
    AcValueScene(QObject *parent = 0);
    virtual ~AcValueScene();

    static AcValueScene *instance();

protected:
    virtual void updateViewSettingsProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcValueScene)
    Private::AcValueSceneData *d;
};

#endif // AC_VALUESCENE_H
