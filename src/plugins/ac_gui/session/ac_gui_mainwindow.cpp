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

#include "ac_gui_mainwindow.h"
#include <mi_gui_namespace.h>
#include <icore.h>
#include <mainwindow.h>
#include <QMessageBox>
#include <QWidget>

using namespace Mi;
using namespace Qt;

namespace Ac {
namespace Gui {

bool MainWindow::maybeSaveDatabase()
{
    QMessageBox message_box;
    message_box.setParent(Core::ICore::instance()->mainWindow());
    message_box.setWindowModality(WindowModal);
    message_box.setText("The document has been modified.");
    message_box.setInformativeText("Do you want to save your changes?");
    message_box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    int result = message_box.exec();
    if (QMessageBox::Cancel == result)
        return false;
    if (QMessageBox::Save == result)
        return runCommand(FileSaveCommand);
    return true;
}

}
}
