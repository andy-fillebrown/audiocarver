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

#include "ac_midi_fileimportdialog.h"
#include <ui_ac_midi_fileimportdialog.h>
#include "ac_midi_constants.h"
#include "ac_midi_filereader.h"
#include <ac_core_namespace.h>
#include <ac_core_point.h>
#include <icore.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <iundomanager.h>
#include <imodelitem.h>
#include <QFileDialog>
#include <QMenu>
#include <QSettings>
#include <QtDebug>

using namespace Midi;
using namespace Ac;
using namespace Core;

enum ImportType {
    Overwrite,
    Append
};

namespace Midi {

struct Note {
    qreal startTime;
    qreal stopTime;
    qreal velocity;
    qreal pitch;
};

typedef QList<Note*> Notes;

}

// Returns the length of the track, in seconds.
static qreal importTrack(FileReader &reader, const int trackNumber)
{
    const EventList events = reader.events(trackNumber);
#   if 0
    {   qDebug() << "Track" << trackNumber;
        foreach (const Event &e, events) {
            if (Event::NoteOn == e.type() || Event::NoteOff == e.type())
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
    Notes notes;
    foreach (const Event &event, events) {
        if (Event::NoteOn == event.type()) {
            Note *note = new Note;
            note->startTime = reader.ticksToSeconds(event.tick());
            note->velocity = event.data(1) / qreal(127.0f);
            note->pitch = event.data(0);
            notes.append(note);
        }
    }

    // Match NoteOff events.
    Notes matched_notes;
    const int note_count = notes.size();
    matched_notes.reserve(note_count);
    foreach (const Event &event, events) {
        if (Event::NoteOff == event.type()) {
            const qreal stop_time = reader.ticksToSeconds(event.tick());
            for (int i = 0;  i < note_count;  ++i) {
                Note *note = notes.at(i);
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

    // Add new track and notes to the score.
    IModelItem *score = IDatabase::instance()->rootItem();
    IModelItem *track_list = query<IModelItem>(score->findItem(TrackListItem));
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    IModelItem *track = query<IModelItem>(factory->create(TrackItem));
    track_list->appendItem(track);
    IModelItem *note_list = track->findItem(NoteListItem);
    foreach (Note *midi_note, matched_notes) {
        IModelItem *note = query<IModelItem>(factory->create(NoteItem));
        IModelItem *pitch_curve = note->findItem(PitchCurveItem);
        PointList points;
        points.append(Point(midi_note->startTime, midi_note->pitch));
        points.append(Point(midi_note->stopTime, midi_note->pitch));
        pitch_curve->setValue(PointsRole, QVariant::fromValue(points));
        note->setValue(VolumeRole, midi_note->velocity);
        note_list->appendItem(note);
    }

    // Extend the score length if the track is longer than the current length.
    qreal length = 0.0f;
    foreach (Note *note, matched_notes)
        if (length < note->stopTime)
            length = note->stopTime;
    if (get<qreal>(score, LengthRole) < length)
        score->setValue(LengthRole, length);
    qDeleteAll(matched_notes);
    return length;
}

static IModelItem *createBarline(qreal time, const QColor &color, int priority, const QString &label = QString())
{
    IModelItem *barline = query<IModelItem>(IDatabaseObjectFactory::instance()->create(TimeGridLineItem));
    barline->setValue(LocationRole, time);
    barline->setValue(ColorRole, color);
    barline->setValue(LabelRole, label);
    barline->setValue(PriorityRole, priority);
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

static void importBarlines(FileReader &reader, qreal scoreLength)
{
    QList<IModelItem*> barline_items;
    const QList<MeterChange> &meter_changes = reader.meterChanges();
    int current_bar_number = 1;
    int current_tick = 0;
    qreal current_time = -1.0f;

    // Create the barlines.
    const int n = meter_changes.count();
    for (int i = 0;  i < n;  ++i) {
        const MeterChange &meter_change = meter_changes.at(i);
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
    barline_items.first()->setValue(PriorityRole, 0);

    // Add the barlines to the database.
    IModelItem *score = IDatabase::instance()->rootItem();
    IModelItem *barline_item_list = score->findItem(GridSettingsItem)->findItem(TimeGridLineListItem);
    foreach (IModelItem *barline_item, barline_items)
        barline_item_list->appendItem(barline_item);

    // Extend the score length to the last barline, if necessary.
    if (get<qreal>(score, LengthRole) < current_time)
        score->setValue(LengthRole, current_time);
}

namespace Midi {

class FileImportDialogPrivate
{
public:
    FileImportDialog *q;
    ImportType importType;
    uint importBarlines : 1;

    FileImportDialogPrivate(FileImportDialog *q)
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
            IDatabase::instance()->reset();
        IUndoManager *undo_manager = IUndoManager::instance();
        undo_manager->pause();

        // Import MIDI file.
        FileReader reader(file_name);
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

        // TODO: Fix the undo bug so the undo manager doesn't have to be reset
        // after a midi file is imported.
        undo_manager->reset();
        undo_manager->resume();
    }
};


FileImportDialog::FileImportDialog(QWidget *parent)
    :   QDialog(parent)
    ,   d(new FileImportDialogPrivate(this))
    ,   ui(new Ui_FileImportDialog)
{
    ui->setupUi(this);
    connect(ui->midiFileOpenButton, SIGNAL(clicked()), SLOT(openFile()));
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(import()));
    connect(ui->buttonBox, SIGNAL(rejected()), SLOT(close()));
    openFile();
}

FileImportDialog::~FileImportDialog()
{
    delete ui;
    delete d;
}

void FileImportDialog::openFile()
{
    QSettings *settings = ICore::instance()->settings();
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

void FileImportDialog::import()
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

}
