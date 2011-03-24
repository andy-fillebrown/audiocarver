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

#ifndef GL_NODE_H
#define GL_NODE_H

#include <QtCore/QObject>

#include <glsceneplugin/glscene_global.h>

namespace GL {

class Root;

class GLSCENE_EXPORT Node : public QObject
{
    Q_OBJECT

public:
    Node(QObject *parent = 0);
    virtual ~Node();

    virtual bool isRoot() const { return false; }
    Root *root() const;

    virtual void drawLines(bool picking = false);
    virtual void drawTriangles(bool picking = false);

public slots:
    virtual void changeSubArrayId(int from, int to);
};

} // namespace GL

#endif // GL_NODE_H
