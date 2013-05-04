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

#include "ac_gui_undo_viewsettingscommand.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"

using namespace Ac;

namespace Undo {

ViewSettingsCommand::ViewSettingsCommand(QUndoCommand *parent)
    :   Command(parent)
{
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    _oldTimePos = vm->position(TimePositionRole);
    _oldPitchPos = vm->position(PitchPositionRole);
    _oldControlPos = vm->position(ControlPositionRole);
    _oldTimeScale = vm->scale(TimeScaleRole);
    _oldPitchScale = vm->scale(PitchScaleRole);
    _oldControlScale = vm->scale(ControlScaleRole);
}

int ViewSettingsCommand::id() const
{
    return ViewSettingsCommandId;
}

bool ViewSettingsCommand::mergeWith(const QUndoCommand *other)
{
    if (ViewSettingsCommandId != other->id())
        return false;
    updateNewData();
    return true;
}

void ViewSettingsCommand::redo()
{
    if (!isEnabled()) {
        updateNewData();
        enable();
        return;
    }
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    vm->setPosition(TimePositionRole, _newTimePos);
    vm->setPosition(PitchPositionRole, _newPitchPos);
    vm->setPosition(ControlPositionRole, _newControlPos);
    vm->setScale(TimeScaleRole, _newTimeScale);
    vm->setScale(PitchScaleRole, _newPitchScale);
    vm->setScale(ControlScaleRole, _newControlScale);
    vm->updateViews();
}

void ViewSettingsCommand::undo()
{
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    vm->setPosition(TimePositionRole, _oldTimePos);
    vm->setPosition(PitchPositionRole, _oldPitchPos);
    vm->setPosition(ControlPositionRole, _oldControlPos);
    vm->setScale(TimeScaleRole, _oldTimeScale);
    vm->setScale(PitchScaleRole, _oldPitchScale);
    vm->setScale(ControlScaleRole, _oldControlScale);
    vm->updateViews();
}

void ViewSettingsCommand::updateNewData()
{
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    _newTimePos = vm->position(TimePositionRole);
    _newPitchPos = vm->position(PitchPositionRole);
    _newControlPos = vm->position(ControlPositionRole);
    _newTimeScale = vm->scale(TimeScaleRole);
    _newPitchScale = vm->scale(PitchScaleRole);
    _newControlScale = vm->scale(ControlScaleRole);
}

}
