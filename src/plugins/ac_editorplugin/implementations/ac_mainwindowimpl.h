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

#ifndef AC_MAINWINDOWIMPL_H
#define AC_MAINWINDOWIMPL_H

#include <coreplugin/interfaces/imainwindow.h>

namespace Core {

class VersionDialog;

} // namespace Core

namespace AudioCarver {
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
    void aboutAudioCarver();
    void destroyVersionDialog();

private:
    Core::VersionDialog *m_versionDialog;
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_MAINWINDOWIMPL_H
