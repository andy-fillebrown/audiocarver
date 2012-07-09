/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

#include "ac_editor.h"

#include <ac_igraphicsviewgroup.h>

namespace Ac {

IAggregator *Editor::init()
{
    return Mi::Editor::init();
}

Editor::~Editor()
{
    qDeleteAll(_viewGroups);
    _viewGroups.clear();
}

void Editor::undo()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::redo()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::cut()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::copy() const
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::paste()
{
    qDebug() << Q_FUNC_INFO;
}

void Editor::selectAll()
{
    qDebug() << Q_FUNC_INFO;
}

} // namespace Ac

namespace Graphics {

using namespace Ac;

IAggregate *ViewManager::init()
{
    return this;
}

IAggregate *ObjectFactory::init()
{
    return this;
}

IAggregator *ObjectFactory::create(int itemType)
{
    switch (itemType) {
    case ScoreItem:
        return 0;
    case TrackItem:
        return 0;
    case TrackListItem:
        return 0;
    case NoteItem:
        return 0;
    case NoteListItem:
        return 0;
    case CurveItem:
        return 0;
    case PitchCurveItem:
        return 0;
    case ControlCurveItem:
        return 0;
    case ControlCurveListItem:
        return 0;
    case GridSettingsItem:
        return 0;
    case GridLine:
        return 0;
    case TimeGridLineItem:
        return 0;
    case TimeGridLineListItem:
        return 0;
    case PitchGridLineItem:
        return 0;
    case PitchGridLineListItem:
        return 0;
    case ControlGridLineItem:
        return 0;
    case ControlGridLineListItem:
        return 0;
    case GraphicsSceneItem:
        return 0;
    case GraphicsViewItem:
        return 0;
    case GraphicsViewGroupItem:
        return 0;
    default:
        return 0;
    }
}

} // namespace Graphics
