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

#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <base/editor.h>
#include <QList>

class IGraphicsViewGroup;

namespace Session {
namespace Gui {

class Editor : public Base::Editor
{
    QList<IGraphicsViewGroup*> _viewGroups;

public:
    Editor()
    {}

    IUnknown *initialize();
    ~Editor();

protected:
    void undo();
    void redo();
    void cut();
    void copy() const;
    void paste();
    void selectAll();
};

}
}

#endif
