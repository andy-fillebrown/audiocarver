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

#include "sceneimpl.h"

#include <ac_sceneplugin/classes/graphicsscene.h>

using namespace AudioCarver;
using namespace AudioCarver::Internal;

namespace AudioCarver {
namespace Internal {

class SceneImplData
{
public:
    GraphicsScene *scene;

    SceneImplData(SceneImpl *q)
        :   scene(new GraphicsScene(q))
    {}
};

} // namespace Internal
} // namespace AudioCarver

SceneImpl::SceneImpl()
    :   d(new SceneImplData(this))
{}

SceneImpl::~SceneImpl()
{
    delete d;
}

QGraphicsScene *SceneImpl::scene() const
{
    return d->scene;
}
