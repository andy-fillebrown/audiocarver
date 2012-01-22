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

#include "ac_editor.h"

#include <ac_undo.h>

#include <ac_ifactory.h>
#include <ac_ifiler.h>
#include <ac_noteselectionmodel.h>
#include <ac_trackmodel.h>
#include <ac_trackselectionmodel.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QApplication>
#include <QClipboard>

class EditorPrivate
{
public:
    Editor *q;
    UndoStack *undoStack;
    quint32 undoEnabled : 1;
    quint32 undoing : 1;
    quint32 creating : 30;

    EditorPrivate(Editor *q)
        :   q(q)
        ,   undoStack(0)
        ,   undoEnabled(quint32(true))
        ,   undoing(quint32(false))
        ,   creating(quint32(false))
    {}

    void init()
    {
        undoStack = new UndoStack(q);
    }
};

Editor::Editor()
    :   d(new EditorPrivate(this))
{
    d->init();
}

Editor::~Editor()
{
    delete d;
}

void Editor::undo()
{
    if (d->undoEnabled
            && !d->creating
            && d->undoStack->canUndo()) {
        d->undoing = quint32(true);
        d->undoStack->undo();
        d->undoing = quint32(false);
    }
}

void Editor::redo()
{
    if (d->undoEnabled
            && !d->creating
            && d->undoStack->canRedo()) {
        d->undoing = quint32(true);
        d->undoStack->redo();
        d->undoing = quint32(false);
    }
}

void Editor::cut()
{
    copy();

    IModel *model = IModel::instance();

    const QModelIndexList tracks = TrackSelectionModel::instance()->selectedTrackIndexes();
    const int tracks_n = tracks.count();
    if (tracks_n) {
        QList<int> rows;
        rows.reserve(tracks_n);
        foreach (const QModelIndex &track, tracks)
            rows.append(track.row());
        qSort(rows);

        const QModelIndex trackList = model->listIndex(Ac::TrackItem);

        beginCommand();

        for (int i = tracks_n - 1;  0 <= i;  --i)
            model->removeItem(rows.at(i), trackList);

        endCommand();
    } else {
        const QModelIndexList notes = NoteSelectionModel::instance()->selectedIndexes();
        const int notes_n = notes.count();
        if (notes_n) {
            QMap<QModelIndex, QModelIndexList> noteListMap;
            foreach (const QModelIndex note, notes)
                noteListMap[model->parent(note)].append(note);

            beginCommand();

            QModelIndexList noteLists = noteListMap.keys();
            foreach (const QModelIndex &noteList, noteLists) {
                const QModelIndexList &notes = noteListMap.value(noteList);
                const int notes_n = notes.count();

                QList<int> rows;
                rows.reserve(notes_n);
                foreach (const QModelIndex &note, notes)
                    rows.append(note.row());
                qSort(rows);

                for (int i = notes_n - 1;  0 <= i;  --i)
                    model->removeItem(rows.at(i), noteList);
            }

            endCommand();
        }
    }
}

void Editor::copy() const
{
    IWriter *writer = IFilerFactory::instance()->createWriter(Ac::XmlCopyFiler);

    QList<IModelItem*> tracks = TrackSelectionModel::instance()->selectedTracks();
    foreach (IModelItem *track, tracks)
        writer->write(track);

    if (tracks.isEmpty()) {
        QList<IModelItem*> notes = NoteSelectionModel::instance()->selectedNotes();
        foreach (IModelItem *note, notes)
            writer->write(note);
    }

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(query<ICopyFiler>(writer)->data());

    delete writer;
}

void Editor::paste()
{
    IReader *reader = IFilerFactory::instance()->createReader(Ac::XmlCopyFiler);
    ICopyFiler *filer = query<ICopyFiler>(reader);
    if (filer->data().isEmpty())
        return;

    IObjectFactory *objectFactory = IObjectFactory::instance();
    IModel *model = IModel::instance();
    const QModelIndex trackListIndex = model->listIndex(Ac::TrackItem);

    int itemType = reader->nextItemType();
    if (Mi::UnknownItem == itemType)
        return;

    beginCommand();

    if (Ac::TrackItem == itemType) {
        while (Mi::UnknownItem != itemType) {
            Q_ASSERT(Ac::TrackItem == itemType);
            IModelItem *track = objectFactory->create(Ac::TrackItem);
            reader->read(track);
            model->insertItem(track, model->rowCount(trackListIndex), trackListIndex);

            itemType = reader->nextItemType();
        }
    } else if (Ac::NoteItem == itemType) {
        QList<IModelItem*> recordingTracks = model->findItems(Ac::TrackItem, Ac::RecordingRole, true);
        QModelIndexList noteListIndexes;
        foreach (IModelItem *track, recordingTracks)
            noteListIndexes.append(model->indexFromItem(track->findModelItemList(Ac::NoteItem)));
        if (!recordingTracks.isEmpty()) {
            foreach (const QModelIndex &noteListIndex, noteListIndexes) {
                IReader *cloneReader = IFilerFactory::instance()->createReader(Ac::XmlCopyFiler);

                itemType = cloneReader->nextItemType();
                while (Mi::UnknownItem != itemType) {
                    Q_ASSERT(Ac::NoteItem == itemType);
                    IModelItem *note = objectFactory->create(Ac::NoteItem);
                    cloneReader->read(note);
                        model->insertItem(note, model->rowCount(noteListIndex), noteListIndex);

                    itemType = cloneReader->nextItemType();
                }

                delete cloneReader;
            }
        }
    } else
        Q_ASSERT(false);

    endCommand();
    delete reader;
}

void Editor::selectAll()
{
}

bool Editor::isUndoEnabled() const
{
    return d->undoEnabled;
}

void Editor::setUndoEnabled(bool enabled)
{
    d->undoEnabled = enabled;
}

void Editor::beginCommand(const QString &text)
{
    d->undoStack->beginMacro(text);
}

void Editor::endCommand()
{
    d->undoStack->endMacro();
}

bool Editor::canPushCommand() const
{
    return !d->undoing;
}

void Editor::pushCommand(QUndoCommand *cmd)
{
    if (!d->undoing)
        d->undoStack->push(cmd);
    else
        delete cmd;
}

void Editor::startCreating()
{
    d->creating = quint32(true);
}

void Editor::finishCreating()
{
    d->creating = quint32(false);
}

bool Editor::isCreating() const
{
    return d->creating;
}
