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

#ifndef AC_GUI_UNDO_VIEWSETTINGSCOMMAND_H
#define AC_GUI_UNDO_VIEWSETTINGSCOMMAND_H

#include <mi_gui_undo_command.h>

namespace Undo {

class ViewSettingsCommand : public Command
{
    qreal _oldTimePos;
    qreal _oldPitchPos;
    qreal _oldControlPos;
    qreal _oldTimeScale;
    qreal _oldPitchScale;
    qreal _oldControlScale;
    qreal _newTimePos;
    qreal _newPitchPos;
    qreal _newControlPos;
    qreal _newTimeScale;
    qreal _newPitchScale;
    qreal _newControlScale;

protected:
    ViewSettingsCommand(QUndoCommand *parent = 0);

    int id() const;
    bool mergeWith(const QUndoCommand *other);
    void redo();
    void undo();

private:
    void updateNewData();
};

}

#endif
