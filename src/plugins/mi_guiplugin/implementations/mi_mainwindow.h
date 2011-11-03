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

#ifndef MI_MAINWINDOW_H
#define MI_MAINWINDOW_H

#include <imainwindow.h>

class MainWindow : public Core::IMainWindow
{
    Q_OBJECT

public:
    void initMenuBarGroups(QStringList &groups) const;
    void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const;
    void initActions();

private slots:
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

#endif // MI_MAINWINDOW_H
