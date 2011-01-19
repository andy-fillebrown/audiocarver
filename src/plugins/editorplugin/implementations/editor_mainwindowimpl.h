/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#ifndef EDITOR_MAINWINDOWIMPL_H
#define EDITOR_MAINWINDOWIMPL_H

#include <coreplugin/interfaces/imainwindow.h>

namespace Editor {
namespace Internal {

class MainWindowImpl : public Core::IMainWindow
{
    Q_OBJECT

public:
    MainWindowImpl();
    virtual ~MainWindowImpl();

    virtual void initMenuBarGroups(QStringList &groups) const;
    virtual void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const;
    virtual void initActions();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();

    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void selectAll();
};

} // namespace Internal
} // namespace Editor

#endif // EDITOR_MAINWINDOWIMPL_H
