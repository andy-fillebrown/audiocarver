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

#ifndef AC_GUI_MAINWINDOWEXTENSION_H
#define AC_GUI_MAINWINDOWEXTENSION_H

#include <imainwindowextension.h>

namespace Core {
    class VersionDialog;
}

namespace Gui {

class MainWindowExtensionPrivate;
class MainWindowExtension : public IMainWindowExtension
{
    Q_OBJECT

    Core::VersionDialog *_versionDialog;

public:
    static MainWindowExtension *instance();

    MainWindowExtension();
    ~MainWindowExtension();

protected:
    void initMenuBarGroups(QStringList &groups) const;
    void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const;
    void initActions();

public slots:
    void showGridSettings();
    void createTrack();
    void erase();
    void build();
    void buildSelected();
    void buildAll();
    void startOrStop();
    void start();
    void stop();
    void aboutAudioCarver();
    void destroyVersionDialog();

private:
    bool maybeSaveDatabase();
};

}

#endif
