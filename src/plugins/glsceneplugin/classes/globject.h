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

#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QtCore/QObject>

namespace GLScene {

class GLObject : public QObject
{
    Q_OBJECT

public:
    GLObject(QObject *parent = 0);
    virtual ~GLObject();

    virtual bool isRoot() { return false; }

    virtual void drawLines(bool picking = false);
    virtual void drawTriangles(bool picking = false);

public slots:
    void changeSubArrayId(int from, int to);
};

} // namespace GLScene

#endif // GLOBJECT_H
