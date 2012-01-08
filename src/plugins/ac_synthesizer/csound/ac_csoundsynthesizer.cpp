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

#include <ac_csoundsynthesizer.h>

#include <ac_namespace.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QDir>
#include <QFileInfo>

#include <csound.h>

class CsoundSynthesizerPrivate
{
public:
    void renderTrack(const IModelItem *track)
    {
        if (!track)
            return;

        const QString database_file_name = IDatabase::instance()->fileName();

        const QString track_name = track->data(Mi::NameRole).toString();
        const QString instrument = track->data(Ac::InstrumentRole).toString();

        IModel *model = IModel::instance();
        const IModelItem *project_settings = model->itemFromIndex(model->itemIndex(Ac::ProjectSettingsItem));
        QString output_dir = project_settings->data(Ac::OutputDirectoryRole).toString();
        QString instrument_dir = project_settings->data(Ac::InstrumentDirectoryRole).toString();

        if (QDir::convertSeparators(output_dir).startsWith(QDir::convertSeparators("./")))
            output_dir = IDatabase::instance()->fileName() + "/" + output_dir;
        if (QDir::convertSeparators(instrument_dir).startsWith(QDir::convertSeparators("./")))
            instrument_dir = IDatabase::instance()->fileName() + "/" + instrument_dir;

        const QString output_file_name = output_dir + "/" + track_name;
        const QString instrument_file_name = instrument_dir + "/" + instrument;

        QFileInfo output_file_info = QFileInfo(output_file_name);
        QFileInfo instrument_file_info = QFileInfo(instrument_file_name);

        qDebug() << Q_FUNC_INFO << "filename:" << QDir::convertSeparators(database_file_name);
        qDebug() << Q_FUNC_INFO << "output:" << QDir::convertSeparators(output_file_info.absoluteFilePath()).toLower();
        qDebug() << Q_FUNC_INFO << "instrument:" << QDir::convertSeparators(instrument_file_info.absoluteFilePath()).toLower();

        const IModelItem *notes = track->findModelItemList(Ac::NoteItem);
        const int n = notes->modelItemCount();
        for (int i = 0;  i < n;  ++i) {
        }
    }
};

CsoundSynthesizer::CsoundSynthesizer()
    :   d(new CsoundSynthesizerPrivate)
{}

CsoundSynthesizer::~CsoundSynthesizer()
{
    delete d;
}

void CsoundSynthesizer::renderTrack(int trackNumber)
{
    const IModel *model = IModel::instance();
    const IModelItem *track = model->itemFromIndex(model->index(trackNumber, model->listIndex(Ac::TrackItem)));
    d->renderTrack(track);
}
