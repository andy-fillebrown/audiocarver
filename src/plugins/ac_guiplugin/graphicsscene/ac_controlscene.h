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

#ifndef AC_CONTROLSCENE_H
#define AC_CONTROLSCENE_H

#include <ac_graphicsscene.h>

namespace Private {

class AcControlSceneData;

} // namespace Private

class AcControlScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcControlScene(QObject *parent = 0);
    virtual ~AcControlScene();

    static AcControlScene *instance();

protected slots:
    virtual void updateScoreProperty(int propertyIndex);

private:
    Q_DISABLE_COPY(AcControlScene)
    Private::AcControlSceneData *d;
};

#endif // AC_CONTROLSCENE_H
