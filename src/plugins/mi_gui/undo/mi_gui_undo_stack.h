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

#ifndef MI_GUI_UNDO_STACK_H
#define MI_GUI_UNDO_STACK_H

#include <QUndoStack>
#include "mi_gui_global.h"

class IModelItem;

namespace Undo {

class DataChangeCommand;
class InsertCommand;
class RemoveCommand;

class MI_GUI_EXPORT Stack : public QUndoStack
{
    Q_OBJECT
    QUndoCommand *_command;
    QList<DataChangeCommand*> _dataChanges;
    QList<InsertCommand*> _inserts;
    QList<RemoveCommand*> _removes;
    QList<IModelItem*> _orphanedItems;

public:
    static Stack *instance();

    Stack(QObject *parent = 0);
    ~Stack();

    void beginCommand();
    void endCommand();

protected slots:
    virtual void dataAboutToBeChanged(IModelItem *item, int role);
    virtual void dataChanged(IModelItem *item, int role);
    virtual void itemAboutToBeInserted(IModelItem *list, int index);
    virtual void itemInserted(IModelItem *list, int index);
    virtual void itemAboutToBeRemoved(IModelItem *list, int index);
    virtual void itemRemoved(IModelItem *list, int index);
    virtual void modelReset();
};

}

#endif
