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

#include "ac_pitchview.h"

#include <ac_guiconstants.h>
#include <ac_ientity.h>
#include <ac_viewmanager.h>

#include <ac_factory.h>

#include <mi_ieditor.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>

#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>

class PitchViewPrivate
{
public:
    PitchView *q;
    uint creatingNotes : 1;
    uint notesStarted : 1;
    uint curve : bitsizeof(uint) - 2;
    QModelIndexList trackSSIndexes;
    QList<IEntity*> currentNotes;
    QList<IEntity*> currentPitchCurves;
    PointList currentPoints;

    PitchViewPrivate(PitchView *q)
        :   q(q)
        ,   creatingNotes(false)
        ,   notesStarted(false)
        ,   curve(false)
    {}

    void startNote(const QPoint &pos)
    {
        IEditor::instance()->startCreating();

        IModel *model = IModel::instance();

        const int trackSS_n = trackSSIndexes.count();
        currentNotes.reserve(trackSS_n);
        currentPitchCurves.reserve(trackSS_n);

        for (int i = 0;  i < trackSS_n;  ++i) {
            const QModelIndex &trackIndex = trackSSIndexes.at(i);
            IModelItem *notesItem = model->itemFromIndex(trackIndex)->findModelItemList(Ac::NoteItem);
            const QModelIndex notesIndex = model->indexFromItem(notesItem);

            IModelItem *noteItem = ObjectFactory::instance()->create(Ac::NoteItem);
            model->insertItem(noteItem, model->rowCount(notesIndex), notesIndex);

            IEntity *noteEntity = query<IEntity>(noteItem);
            const QList<IEntity*> pitchSubEntities = noteEntity->subEntities(Ac::PitchScene);
            IEntity *pitchCurveEntity = pitchSubEntities.first();

            trackSSIndexes.append(trackIndex);
            currentNotes.append(noteEntity);
            currentPitchCurves.append(pitchCurveEntity);
        }

        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
        currentPoints.append(scenePos);

        addNotePoint(pos);
        notesStarted = true;
    }

    void addNotePoint(const QPoint &pos)
    {
        if (Qt::ControlModifier & QApplication::keyboardModifiers())
            currentPoints.last().curveType = Ac::BezierCurve;

        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
        currentPoints.append(scenePos);

        const int notes_n = currentNotes.count();
        for (int i = 0;  i < notes_n;  ++i)
            currentPitchCurves.at(i)->setPoints(currentPoints);
    }

    void moveNotePoint(const QPoint &pos)
    {
        const QPointF scenePos = q->sceneTransform().inverted().map(QPointF(pos));
        currentPoints[currentPoints.count() - 1].pos = scenePos;

        const int notes_n = currentNotes.count();
        for (int i = 0;  i < notes_n;  ++i)
            currentPitchCurves[i]->setPoints(currentPoints);
    }

    void finishNote()
    {
        if (currentPoints.count() <= 2) {
            cancelNote();
            return;
        }

        currentPoints.removeLast();

        IModel *model = IModel::instance();
        const int notes_n = currentNotes.count();

        QModelIndexList notesIndexes;
        notesIndexes.reserve(notes_n);

        QList<IModelItem*> noteItems;
        noteItems.reserve(notes_n);

        for (int i = 0;  i < notes_n;  ++i) {
            currentPitchCurves[i]->setPoints(currentPoints);

            const QModelIndex &trackIndex = trackSSIndexes.at(i);
            IModelItem *notesItem = model->itemFromIndex(trackIndex)->findModelItemList(Ac::NoteItem);
            const QModelIndex notesIndex = model->indexFromItem(notesItem);
            model->removeItem(model->rowCount(notesIndex) - 1, notesIndex);

            notesIndexes.append(notesIndex);
            noteItems.append(query<IModelItem>(currentNotes.at(i)));
        }

        IEditor *editor = IEditor::instance();
        editor->finishCreating();
        editor->beginCommand();

        for (int i = 0;  i < notes_n;  ++i)
            model->insertItem(noteItems.at(i), model->rowCount(notesIndexes.at(i)), notesIndexes.at(i));

        editor->endCommand();
        endNote();
    }

    void cancelNote()
    {
        IModel *model = IModel::instance();
        const int notes_n = currentNotes.count();

        for (int i = 0;  i < notes_n;  ++i) {
            const QModelIndex &trackIndex = trackSSIndexes.at(i);
            IModelItem *notesItem = model->itemFromIndex(trackIndex)->findModelItemList(Ac::NoteItem);
            const QModelIndex notesIndex = model->indexFromItem(notesItem);
            model->removeItem(model->rowCount(notesIndex) - 1, notesIndex);
        }

        qDeleteAll(currentNotes);

        IEditor::instance()->finishCreating();
        endNote();
    }

    void endNote()
    {
        notesStarted = false;
        creatingNotes = false;
        trackSSIndexes.clear();
        currentNotes.clear();
        currentPitchCurves.clear();
        currentPoints.clear();
        q->setCursor(GraphicsView::normalCrosshair());
    }
};

PitchView::PitchView(QGraphicsScene *scene, QWidget *parent)
    :   GraphicsHView(scene, parent)
    ,   d(new PitchViewPrivate(this))
{
    setObjectName("PitchView");
    setStyleSheet("QFrame {"
                  "border-top: 0px solid palette(shadow);"
                  "border-bottom: 1px solid palette(shadow);"
                  "border-left: 1px solid palette(shadow);"
                  "border-right: 1px solid palette(shadow);"
                  "}");
}

PitchView::~PitchView()
{
    delete d;
}

qreal PitchView::sceneHeight() const
{
    return qreal(127.0f) / ViewManager::instance()->scale(Ac::PitchScaleRole);
}

QPointF PitchView::sceneCenter() const
{
    ViewManager *vm = ViewManager::instance();
    return QPointF(vm->position(Ac::TimePositionRole), -vm->position(Ac::PitchPositionRole));
}

void PitchView::createNote()
{
    d->trackSSIndexes = IModel::instance()->findIndexes(Ac::TrackItem, Ac::RecordingRole, true);
    if (d->trackSSIndexes.isEmpty())
        QMessageBox::warning(this, PRO_NAME_STR, "No tracks are recording.");
    else {
        setCursor(creationCrosshair());
        d->creatingNotes = true;
    }
}

void PitchView::mousePressEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (Qt::LeftButton == event->button()) {
            if (!d->currentPoints.count())
                d->startNote(event->pos());
            else
                d->addNotePoint(event->pos());
            setFocus(Qt::MouseFocusReason);
        }
    } else
        GraphicsView::mousePressEvent(event);
}

void PitchView::mouseMoveEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (d->notesStarted)
            d->moveNotePoint(event->pos());
    } else
        GraphicsView::mouseMoveEvent(event);
}

void PitchView::mouseReleaseEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (Qt::RightButton == event->button()) {
            d->finishNote();
            event->accept();
        }
    } else
        GraphicsView::mouseReleaseEvent(event);
}

void PitchView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (d->creatingNotes) {
        if (Qt::LeftButton == event->button()) {
            d->finishNote();
            event->accept();
        }
    } else
        GraphicsView::mouseDoubleClickEvent(event);
}

void PitchView::keyReleaseEvent(QKeyEvent *event)
{
    if (d->creatingNotes) {
        const int key = event->key();
        switch (key) {
        case Qt::Key_Enter:
            d->finishNote();
            break;
        case Qt::Key_Escape:
            d->cancelNote();
            break;
        }
    } else
        GraphicsView::keyReleaseEvent(event);
}
