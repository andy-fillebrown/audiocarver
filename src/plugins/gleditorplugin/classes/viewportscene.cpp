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

#include "viewportscene.h"

#include <gleditorplugin/nodes/axesnode.h>
#include <glsceneplugin/classes/root.h>

using namespace GL;
using namespace GL::Internal;

namespace GL {
namespace Internal {

class ViewportScenePrivate
{
public:
    ViewportScene *q;
    Root *root;
    AxesNode *axes;

    ViewportScenePrivate(ViewportScene *q)
        :   q(q)
        ,   root(new Root(q))
        ,   axes(0)
    {
    }

    ~ViewportScenePrivate()
    {
        axes = 0;
        root = 0;
        q = 0;
    }

    void init()
    {
        root->initializeBuffers(1024, 4096);
        axes = new AxesNode(root);
    }

    void destroy()
    {
        root->destroyBuffers();
    }
};

} // namespace Internal
} // namespace GL

ViewportScene::ViewportScene(QObject *parent)
    :   Scene(parent)
    ,   d(new ViewportScenePrivate(this))
{
}

ViewportScene::~ViewportScene()
{
    delete d;  d = 0;
}

Root *ViewportScene::rootNode() const
{
    return d->root;
}

void ViewportScene::initialize()
{
    d->init();
}

void ViewportScene::destroy()
{
}

bool ViewportScene::drawStatic(bool picking)
{
    d->root->drawLines(picking);
    return true;
}
