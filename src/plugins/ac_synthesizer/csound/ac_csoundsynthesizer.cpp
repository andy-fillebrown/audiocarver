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

        const QString track_name = track->data(Mi::NameRole).toString().toLower();
        const QString instrument = track->data(Ac::InstrumentRole).toString();

        IModel *model = IModel::instance();
        const IModelItem *project_settings = model->itemFromIndex(model->itemIndex(Ac::ProjectSettingsItem));
        QDir output_dir = project_settings->data(Ac::OutputDirectoryRole).toString();
        QDir instrument_dir = project_settings->data(Ac::InstrumentDirectoryRole).toString();

        if (output_dir.isRelative()) {
            QDir output_root_dir = QFileInfo(IDatabase::instance()->fileName()).canonicalPath();
            output_dir = QDir(output_root_dir.path() + "/" + output_dir.path());
        }
        if (instrument_dir.isRelative()) {
            QDir instrument_root_dir = QFileInfo(IDatabase::instance()->fileName()).canonicalPath();
            instrument_dir = QDir(instrument_root_dir.path() + "/" + instrument_dir.path());
        }

        QFileInfo output_file_name(QDir::convertSeparators(output_dir.path() + "/" + track_name));
        output_file_name.makeAbsolute();

        QFile output_file(output_file_name.filePath());
        bool ok = output_file.open(QIODevice::Text | QIODevice::WriteOnly);
        if (!ok) {
            qDebug() << Q_FUNC_INFO << output_file_name.filePath();
            qDebug() << Q_FUNC_INFO << output_file.errorString();
            return;
        }
        output_file.write("test\n");
        output_file.close();

        const QString instrument_file_name = QFileInfo(instrument_dir.path() + "/" + instrument).filePath();

        qDebug() << Q_FUNC_INFO << "output file name:" << QFileInfo(output_file_name).canonicalFilePath();
        qDebug() << Q_FUNC_INFO << "instrument file name:" << instrument_file_name;

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
