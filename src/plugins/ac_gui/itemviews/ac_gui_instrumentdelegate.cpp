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

#include "ac_gui_instrumentdelegate.h"
#include "ac_core_namespace.h"
#include <mi_core_utilities.h>
#include <mainwindow.h>
#include <icore.h>
#include <idatabase.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <iqmodel.h>
#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>

using namespace Ac;
using namespace Core;
using namespace Mi;

bool InstrumentDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (customColumn() != index.column())
        return false;

    // We're only interested in left button mouse double-clicks.
    if (QEvent::MouseButtonDblClick != event->type())
        return false;
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    if (Qt::LeftButton != mouse_event->button())
        return false;

    // Open a file-open dialog and set the track's instrument if the user didn't cancel the dialog.
    const IModelData *project_settings = query<IModelData>(IDatabase::instance()->rootItem()->findItem(ProjectSettingsItem));
    QString instrument_dir_name = project_settings->get<QString>(InstrumentDirectoryRole);
    if (instrument_dir_name.isEmpty())
        instrument_dir_name = applicationTreeDirectory() + "instruments";
    QString filename = QFileDialog::getOpenFileName(ICore::instance()->mainWindow(), "Open Instrument", instrument_dir_name, QString("Instrument (*orc)"));
    if (!filename.isEmpty()) {
        QFileInfo instrument_file_info(filename);
        QString instrument_basename = instrument_file_info.baseName();
        IModelData *track = query<IModelData>(IQModel::instance()->itemFromIndex(index));
        track->set(instrument_basename, InstrumentRole);
    }
    return true;
}
