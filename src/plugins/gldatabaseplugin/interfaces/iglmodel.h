/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef IGLMODEL_H
#define IGLMODEL_H

#include <gldatabaseplugin/gldatabase_global.h>

#include <QtCore/QObject>
#include <QtCore/QRectF>

namespace GLDatabase {

class GLDATABASE_EXPORT IGLModel : public QObject
{
    Q_OBJECT

public:
    IGLModel();
    virtual ~IGLModel();

    virtual void drawStaticGL(const QRectF &frustum) = 0;
    virtual void drawTransientGL(const QRectF &frustum) = 0;
    virtual void drawAnimatedGL(const QRectF &frustum, qreal timeDelta) = 0;
};

} // namespace GLDatabase

#endif // IGLMODEL_H
