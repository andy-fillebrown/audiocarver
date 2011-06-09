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

#ifndef MI_ISCENE_H
#define MI_ISCENE_H

#include <QObject>
#include <mi_scene_global.h>

class QGraphicsScene;

class MI_SCENE_EXPORT MiIScene : public QObject
{
    Q_OBJECT

public:
    MiIScene(QObject *parent = 0);
    virtual ~MiIScene() {}

    static MiIScene *instance();

    virtual QGraphicsScene *scene() const = 0;

private:
    Q_DISABLE_COPY(MiIScene)
};

#endif // MI_ISCENE_H
