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

#ifndef ISCENE_H
#define ISCENE_H

#include <sceneplugin/scene_global.h>

#include <QtCore/QObject>

namespace Scene {

class SCENE_EXPORT IScene : public QObject
{
    Q_OBJECT

public:
    IScene(QObject *parent = 0);
protected:
    virtual ~IScene() {}
private:
    Q_DISABLE_COPY(IScene)
};

} // namespace Scene

#endif // ISCENE_H
