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

#ifndef AC_ITEM_H
#define AC_ITEM_H

#include <ac_core_enums.h>
#include <ac_point.h>
#include <QGraphicsItem>
#include <QGraphicsScene>

class AcScore
{
public:
    QList<QGraphicsScene*> scenes;

    AcScore()
    {
        for (int i = 0;  i < SceneTypeCount;  ++i)
            scenes.append(new QGraphicsScene);
    }

    ~AcScore()
    {
        qDeleteAll(scenes);
    }
};

class AcTrack
{
public:
    qreal vol;
    QGraphicsRectItem *pitchGfx;
    QGraphicsRectItem *ctrlGfx;

    AcTrack(AcScore *score)
        :   vol(0.9f)
        ,   pitchGfx(new QGraphicsRectItem)
        ,   ctrlGfx(new QGraphicsRectItem)
    {
        score->scenes[PitchScene]->addItem(pitchGfx);
        score->scenes[ControlScene]->addItem(ctrlGfx);
    }
};

class AcNote
{
public:
    qreal vol;
    AcPoints pitchPts;
    AcPoints volPts;
    QGraphicsPathItem *pitchGfx;
    QGraphicsPathItem *ctrlGfx;

    AcNote(AcTrack *track)
        :   vol(1.0f)
        ,   pitchGfx(new QGraphicsPathItem(track->pitchGfx))
        ,   ctrlGfx(new QGraphicsPathItem(track->ctrlGfx))
    {}

    void updatePitchGfx()
    {

    }

    void updateCtrlGfx()
    {

    }
};

#endif // AC_ITEM_H
