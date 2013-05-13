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
#include "ac_gui_mainwindowextension.h"
#include "ac_gui_object_selectionupdater.h"
#include "ac_gui_selectionset.h"
#include "ac_gui_track_selectionupdater.h"
#include <ac_core_namespace.h>
#include <mi_core_base_aggregate.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <ifiler.h>
#include <ifilerfactory.h>
#include <igraphicsitem.h>
#include <imodelitem.h>
#include <ireader.h>
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

void Editor::cut()
{
    copy();
    ::Gui::MainWindowExtension::instance()->erase();
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

}
}
