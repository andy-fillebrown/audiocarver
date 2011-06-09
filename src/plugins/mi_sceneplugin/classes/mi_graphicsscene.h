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

#ifndef MI_GRAPHICSSCENE_H
#define MI_GRAPHICSSCENE_H

#include <QGraphicsScene>

#include <mi_scene_global.h>

class MI_SCENE_EXPORT MiGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MiGraphicsScene(QObject *parent = 0);
    virtual ~MiGraphicsScene() {}

private:
    Q_DISABLE_COPY(MiGraphicsScene)
};

#endif // MI_GRAPHICSSCENE_H