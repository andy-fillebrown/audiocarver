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

#ifndef AC_SCALEDSCENE_H
#define AC_SCALEDSCENE_H

#include <ac_graphicsscene.h>

namespace Private {

class AcScaledSceneData;

} // namespace Private

class AC_SCENE_EXPORT AcScaledScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcScaledScene(QObject *parent = 0);
    virtual ~AcScaledScene();

protected slots:
    virtual void updateViewSettingsProperty(const QString &propertyName) = 0;

private:
    Q_DISABLE_COPY(AcScaledScene)
    Private::AcScaledSceneData *d;
};

#endif // AC_SCALEDSCENE_H
