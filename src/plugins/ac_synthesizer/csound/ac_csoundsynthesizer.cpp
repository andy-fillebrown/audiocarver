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

#include <csound.h>

#include <QDir>
#include <QFileInfo>

class CsoundSynthesizerPrivate
{
public:
    void renderTrack(const IModelItem *track)
    {
        if (!track)
            return;

        const QString db_file_name = IDatabase::instance()->fileName();
        if (db_file_name.isEmpty())
            return;

        const QString root_dir_name = QFileInfo(db_file_name).path();
        QDir root_dir(root_dir_name);

        const IModel *model = IModel::instance();
        const IModelItem *project_settings = model->itemFromIndex(model->itemIndex(Ac::ProjectSettingsItem));

        QString output_dir_name = project_settings->data(Ac::OutputDirectoryRole).toString();
        if (output_dir_name.isEmpty())
            output_dir_name = root_dir_name + "/output";
        if (!root_dir.mkpath(output_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << output_dir_name;
            return;
        }

        const QString csound_dir_name = output_dir_name + "/csound";
        if (!root_dir.mkpath(csound_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << csound_dir_name;
            return;
        }

        const QString track_name = track->data(Mi::NameRole).toString().toLower();
        const QString csound_file_name_prefix = csound_dir_name + "/" + track_name;

        const QString orc_file_name = csound_file_name_prefix + ".orc";
        QFile orc_file(orc_file_name);
        if (!orc_file.open(QIODevice::Text | QIODevice::WriteOnly)) {
            qDebug() << Q_FUNC_INFO << ": Error opening orc file" << orc_file_name;
            return;
        }
        orc_file.write("test orc\n");
        orc_file.close();

        const QString sco_file_name = csound_file_name_prefix + ".sco";
        QFile sco_file(sco_file_name);
        if (!sco_file.open(QIODevice::Text | QIODevice::WriteOnly)) {
            qDebug() << Q_FUNC_INFO << ": Error opening sco file" << sco_file_name;
            return;
        }
        sco_file.write("test sco\n");
        sco_file.close();

        const QString audio_dir_name = output_dir_name + "/audio";
        if (!root_dir.mkpath(audio_dir_name)) {
            qDebug() << Q_FUNC_INFO << ": Error making path" << audio_dir_name;
            return;
        }

        QString audio_file_type = project_settings->data(Ac::AudioFileTypeRole).toString();
        if (audio_file_type.isEmpty())
            audio_file_type = "wav";
        const QString audio_file_name = audio_dir_name + "/" + track_name + "." + audio_file_type;
        QFile audio_file(audio_file_name);
        if (!audio_file.open(QIODevice::WriteOnly)) {
            qDebug() << Q_FUNC_INFO << ": Error opening audio file" << audio_file_name;
            return;
        }
        audio_file.close();

//        const QString instrument_file_name = track->data(Ac::InstrumentRole).toString();
//        QFile instrument_file(instrument_file_name);
//        if (!instrument_file.open(QIODevice::ReadOnly)) {
//            qDebug() << Q_FUNC_INFO << ": Error opening instrument file" << instrument_file_name;
//            return;
//        }

        const IModelItem *notes = track->findModelItemList(Ac::NoteItem);
        const int n = notes->modelItemCount();
        for (int i = 0;  i < n;  ++i) {
        }

        qDebug() << Q_FUNC_INFO << ": Passed render test";
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
