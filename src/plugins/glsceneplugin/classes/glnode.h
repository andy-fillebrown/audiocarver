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

#ifndef GLNODE_H
#define GLNODE_H

#include <QtCore/QObject>

#include <glsceneplugin/glscene_global.h>

namespace GLScene {

class GLRoot;

class GLSCENE_EXPORT GLNode : public QObject
{
    Q_OBJECT

public:
    GLNode(QObject *parent = 0);
    virtual ~GLNode();

    virtual bool isRoot() const { return false; }
    GLRoot *root() const;

    virtual void drawLines(bool picking = false);
    virtual void drawTriangles(bool picking = false);

public slots:
    virtual void changeSubArrayId(int from, int to);
};

} // namespace GLScene

#endif // GLNODE_H
