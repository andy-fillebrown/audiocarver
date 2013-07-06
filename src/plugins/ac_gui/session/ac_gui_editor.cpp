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

#include "ac_gui_editor.h"
#include "ac_gui_graphicsview.h"
#include "ac_gui_graphicsviewmanager.h"
#include "ac_gui_namespace.h"
#include "ac_gui_object_selectionupdater.h"
#include "ac_gui_selectionset.h"
#include "ac_gui_track_selectionupdater.h"
#include <ac_core_namespace.h>
#include <mi_core_base_aggregate.h>
#include <iaudioengine.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <ifiler.h>
#include <ifilerfactory.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <ireader.h>
#include <isynthesizer.h>
#include <iundomanager.h>
#include <iwriter.h>

using namespace Mi;

namespace Ac {
namespace Gui {

Editor::Editor()
{
    _objectSS = new Base::Aggregate;
    new SelectionSet(_objectSS);
    new Object::SelectionUpdater(_objectSS);
    _trackSS = new Base::Aggregate;
    new SelectionSet(_trackSS);
    new Track::SelectionUpdater(_trackSS);
    _noteSS = new Base::Aggregate;
    new SelectionSet(_noteSS);
}

Editor::~Editor()
{
    qDelete(_noteSS);
    qDelete(_trackSS);
    qDelete(_objectSS);
}

void Editor::cut()
{
    copy();
    erase();
}

void Editor::copy() const
{
    int ss_type = NoteListItem;
    ISelectionSet *ss = currentSelection(NoteItem);
    if (ss->items().isEmpty()) {
        ss_type = TrackListItem;
        ss = currentSelection(TrackItem);
    }
    if (ss->items().isEmpty())
        return;
    IWriter *writer = query<IWriter>(IFilerFactory::instance()->create(CopyFiler));
    const QList<IGraphicsItem*> &items = ss->items();
    writer->writeStartElement(itemTypeString(ss_type));
    foreach (IGraphicsItem *item, items)
        writer->write(query<IModelItem>(item));
    writer->writeEndElement();
    delete query<IAggregate>(writer);
    return;
}

void Editor::paste()
{
    IReader *reader = query<IReader>(IFilerFactory::instance()->create(CopyFiler));
    IFiler *filer = query<IFiler>(reader);
    IModelItem *track_list = IDatabase::instance()->rootItem()->findItem(TrackListItem);
    const int item_type = reader->nextItemType();
    filer->reset();
    if (NoteListItem == item_type) {
        QList<IModelItem*> tracks;
        QList<IGraphicsItem*> notes;
        const int track_count = track_list->itemCount();
        for (int i = 0;  i < track_count;  ++i) {
            IModelItem *track = track_list->itemAt(i);
            if (get<bool>(track, RecordingRole))
                tracks.append(track);
        }
        if (tracks.isEmpty())
            return;
        IUndoManager *undo_manager = IUndoManager::instance();
        undo_manager->beginCommand();
        foreach (IModelItem *track, tracks) {
            IModelItem *note_list = track->findItem(NoteListItem);
            const int prev_count = note_list->itemCount();
            reader->read(note_list);
            filer->reset();
            const int cur_count = note_list->itemCount();
            for (int i = prev_count;  i < cur_count;  ++i)
                notes.append(query<IGraphicsItem>(note_list->itemAt(i)));
        }
        undo_manager->endCommand();
        ISelectionSet *ss = IEditor::instance()->currentSelection();
        ss->clear();
        ss->append(notes);
    }
    else if (TrackListItem == item_type) {
        IUndoManager *undo_manager = IUndoManager::instance();
        undo_manager->beginCommand();
        reader->read(track_list);
        undo_manager->endCommand();
    }
    delete reader;
}

void Editor::selectAll()
{
}

void Editor::createTrack()
{
    IUndoManager *undo_manager = IUndoManager::instance();
    undo_manager->beginCommand();
    IModelItem *track_list = IDatabase::instance()->rootItem()->findItem(TrackListItem);
    IModelItem *track = query<IModelItem>(IDatabaseObjectFactory::instance()->create(TrackItem));
    track_list->appendItem(track);
    undo_manager->endCommand();
}

void Editor::erase()
{
    IEditor *editor = IEditor::instance();
    IUndoManager *undo_manager = IUndoManager::instance();

    // Erase selected points in pitch and control views.
    GraphicsViewManager *vm = GraphicsViewManager::instance();
    GraphicsView *view = qobject_cast<GraphicsView*>(vm->view(PitchScene));
    if (view->pointsAreSelected()) {
        undo_manager->beginCommand();
        view->removePoints();
    }
    view = qobject_cast<GraphicsView*>(vm->view(ControlScene));
    if (view->pointsAreSelected()) {
        if (!undo_manager->isInCommand())
            undo_manager->beginCommand();
        view->removePoints();
    }
    if (undo_manager->isInCommand()) {
        undo_manager->endCommand();
        return;
    }

    // If no points are selected, erase selected notes.
    ISelectionSet *ss = editor->currentSelection(NoteItem);
    QList<IGraphicsItem*> items = ss->items();
    if (!items.isEmpty()) {
        undo_manager->beginCommand();
        while (!items.isEmpty()) {
            IGraphicsItem *item = items.last();
            item->update(HighlightRole, NoHighlight);
            IModelItem *note = query<IModelItem>(item);
            note->remove();
            items.removeLast();
        }
        undo_manager->endCommand();
        ss->clear();
        editor->currentSelection()->clear();
        return;
    }

    // If no points or notes are selected, erase selected tracks.
    ss = editor->currentSelection(TrackItem);
    items = ss->items();
    if (!items.isEmpty()) {
        undo_manager->beginCommand();
        while (!items.isEmpty()) {
            IGraphicsItem *item = items.last();
            item->update(HighlightRole, NoHighlight);
            item->update(VisibilityRole, false);
            IModelItem *track = query<IModelItem>(item);
            track->remove();
            items.removeLast();
        }
        undo_manager->endCommand();
        ss->clear();
        return;
    }
}

void Editor::build()
{
    IModelItem *track_list = IDatabase::instance()->rootItem()->findItem(TrackListItem);
    ISynthesizer *synth = ISynthesizer::instance();
    int track_count = track_list->itemCount();
    for (int i = 0;  i < track_count;  ++i) {
        QString track_name = get<QString>(track_list->itemAt(i), NameRole);
        if (_dirtyTracks.contains(track_name))
            synth->renderTrack(i);
    }
    _dirtyTracks.clear();
}

void Editor::buildSelected()
{
    ISelectionSet *track_ss = currentSelection(TrackItem);
    const QList<IGraphicsItem*> &tracks = track_ss->items();
    IModelItem *track_list = IDatabase::instance()->rootItem()->findItem(TrackListItem);
    ISynthesizer *synth = ISynthesizer::instance();
    foreach (IGraphicsItem *track_graphics, tracks) {
        IModelItem *track = query<IModelItem>(track_graphics);
        synth->renderTrack(track_list->indexOfItem(track));
        _dirtyTracks.removeAll(get<QString>(track, NameRole));
    }
}

void Editor::buildAll()
{
    const int track_count = IDatabase::instance()->rootItem()->findItem(TrackListItem)->itemCount();
    ISynthesizer *synth = ISynthesizer::instance();
    for (int i = 0;  i < track_count;  ++i)
        synth->renderTrack(i);
    _dirtyTracks.clear();
}

void Editor::startOrStop()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    if (!audio_engine)
        return;
    if (audio_engine->isStarted())
        stop();
    else
        start();
}

void Editor::start()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    if (audio_engine)
        audio_engine->start();
}

void Editor::stop()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    if (audio_engine)
        audio_engine->stop();
}

ISelectionSet *Editor::currentSelection(int itemType) const
{
    switch (itemType) {
    case UnknownItem:
        return query<ISelectionSet>(_objectSS);
    case TrackItem:
        return query<ISelectionSet>(_trackSS);
    case NoteItem:
        return query<ISelectionSet>(_noteSS);
    default:
        Q_ASSERT(false);
        return 0;
    }
}

void Editor::runCommand(int command)
{
    switch (command) {
    case CutCommand:
        return cut();
    case CopyCommand:
        return copy();
    case PasteCommand:
        return paste();
    case SelectAllCommand:
        return selectAll();
    case CreateTrackCommand:
        return createTrack();
    case EraseCommand:
        return erase();
    case BuildCommand:
        return build();
    case BuildSelectedCommand:
        return buildSelected();
    case BuildAllCommand:
        return buildAll();
    case StartOrStopTransportCommand:
        return startOrStop();
    case StartTransportCommand:
        return start();
    case StopTransportCommand:
        return stop();
    default:
        return;
    }
}

void Editor::beginChangeData(IModelItem *item, int role)
{
    if (item->isTypeOfItem(TrackItem)) {
        if (NameRole == role) {
            _dirtyTracks.removeOne(get<QString>(item, NameRole));
            return;
        }
    }
}

void Editor::endChangeData(IModelItem *item, int role)
{
    if (IDatabase::instance()->isReading())
        return;
    IModelItem *track = 0;
    if (item->isTypeOfItem(TrackItem))
        if (NameRole == role || InstrumentRole == role)
            track = item;
    if (item->isTypeOfItem(NoteItem))
        track = item->parent();
    else if (item->isTypeOfItem(CurveItem)) {
        IModelItem *note = item->parent();
        if (note) {
            IModelItem *note_list = note->parent();
            if (note_list)
                track = note_list->parent();
        }
    }
    if (track) {
        QString track_name = get<QString>(track, NameRole);
        if (!_dirtyTracks.contains(track_name)) {
            _dirtyTracks.append(track_name);
            return;
        }
    }
}

void Editor::endInsertItem(IModelItem *list, int index)
{
    if (IDatabase::instance()->isReading())
        return;
    if (list->isTypeOfItem(ListItem) && NoteItem == get<int>(list, ListTypeRole)) {
        QString track_name = get<QString>(list->parent(), NameRole);
        if (!_dirtyTracks.contains(track_name))
            _dirtyTracks.append(track_name);
    }
}

void Editor::endRemoveItem(IModelItem *list, int index)
{
    if (IDatabase::instance()->isReading())
        return;
    if (list->isTypeOfItem(ListItem) && NoteItem == get<int>(list, ListTypeRole)) {
        QString track_name = get<QString>(list->parent(), NameRole);
        if (!_dirtyTracks.contains(track_name))
            _dirtyTracks.append(track_name);
    }
}

}
}
