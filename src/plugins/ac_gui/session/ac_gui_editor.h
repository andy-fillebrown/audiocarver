/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_GUI_EDITOR_H
#define AC_GUI_EDITOR_H

#include <mi_gui_base_editor.h>

class IAggregate;

namespace Gui {

class Editor : public Base::Editor
{
    IAggregate *_ss;

public:
    Editor();
    ~Editor();

protected:
    ISelectionSet *currentSelection() const;
    void undo();
    void redo();
    void cut();
    void copy() const;
    void paste();
    void selectAll();
};

}

#endif
