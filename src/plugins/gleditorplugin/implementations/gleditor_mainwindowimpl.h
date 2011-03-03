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

#ifndef GLEDITOR_MAINWINDOWIMPL_H
#define GLEDITOR_MAINWINDOWIMPL_H

#include <coreplugin/interfaces/imainwindow.h>

namespace GLEditor {
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

private slots:
    void viewAll();
    void viewZoom();
    void viewPan();
    void viewRotate();
    void viewParallel();
    void viewPerspective();
    void viewTransparencyNone();
    void viewTransparencyScreen();
    void viewTransparencyFull();

    void windowSplitHorizontal();
    void windowSplitVertical();
    void windowRemoveCurrentSplit();
    void windowRemoveAllSplits();
};

} // namespace Internal
} // namespace GLEditor

#endif // GLEDITOR_MAINWINDOWIMPL_H
