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

#include "mi_guiplugin.h"

//#include <mi_gui_editor.h>
#include <mi_gui_mainwindowextension.h>

#include <icore.h>
#include <mainwindow.h>

#include <QtPlugin>

namespace Mi {

using namespace Gui;

bool GuiPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    addAutoReleasedObject(new MainWindowExtension);
    return true;
}

GuiPlugin::~GuiPlugin()
{
//    Gui::Editor::destroy();
}

} // namespace Mi

Q_EXPORT_PLUGIN(Mi::GuiPlugin)
