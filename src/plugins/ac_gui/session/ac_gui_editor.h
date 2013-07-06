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
#include <QList>

namespace Ac {
namespace Gui {

class Editor : public Base::Editor
{
    QList<QString> _dirtyTracks;
    IAggregate *_objectSS;
    IAggregate *_trackSS;
    IAggregate *_noteSS;

public:
    Editor();
    ~Editor();

protected:
    void cut();
    void copy() const;
    void paste();
    void selectAll();
    void createTrack();
    void erase();
    void build();
    void buildSelected();
    void buildAll();
    void startOrStop();
    void start();
    void stop();

    ISelectionSet *currentSelection(int itemType) const;
    void runCommand(int command);
    void beginChangeData(IModelItem *item, int role);
    void endChangeData(IModelItem *item, int role);
    void endInsertItem(IModelItem *list, int index);
    void endRemoveItem(IModelItem *list, int index);
};

}
}

#endif
