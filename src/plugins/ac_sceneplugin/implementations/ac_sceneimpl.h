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

#ifndef AC_SCENEIMPL_H
#define AC_SCENEIMPL_H

#include <mi_iscene.h>

namespace Private {

class AcSceneImplData;

class AcSceneImpl : public MiIScene
{
public:
    AcSceneImpl();
    virtual ~AcSceneImpl();

    virtual QGraphicsScene *scene() const;

private:
    Q_DISABLE_COPY(AcSceneImpl)
    AcSceneImplData *d;
};

} // namespace Private

#endif // AC_SCENEIMPL_H