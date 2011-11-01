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

#ifndef AC_UNDO_H
#define AC_UNDO_H

#include <QUndoStack>

class IModelItem;

class QModelIndex;

class UndoCommandPrivate;
class UndoCommand : public QUndoCommand
{
public:
    ~UndoCommand();

    IModelItem *item() const;

    void enable();

protected:
    UndoCommand(UndoCommandPrivate &dd, QUndoCommand *parent)
        :   QUndoCommand(parent)
        ,   d_ptr(&dd)
    {}

    UndoCommandPrivate *d_ptr;
};

class UndoDataCommandPrivate;
class UndoDataCommand : public UndoCommand
{
public:
    UndoDataCommand(IModelItem *item, QUndoCommand *parent = 0);

    void updateNewData();

    void redo();
    void undo();

private:
    Q_DECLARE_PRIVATE(UndoDataCommand)
};

class UndoListCommandPrivate;
class UndoListCommand : public UndoCommand
{
public:
    ~UndoListCommand();

    void insert();
    void remove();

    bool mergeWith(const QUndoCommand *other);

protected:
    UndoListCommand(UndoListCommandPrivate &dd, QUndoCommand *parent);

private:
    Q_DECLARE_PRIVATE(UndoListCommand)
};

class UndoInsertCommand : public UndoListCommand
{
public:
    UndoInsertCommand(IModelItem *item, int row, const QModelIndex &parentIndex, QUndoCommand *parent = 0);

    void redo() { remove(); }
    void undo() { insert(); }
};

class UndoRemoveCommand : public UndoListCommand
{
public:
    UndoRemoveCommand(IModelItem *item, int row, const QModelIndex &parentIndex, QUndoCommand *parent = 0);

    void redo() { insert(); }
    void undo() { remove(); }
};

class UndoStackPrivate;
class UndoStack : public QUndoStack
{
    Q_OBJECT

public:
    explicit UndoStack(QObject *parent = 0);
    ~UndoStack();

private slots:
    void databaseAboutToBeRead();
    void databaseRead();
    void dataAboutToBeChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void modelReset();
    void rowsAboutToBeInserted(const QModelIndex &parent, int start, int end);
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    void rowsRemoved(const QModelIndex &parent, int start, int end);

private:
    UndoStackPrivate *d;
};

#endif // AC_UNDO_H
