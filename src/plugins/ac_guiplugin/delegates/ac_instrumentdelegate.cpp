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

#include "ac_instrumentdelegate.h"

#include <ac_namespace.h>

#include <mi_coreutils.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <icore.h>
#include <mainwindow.h>

#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>

bool InstrumentDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);

    if (customColumn() != index.column())
        return false;

    // We're only interested in left button mouse double-clicks.
    if (QEvent::MouseButtonDblClick != event->type())
        return false;
    QMouseEvent *e = static_cast<QMouseEvent*>(event);
    if (Qt::LeftButton != e->button())
        return false;

    // Open a file-open dialog and set the track's instrument if the user didn't cancel the dialog.
    const IModel *m = IModel::instance();
    const IModelItem *project_settings = m->itemFromIndex(m->itemIndex(Ac::ProjectSettingsItem));
    QString instrument_dir_name = project_settings->data(Ac::InstrumentDirectoryRole).toString();
    if (instrument_dir_name.isEmpty())
        instrument_dir_name = Mi::applicationTreeDirectory() + "instruments";
    QString filename = QFileDialog::getOpenFileName(Core::ICore::instance()->mainWindow(), "Open Instrument", instrument_dir_name, QString::fromLatin1("Instrument (*orc)"));

    if (!filename.isEmpty()) {
        QFileInfo instrument_file_info(filename);
        QString abbreviated_filename = instrument_file_info.baseName();
        model->setData(index, abbreviated_filename, Qt::EditRole);
    }

    return true;
}
