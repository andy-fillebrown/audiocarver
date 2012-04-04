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

#ifndef AC_UNDO_H
#define AC_UNDO_H

#include <QUndoStack>

class IModelItem;

class QModelIndex;

namespace Ac {

enum UndoCommandId {
    UndoViewSettingsCommandId = 1,
    UndoDataCommandId,
    UndoInsertCommandId,
    UndoRemoveCommandId
};

} // namespace Ac

class UndoCommandPrivate;
class UndoCommand : public QUndoCommand
{
public:
    ~UndoCommand();

protected:
    UndoCommand(UndoCommandPrivate &dd, QUndoCommand *parent)
        :   QUndoCommand(parent)
        ,   d_ptr(&dd)
    {}

    UndoCommandPrivate *d_ptr;
};

class UndoViewSettingsCommandPrivate;
class UndoViewSettingsCommand : public UndoCommand
{
public:
    UndoViewSettingsCommand(QUndoCommand *parent = 0);

    int id() const { return Ac::UndoViewSettingsCommandId; }
    bool mergeWith(const QUndoCommand *other);
    void redo();
    void undo();

private:
    Q_DECLARE_PRIVATE(UndoViewSettingsCommand)
};

class UndoModelItemCommandPrivate;
class UndoModelItemCommand : public UndoCommand
{
public:
    IModelItem *item() const;
    void setItem(IModelItem *item);

protected:
    UndoModelItemCommand(UndoModelItemCommandPrivate &dd, QUndoCommand *parent);

private:
    Q_DECLARE_PRIVATE(UndoModelItemCommand)
};

class UndoDataCommandPrivate;
class UndoDataCommand : public UndoModelItemCommand
{
public:
    UndoDataCommand(IModelItem *item, QUndoCommand *parent = 0);

    void updateNewData();

    int id() const { return Ac::UndoDataCommandId; }
    void redo();
    void undo();

private:
    Q_DECLARE_PRIVATE(UndoDataCommand)
};

class UndoListCommandPrivate;
class UndoListCommand : public UndoModelItemCommand
{
public:
    const QModelIndex &parentIndex() const;
    int row() const;

    void insert();
    void remove();

    bool mergeWith(const QUndoCommand *other);

protected:
    UndoListCommand(UndoListCommandPrivate &dd, QUndoCommand *parent);

    Q_DECLARE_PRIVATE(UndoListCommand)
};

class UndoInsertCommand : public UndoListCommand
{
public:
    UndoInsertCommand(int row, const QModelIndex &parentIndex, QUndoCommand *parent = 0);

    int id() const { return Ac::UndoInsertCommandId; }
    void redo() { insert(); }
    void undo() { remove(); }
};

class UndoRemoveCommand : public UndoListCommand
{
public:
    UndoRemoveCommand(IModelItem *item, int row, const QModelIndex &parentIndex, QUndoCommand *parent = 0);

    int id() const { return Ac::UndoRemoveCommandId; }
    void redo() { remove(); }
    void undo() { insert(); }
};

class UndoStackPrivate;
class UndoStack : public QUndoStack
{
    Q_OBJECT

public:
    UndoStack(QObject *parent = 0);
    ~UndoStack();

private slots:
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
