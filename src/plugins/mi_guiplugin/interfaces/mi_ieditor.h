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

#ifndef MI_IEDITOR_H
#define MI_IEDITOR_H

#include <mi_global.h>

#include <QObject>

class QUndoCommand;
class QUndoStack;

class MI_GUI_EXPORT IEditor : public QObject
{
    Q_OBJECT

public:
    IEditor();
    ~IEditor();

    static IEditor *instance();

    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void cut() = 0;
    virtual void copy() const = 0;
    virtual void paste() = 0;
    virtual void selectAll() = 0;

    virtual QUndoStack *undoStack() const = 0;

    virtual bool isUndoEnabled() const = 0;
    virtual void setUndoEnabled(bool enabled) = 0;

    virtual void beginCommand(const QString &text = QString()) = 0;
    virtual void endCommand() = 0;

    virtual bool canPushCommand() const = 0;
    virtual void pushCommand(QUndoCommand *cmd) = 0;

    virtual void startCreating() = 0;
    virtual void finishCreating() = 0;
    virtual bool isCreating() const = 0;

signals:
    void commandUndone();
    void commandRedone();
};

#endif // MI_IEDITOR_H
