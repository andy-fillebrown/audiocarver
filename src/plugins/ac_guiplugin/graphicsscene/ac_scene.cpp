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

#include "ac_scene.h"

SceneNoteItem::SceneNoteItem(const QModelIndex &index)
    :   SceneItem(index)
    ,   _pitchCurve(new GraphicsCurveItem)
    ,   _velocityLine(new QGraphicsLineItem)
{
    _pitchCurve->setData(0, quintptr(this));
    PointList pts = _index.model()->data(_index, PointsRole).value<PointList>();
    foreach (const Point &pt, pts) {
        GraphicsCurvePointItem *ptItem = new GraphicsCurvePointItem;
        ptItem->setPos(pt.pos);
        _pitchCurve->appendPoint(ptItem);
    }
    _pitchCurve->update();
    _velocityLine->setData(0, quintptr(this));
}

void SceneManager::rowsInserted(const QModelIndex &parent, int start, int end)
{
    if (!_model)
        return;
    ItemType type = ItemType(_model->data(parent, ItemTypeRole).toInt());
    if (ListItem == type) {
        ItemType listType = ItemType(_model->data(parent, ListTypeRole).toInt());
        switch (listType) {
        case TrackItem: {
            SceneTrackItem *track = new SceneTrackItem(_model->index(start, 0, parent));
            _score->insertTrack(start, track);
            break;
        }
        case NoteItem: {
            SceneTrackItem *track = _score->trackAt(_model->parent(parent).row());
            SceneNoteItem *note = new SceneNoteItem(_model->index(start, 0, parent));
            track->appendNote(note);
            break;
        }
        default:
            break;
        }
    }
}
