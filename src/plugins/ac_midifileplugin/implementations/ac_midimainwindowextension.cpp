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

#include "ac_midimainwindowextension.h"

#include <ac_midifileconstants.h>
#include <ac_midifilereader.h>

#include <ac_ifactory.h>
#include <ac_namespace.h>
#include <ac_point.h>

#include <mi_ieditor.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <actioncontainer.h>
#include <actionmanager.h>
#include <icontext.h>
#include <icore.h>
#include <mainwindow.h>

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QSettings>

using namespace Ac::Midi;

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

    IModelItem *score = IModel::instance()->rootItem();

    // Add new track and notes to the score.
    IModelItem *track_list = score->findModelItemList(Ac::TrackItem);
    IObjectFactory *factory = IObjectFactory::instance();
    IModelItem *track = factory->create(Ac::TrackItem);
    track->setParentModelItem(track_list);
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

void MainWindowExtension::initMenuBarGroups(QStringList &groups) const
{
    Q_UNUSED(groups);
}

void MainWindowExtension::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    Q_UNUSED(menuBarGroup);
    Q_UNUSED(id);
    Q_UNUSED(title);
    Q_UNUSED(groups);
}

void MainWindowExtension::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *file_menu = am->actionContainer(Core::Constants::M_FILE);
    Core::Context global_context(Core::Constants::C_GLOBAL);

    QAction *action = 0;
    Core::Command *cmd = 0;

    // Create File->Import menu if not already created.
    Core::ActionContainer *import_menu = am->actionContainer(M_IMPORT);
    if (!import_menu) {
        action = new QAction(this);
        action->setSeparator(true);
        cmd = am->registerAction(action, PRO_NAME_STR".File.Sep.Import", global_context);
        file_menu->addAction(cmd, G_FILE_IMPORT);
        import_menu = am->createMenu(M_IMPORT);
        file_menu->addMenu(import_menu, G_FILE_IMPORT);
        import_menu->menu()->setTitle(tr("&Import"));
    }

    // Import MIDI File Action
    action = new QAction(tr("&MIDI File"), this);
    cmd = am->registerAction(action, IMPORTMIDIFILE, global_context);
    import_menu->addAction(cmd);
    connect(action, SIGNAL(triggered()), SLOT(importMidiFile()));
}

void MainWindowExtension::importMidiFile()
{
    QSettings *settings = Core::ICore::instance()->settings();
    QString mru_dir = settings->value("MidiImport/MRU_Directory").toString();

    // Get MIDI file name from user.
    QString file_name = QFileDialog::getOpenFileName(
                Core::ICore::instance()->mainWindow(),
                "Import MIDI File",
                mru_dir,
                "MIDI File (*.mid)");
    if (!QFile::exists(file_name))
        return;

    mru_dir = QDir(file_name).path();
    settings->setValue("MidiImport/MRU_Directory", mru_dir);
    settings->sync();

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
        importTrack(reader, i);

    editor->endCommand();
}
