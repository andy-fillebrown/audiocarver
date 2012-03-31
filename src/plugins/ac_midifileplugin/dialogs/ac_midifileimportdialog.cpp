/******************************************************************************
**
**   Copyright 2008, 2009 by Andrew Fillebrown. All rights reserved.
**   andy.fillebrown@gmail.com
**
**   This file is part of the MiQt project.
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 3 of the License, or
**   (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
**
**   Contact andy.fillebrown@gmail.com if any conditions of this licensing are
**   not clear to you.
**
******************************************************************************/

#include "ac_midifileimportdialog.h"
#include "ui_ac_midifileimportdialog.h"

#include <ac_midifileconstants.h>
#include <ac_midifilereader.h>

#include <ac_ifactory.h>
#include <ac_namespace.h>
#include <ac_point.h>

#include <mi_ieditor.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <icore.h>

#include <QFileDialog>
#include <QMenu>
#include <QSettings>

enum ImportType {
    Overwrite,
    Append
};

struct MidiNote {
    qreal startTime;
    qreal stopTime;
    qreal velocity;
    qreal pitch;
};

typedef QList<MidiNote*> MidiNotes;

static void importTrack(MidiFileReader &reader, const int trackNumber)
{
    const MidiEventList events = reader.events(trackNumber);
#   if 0
    {   qDebug() << "Track" << trackNumber;
        foreach (const MidiEvent &e, events) {
            if (MidiEvent::NoteOn == e.type()
                    || MidiEvent::NoteOff == e.type())
                qDebug() << "MIDI event:"
                        "\t  tick ==" << e.tick() <<
                        "\t  time ==" << reader.ticksToSeconds(e.tick()) <<
                        "\t  chan ==" << e.channel() <<
                        "\t  type ==" << e.type() <<
                        "\t  data 1 ==" << e.data(0) <<
                        "\t  data 2 ==" << e.data(1);
        }
        qDebug();
    }
#   endif

    // Add midi note for NoteOn events to be matched with NoteOff events later.
    MidiNotes notes;
    foreach (const MidiEvent &event, events) {
        if (MidiEvent::NoteOn == event.type()) {
            MidiNote *note = new MidiNote;
            note->startTime = reader.ticksToSeconds(event.tick());
            note->velocity = event.data(1) / qreal(127.0f);
            note->pitch = event.data(0);
            notes.append(note);
        }
    }

    // Match NoteOff events.
    MidiNotes matched_notes;
    const int note_count = notes.size();
    matched_notes.reserve(note_count);
    foreach (const MidiEvent &event, events) {
        if (MidiEvent::NoteOff == event.type()) {
            const qreal stop_time = reader.ticksToSeconds(event.tick());
            for (int i = 0;  i < note_count;  ++i) {
                MidiNote *note = notes.at(i);
                if (note
                        && quint8(note->pitch) == event.data(0)
                        && note->startTime < stop_time) {
                    // Matching NoteOn event found for NoteOff.
                    note->stopTime = stop_time;
                    matched_notes.append(note);
                    notes[i] = 0;
                }
            }
        }
    }

    // Print a warning if there are NoteOn events that were not matched with
    // NoteOff events.
    notes.removeAll(0);
    if (!notes.isEmpty()) {
        qWarning() << Q_FUNC_INFO << ":" << notes.count() << "unmatched note on events found";
        qDeleteAll(notes);
    }

    if (matched_notes.isEmpty())
        return;

    IModel *model = IModel::instance();
    IModelItem *score = model->rootItem();

    // Add new track and notes to the score.
    IModelItem *track_list = score->findModelItemList(Ac::TrackItem);
    IObjectFactory *factory = IObjectFactory::instance();
    IModelItem *track = factory->create(Ac::TrackItem);
    model->insertItem(track, track_list->modelItemCount(), model->indexFromItem(track_list));
    IModelItem *note_list = track->findModelItemList(Ac::NoteItem);
    foreach (MidiNote *midi_note, matched_notes) {
        IModelItem *note = factory->create(Ac::NoteItem);
        IModelItem *pitch_curve = note->findModelItem(Ac::PitchCurveItem);
        PointList points;
        points.append(Point(midi_note->startTime, midi_note->pitch));
        points.append(Point(midi_note->stopTime, midi_note->pitch));
        pitch_curve->setData(QVariant::fromValue(points), Ac::PointsRole);
        note->setData(midi_note->velocity, Ac::VolumeRole);
        note->setParentModelItem(note_list);
    }

    // Extend the score length if the track is longer than the current length.
    qreal length = 0.0f;
    foreach (MidiNote *note, matched_notes)
        if (length < note->stopTime)
            length = note->stopTime;
    if (score->data(Ac::LengthRole).toReal() < length)
        score->setData(length, Ac::LengthRole);

    qDeleteAll(matched_notes);
}

static void importBarlines(MidiFileReader &reader)
{
    const QList<Midi::MeterChange> &meter_changes = reader.meterChanges();
}

class MidiFileImportDialogPrivate
{
public:
    MidiFileImportDialog *q;
    ImportType importType;
    uint importBarlines : bitsizeof(uint);

    MidiFileImportDialogPrivate(MidiFileImportDialog *q)
        :   q(q)
        ,   importType(Overwrite)
        ,   importBarlines(true)
    {}

    QString filename() const
    {
        return q->ui->midiFileLineEdit->text();
    }

    void setFilename(const QString filename)
    {
        if (!QFile::exists(filename))
            return;
        q->ui->midiFileLineEdit->setText(filename);
    }

    void import()
    {
        const QString file_name = filename();
        if (file_name.isEmpty())
            return;

        if (Overwrite == importType)
            IModel::instance()->clear();

        IEditor *editor = IEditor::instance();
        editor->beginCommand();

        // Import MIDI file.
        MidiFileReader reader(file_name);
    #   if 0
        {   qDebug();
            qDebug() << file_name;
            qDebug() << "format ==" << reader.format();
            qDebug() << "track count ==" << reader.trackCount();
            qDebug() << "division ==" << reader.division();
            qDebug() << "isUsingTimeCode ==" << QString(reader.isUsingTimeCode() ? "true" : "false");
            qDebug() << "tickrate ==" << reader.tickRate();
            qDebug();
        }
    #   endif
        const int track_count = reader.trackCount();
        for (int i = 0;  i < track_count;  ++i)
            ::importTrack(reader, i);
        if (importBarlines)
            ::importBarlines(reader);

        editor->endCommand();
    }
};


MidiFileImportDialog::MidiFileImportDialog(QWidget *parent)
    :   QDialog(parent)
    ,   d(new MidiFileImportDialogPrivate(this))
    ,   ui(new Ui_MidiFileImportDialog)
{
    ui->setupUi(this);

    connect(ui->midiFileOpenButton, SIGNAL(clicked()), SLOT(openFile()));
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(import()));
    connect(ui->buttonBox, SIGNAL(rejected()), SLOT(close()));
}

MidiFileImportDialog::~MidiFileImportDialog()
{
    delete ui;
    delete d;
}

void MidiFileImportDialog::openFile()
{
    QSettings *settings = Core::ICore::instance()->settings();
    QString mru_dir = settings->value("MidiImport/MRU_Directory").toString();

    // Get MIDI file name from user.
    QString file_name = QFileDialog::getOpenFileName(
                this,
                "Import MIDI File",
                mru_dir,
                "MIDI File (*.mid)");
    if (!QFile::exists(file_name))
        return;

    d->setFilename(file_name);

    mru_dir = QDir(file_name).path();
    settings->setValue("MidiImport/MRU_Directory", mru_dir);
    settings->sync();
}

void MidiFileImportDialog::import()
{
    if ("Create New Score" == ui->importTypeComboBox->currentText())
        d->importType = Overwrite;
    else
        d->importType = Append;

    if ("Import Barlines" == ui->importBarlinesComboBox->currentText())
        d->importBarlines = true;
    else
        d->importBarlines = false;

    d->import();
    close();
}
