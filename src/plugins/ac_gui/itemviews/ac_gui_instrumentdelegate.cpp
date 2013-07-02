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

#include "ac_gui_instrumentdelegate.h"
#include "ac_core_namespace.h"
#include <mi_core_utilities.h>
#include <mainwindow.h>
#include <icore.h>
#include <idatabase.h>
#include <ieditor.h>
#include <igraphicsitem.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iselectionset.h>
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

    // Open a file-open dialog and set each of the selected track's instruments
    // if the user didn't cancel the dialog.
    IDatabase *database = IDatabase::instance();
    const QString root_dir_name = QFileInfo(database->fileName()).path();
    IModelItem *project_settings = database->rootItem()->findItem(ProjectSettingsItem);
    QString instrument_dir_name = get<QString>(project_settings, InstrumentDirectoryRole);
    if ("." == root_dir_name || instrument_dir_name.isEmpty())
        instrument_dir_name = applicationTreeDirectory() + "instruments";
    else if (QDir::isRelativePath(instrument_dir_name))
        instrument_dir_name = root_dir_name + "/" + instrument_dir_name;
    QString filename = QFileDialog::getOpenFileName(ICore::instance()->mainWindow(), "Open Instrument", instrument_dir_name, QString("Instrument (*orc)"));
    if (!filename.isEmpty()) {
        QFileInfo instrument_file_info(filename);
        QString instrument_basename = instrument_file_info.baseName();
        ISelectionSet *track_ss = IEditor::instance()->currentSelection(TrackItem);
        const QList<IGraphicsItem*> &tracks = track_ss->items();
        foreach (IGraphicsItem *track_gi, tracks)
            query<IModelItem>(track_gi)->set(InstrumentRole, instrument_basename);
    }
    return true;
}
