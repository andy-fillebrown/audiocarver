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

#ifndef AC_LABELSCENE_H
#define AC_LABELSCENE_H

#include <ac_graphicsscene.h>

class AcLabelScenePrivate;

class AcLabelScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcLabelScene(QObject *parent = 0);
    ~AcLabelScene();

//protected slots:
//    virtual void updateViewSettings(int i, const QVariant &value) = 0;

private:
    Q_DISABLE_COPY(AcLabelScene)
    AcLabelScenePrivate *d;
};

#endif // AC_LABELSCENE_H
