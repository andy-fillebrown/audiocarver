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

#include "ac_editor.h"

#include <ac_undo.h>

#include <ac_ifactory.h>
#include <ac_ifiler.h>
#include <ac_noteselectionmodel.h>
#include <ac_trackmodel.h>
#include <ac_trackselectionmodel.h>

#include <mi_imodel.h>

#include <QApplication>
#include <QClipboard>

class EditorPrivate
{
public:
    Editor *q;
    UndoStack *undoStack;
    quint32 undoing : 1;
    quint32 creating : 31;

    EditorPrivate(Editor *q)
        :   q(q)
        ,   undoStack(0)
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
    if (!d->creating && d->undoStack->canUndo()) {
        d->undoing = quint32(true);
        d->undoStack->undo();
        d->undoing = quint32(false);
    }
}

void Editor::redo()
{
    if (!d->creating && d->undoStack->canRedo()) {
        d->undoing = quint32(true);
        d->undoStack->redo();
        d->undoing = quint32(false);
    }
}

void Editor::cut()
{
}

void Editor::copy() const
{
    TrackModel *trackModel = TrackModel::instance();
    TrackSelectionModel *trackSSModel = TrackSelectionModel::instance();

    QList<int> rows;
    QModelIndexList trackSS = trackSSModel->selectedIndexes();
    foreach (const QModelIndex &index, trackSS) {
        const QModelIndex trackIndex = object_cast<QSortFilterProxyModel>(trackModel->sourceModel())->mapToSource(trackModel->mapToSource(index));
        if (!rows.contains(trackIndex.row()))
            rows.append(trackIndex.row());
    }

    IModel *model = IModel::instance();
    const QModelIndex trackListIndex = model->listIndex(Ac::TrackItem);
    IWriter *writer = IFilerFactory::instance()->createWriter(Ac::XmlCopyFiler);

    const int n = rows.count();
    for (int i = 0;  i < n; ++i) {
        IModelItem *track = model->itemFromIndex(model->index(rows.at(i), trackListIndex));
        writer->write(track);
    }

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("\n<clipboard>\n" + query<ICopyFiler>(writer)->data() + "\n\n</clipboard>\n");

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

    int itemType = filer->nextItemType();
    if (Mi::UnknownItem == itemType)
        return;

    beginCommand();

    while (Mi::UnknownItem != itemType) {
        Q_ASSERT(Ac::TrackItem == itemType);
        IModelItem *track = objectFactory->create(Ac::TrackItem);
        reader->read(track);
        model->insertItem(track, model->rowCount(trackListIndex), trackListIndex);

        itemType = filer->nextItemType();
    }

    endCommand();
    delete reader;
}

void Editor::selectAll()
{
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
