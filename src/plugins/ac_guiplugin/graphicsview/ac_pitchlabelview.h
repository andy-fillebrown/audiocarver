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

#ifndef AC_PITCHLABELVIEW_H
#define AC_PITCHLABELVIEW_H

#include <ac_graphicsview.h>

class PitchLabelViewPrivate;

class PitchLabelView : public GraphicsView
{
    Q_OBJECT

public:
    PitchLabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~PitchLabelView();

protected:
    qreal sceneHeight() const { return 127.0f; }

private:
    Q_DISABLE_COPY(PitchLabelView)
    PitchLabelViewPrivate *d;
};

#endif // AC_PITCHLABELVIEW_H
