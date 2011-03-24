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

#ifndef GL_ROOT_H
#define GL_ROOT_H

#include "node.h"

namespace GL {
namespace Internal {

class RootPrivate;

} // Internal

class GLSCENE_EXPORT Root : public Node
{
    Q_OBJECT

public:
    Root(QObject *parent = 0);
    virtual ~Root();

    virtual bool isRoot() const { return true; }

    virtual void drawLines(bool picking = false);
    virtual void drawTriangles(bool picking = false);

    void releaseBuffers() const;

private:
    Q_DISABLE_COPY(Root)
    Internal::RootPrivate *d;
};

} // namespace GL

#endif // GL_ROOT_H
