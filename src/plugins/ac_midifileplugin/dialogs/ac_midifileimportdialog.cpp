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

// Returns the length of the track, in seconds.
static qreal importTrack(MidiFileReader &reader, const int trackNumber)
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
                    break;
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
        return 0.0f;

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

    return length;
}

static IModelItem *createBarline(qreal time, const QColor &color, int priority, const QString &label = QString())
{
    IModelItem *barline = IObjectFactory::instance()->create(Ac::TimeGridLineItem);
    barline->setData(time, Ac::LocationRole);
    barline->setData(color, Ac::ColorRole);
    barline->setData(label, Ac::LabelRole);
    barline->setData(priority, Ac::PriorityRole);
    return barline;
}

static int calculatePriority(int value, int maxPower)
{
    int power = 2;
    for (int i = 0;  i < maxPower;  ++i, power += power)
        if (value % power)
            return maxPower - i;
    return 1;
}

static void importBarlines(MidiFileReader &reader, qreal scoreLength)
{
    QList<IModelItem*> barline_items;
    const QList<Midi::MeterChange> &meter_changes = reader.meterChanges();
    int current_bar_number = 1;
    int current_tick = 0;
    qreal current_time = -1.0f;

    // Create the barlines.
    const int n = meter_changes.count();
    for (int i = 0;  i < n;  ++i) {
        const Midi::MeterChange &meter_change = meter_changes.at(i);
        const float quarters_per_beat = 4.0f / float(meter_change.denominator);
        const int ticks_per_thirtysecond = reader.tickRate() / meter_change.thirtysecondNotesPerQuarterNote;
        const int ticks_per_barline_subdivision = quarters_per_beat * ticks_per_thirtysecond;

        qreal meter_duration = -1.0f;
        if (i + 1 < n)
            meter_duration = meter_changes.at(i + 1).time - meter_change.time;
        else
            meter_duration = scoreLength - meter_change.time;
        const qreal meter_end_time = meter_change.time + meter_duration;

        current_time = meter_change.time;
        while (current_time < meter_end_time
               && !qFuzzyCompare(current_time, meter_end_time)) {
            for (int j = 0;  j < meter_change.numerator;  ++j) {
                QString bar_label = QString("%1").arg(current_bar_number);
                if (j == 0)
                    barline_items.append(createBarline(current_time, QColor(100, 100, 100), 1 + calculatePriority(current_bar_number - 1, 6), bar_label));
                else {
                    bar_label.append(QString(".%1").arg(j + 1));
                    barline_items.append(createBarline(current_time, QColor(175, 175, 175), 10 + calculatePriority(j, 4), bar_label));
                }
                current_tick += ticks_per_barline_subdivision;
                current_time = reader.ticksToSeconds(current_tick);
                for (int k = 1;  k < meter_change.thirtysecondNotesPerQuarterNote;  ++k) {
                    barline_items.append(createBarline(current_time, QColor(225, 225, 225), 100 + calculatePriority(k, 4)));
                    current_tick += ticks_per_barline_subdivision;
                    current_time = reader.ticksToSeconds(current_tick);
                }
            }
            ++current_bar_number;
        }
    }
    if (barline_items.isEmpty())
        return;

    barline_items.append(createBarline(current_time, QColor(Qt::red), 0));
    barline_items.first()->setData(0, Ac::PriorityRole);

    // Add the barlines to the model.
    IModel *model = IModel::instance();
    IModelItem *barline_item_list = model->rootItem()->findModelItem(Ac::GridSettingsItem)->findModelItemList(Ac::TimeGridLineItem);
    const QModelIndex &barline_list_index = model->indexFromItem(barline_item_list);
    foreach (IModelItem *barline_item, barline_items)
        model->insertItem(barline_item, barline_item_list->modelItemCount(), barline_list_index);

    // Extend the score length to the last barline, if necessary.
    IModelItem *score = model->rootItem();
    if (score->data(Ac::LengthRole).toReal() < current_time)
        score->setData(current_time, Ac::LengthRole);
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
        qreal scoreLength = 0.0f;
        for (int i = 0;  i < track_count;  ++i) {
            const qreal trackLength = ::importTrack(reader, i);
            if (scoreLength < trackLength)
                scoreLength = trackLength;
        }
        if (importBarlines)
            ::importBarlines(reader, scoreLength);

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

    openFile();
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
