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

#ifndef AC_GUI_MAINWINDOWEXTENSION_H
#define AC_GUI_MAINWINDOWEXTENSION_H

#include <imainwindowextension.h>

namespace Ac {
namespace Gui {

class MainWindowExtensionPrivate;
class MainWindowExtension : public ::Core::IMainWindowExtension
{
    Q_OBJECT

public:
    MainWindowExtension();
    ~MainWindowExtension();

    void initMenuBarGroups(QStringList &groups) const;
    void initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const;
    void initActions();

private slots:
    void showGridSettings();
    void createTrack();
    void erase();
    void build();
    void buildAll();
    void startOrStop();
    void start();
    void stop();
    void aboutAudioCarver();
    void destroyVersionDialog();

private:
    MainWindowExtensionPrivate *d;
};

} // namespace Gui
} // namespace Ac

#endif // AC_GUI_MAINWINDOWEXTENSION_H
