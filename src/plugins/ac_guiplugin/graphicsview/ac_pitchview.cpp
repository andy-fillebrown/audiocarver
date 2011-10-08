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

#include "ac_pitchview.h"

#include <ac_mainwidget.h>

class AcPitchViewPrivate
{
public:
    AcPitchViewPrivate()
    {}

    virtual ~AcPitchViewPrivate()
    {}
};

AcPitchView::AcPitchView(QGraphicsScene *scene, QWidget *parent)
    :   AcEditorView(scene, parent)
    ,   d(new AcPitchViewPrivate)
{}

AcPitchView::~AcPitchView()
{
    delete d;
}

void AcPitchView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    AcMainWidget *widget = qobject_cast<AcMainWidget*>(parent());
    if (!widget)
        return;
    widget->test();
}
