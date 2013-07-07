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

#ifndef AC_GUI_MAINWINDOW_H
#define AC_GUI_MAINWINDOW_H

#include <mi_gui_mainwindow.h>

namespace Ac {
namespace Gui {

class MI_GUI_EXPORT MainWindow : public Mi::Gui::MainWindow
{
protected:
    bool maybeSaveDatabase();
};

}
}

#endif
