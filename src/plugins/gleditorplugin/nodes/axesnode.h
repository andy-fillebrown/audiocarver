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

#ifndef GL_AXESNODE_H
#define GL_AXESNODE_H

#include <glsceneplugin/classes/node.h>

#include <gleditorplugin/gleditor_global.h>

namespace GL {
namespace Internal {

class AxesNodePrivate;

} // namespace Internal

class GLEDITOR_EXPORT AxesNode : public Node
{
    Q_OBJECT

public:
    AxesNode(Node *parent = 0);
    virtual ~AxesNode();

    virtual void drawLines(bool picking = false);
    virtual void drawTriangles(bool picking = false);

private:
    Internal::AxesNodePrivate *d;
};

} // namespace GL

#endif // GL_AXESNODE_H
