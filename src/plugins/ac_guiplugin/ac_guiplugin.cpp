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

#include "ac_guiplugin.h"

#include <ac_gridline.h>
#include <ac_gridsettings.h>
#include <ac_model.h>
#include <ac_note.h>
#include <ac_pitchcurve.h>
#include <ac_score.h>
#include <ac_track.h>

#include <ac_editorimpl.h>
#include <ac_mainwidget.h>
#include <ac_mainwindowimpl.h>

#include <icore.h>
#include <mainwindow.h>

#include <QDockWidget>
#include <QTreeView>

#include <QtPlugin>

void populateModel(Model *model)
{
    Score *score = model->score();
    score->setLength(64.0f);
    ObjectList<Track> *tracks = score->tracks();
    Track *track = new Track;
    tracks->append(track);
    ObjectList<Note> *notes = track->notes();
    for (int i = 0;  i < 5;  ++i) {
        Note *note = new Note;
        PointList pts;
        pts.append(Point(10 - i, 30 + (5 * i)));
        pts.append(Point(10 - i + 100, 60 + (5 * i)));
        note->pitchCurve()->setPoints(pts);
        notes->append(note);
    }
    track = new Track;
    tracks->append(track);
    notes = track->notes();
    for (int i = 0;  i < 5;  ++i) {
        Note *note = new Note;
        PointList pts;
        pts.append(Point(10 - i, 60 + (5 * i)));
        pts.append(Point(10 - i + 100, 90 + (5 * i)));
        note->pitchCurve()->setPoints(pts);
        notes->append(note);
    }
//    GridSettings *gridSettings = score->gridSettings();
//    ObjectList<TimeGridLine> *timeGridLines = gridSettings->timeGridLines();
//    TimeGridLine *timeGridLine = new TimeGridLine;
//    timeGridLine->setColor(QColor(0, 127, 0));
//    timeGridLines->append(timeGridLine);
//    for (int i = 1;  i < 128;  ++i) {
//        QString label = QString("%1.%2").arg((i / 4) + 1).arg(i % 4);
//        if (label.endsWith(".0"))
//            label.chop(2);
//        timeGridLine = new TimeGridLine;
//        timeGridLine->setLocation(i);
//        timeGridLine->setLabel(label);
//        timeGridLines->append(timeGridLine);
//    }
//    for (int i = 1;  i < 128;  i*=2)
//        for (int j = i;  j < 128;  j+=i)
//            timeGridLines->at(j)->setPriority(128 / (i + 1));
//    timeGridLine = new TimeGridLine;
//    timeGridLine->setLocation(128);
//    timeGridLine->setPriority(0);
//    timeGridLine->setColor(QColor(127, 0, 0));
//    timeGridLines->append(timeGridLine);
}

bool AcGuiPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
//    addAutoReleasedObject(new AcGuiFactory);
    addAutoReleasedObject(new AcMainWindowImpl);
    addAutoReleasedObject(new AcEditorImpl);
    return true;
}

void AcGuiPlugin::extensionsInitialized()
{
    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();

    AcMainWidget *widget = new AcMainWidget(mw);
    mw->setCentralWidget(widget);

    Model *model = new Model;
    widget->setModel(model);

    QDockWidget *dw = new QDockWidget(mw);
    mw->addDockWidget(Qt::LeftDockWidgetArea, dw);
    dw->setObjectName("Model Dock Widget");

    QTreeView *tv = new QTreeView(dw);
    tv->setModel(model);
    dw->setWidget(tv);

    populateModel(model);
}

Q_EXPORT_PLUGIN(AcGuiPlugin)
