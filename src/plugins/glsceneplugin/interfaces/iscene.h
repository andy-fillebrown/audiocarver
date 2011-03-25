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

#ifndef GL_ISCENE_H
#define GL_ISCENE_H

#include <glsceneplugin/glscene_global.h>

#include <QtCore/QObject>
#include <QtCore/QRectF>

namespace GL {

class GLSCENE_EXPORT IScene : public QObject
{
    Q_OBJECT

public:
    IScene(QObject *parent = 0);
    virtual ~IScene();

    virtual void initialize() = 0;
    virtual void destroy() = 0;

    virtual bool drawBackground() = 0;
    virtual bool drawStatic() = 0;
    virtual bool drawModel() = 0;
    virtual bool drawEdit() = 0;
    virtual bool drawAnimation(qreal time) = 0;
    virtual bool drawOverlay() = 0;
};

} // namespace GL

#endif // GL_ISCENE_H
