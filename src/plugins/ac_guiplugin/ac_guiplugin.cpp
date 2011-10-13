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
    score->setLength(128.0f);
    ObjectList<Track> *tracks = score->tracks();
    Track *track = new Track;
    tracks->append(track);
    ObjectList<Note> *notes = track->notes();
    for (int i = 0;  i < 5;  ++i) {
        Note *note = new Note;
        PointList pts;
        pts.append(Point(0,   30 + (5 * i)));
        pts.append(Point(32,  60 + (5 * i), Ac::BezierCurve));
        pts.append(Point(64,  30 + (5 * i)));
        pts.append(Point(108, 60 + (5 * i), Ac::BezierCurve));
        pts.append(Point(128, 30 + (5 * i)));
        note->pitchCurve()->setPoints(pts);
        notes->append(note);
    }
    track = new Track;
    tracks->append(track);
    notes = track->notes();
    for (int i = 0;  i < 5;  ++i) {
        Note *note = new Note;
        PointList pts;
        pts.append(Point(0,   60 + (5 * i)));
        pts.append(Point(32,  90 + (5 * i), Ac::BezierCurve));
        pts.append(Point(64,  60 + (5 * i)));
        pts.append(Point(108, 90 + (5 * i), Ac::BezierCurve));
        pts.append(Point(128, 60 + (5 * i)));
        note->pitchCurve()->setPoints(pts);
        notes->append(note);
    }
    GridSettings *gridSettings = score->gridSettings();
    ObjectList<TimeGridLine> *timeGridLines = gridSettings->timeGridLines();
    TimeGridLine *timeGridLine = 0;
    for (int i = 0;  i < 128;  ++i) {
        QString label = QString("%1.%2").arg((i / 4) + 1).arg((i % 4) + 1);
        if (label.endsWith(".1"))
            label.chop(2);
        timeGridLine = new TimeGridLine;
        timeGridLine->setLocation(i);
        timeGridLine->setLabel(label);
        timeGridLines->append(timeGridLine);
    }
    timeGridLines[0].at(0)->setColor(QColor(0, 127, 0));
    for (int i = 1;  i < 128;  i*=2)
        for (int j = i;  j < 128;  j+=i)
            timeGridLines->at(j)->setPriority(128 / (i + 1));
    timeGridLine = new TimeGridLine;
    timeGridLine->setLocation(128);
    timeGridLine->setPriority(0);
    timeGridLine->setColor(QColor(127, 0, 0));
    timeGridLines->append(timeGridLine);
    ObjectList<PitchGridLine> *pitchGridLines = gridSettings->pitchGridLines();
    PitchGridLine *pitchGridLine = 0;
    for (int i = 0;  i < 128;  ++i) {
        pitchGridLine = new PitchGridLine;
        pitchGridLine->setLocation(i);
        pitchGridLine->setLabel(QString("%1.0").arg(i));
        pitchGridLines->append(pitchGridLine);
    }
    for (int i = 0;  i < 128;  i+=12)
        pitchGridLines->at(i)->setColor(QColor(191, 0, 0));
    for (int i = 7;  i < 128;  i+=12)
        pitchGridLines->at(i)->setColor(QColor(0, 0, 191));
    int octaveMod[] = { 3, 2, 1, 2, 3, 0, 3, 2, 1, 2, 3, 4 };
    for (int i = 0;  i < 120;  i+=12) {
        int octave = i % 12;
        int mod = octaveMod[octave];
        pitchGridLines->at(i)->setPriority(10 + mod);
        pitchGridLines->at(i + 1)->setPriority(50 + mod);
        pitchGridLines->at(i + 2)->setPriority(40 + mod);
        pitchGridLines->at(i + 3)->setPriority(30 + mod);
        pitchGridLines->at(i + 4)->setPriority(40 + mod);
        pitchGridLines->at(i + 5)->setPriority(30 + mod);
        pitchGridLines->at(i + 6)->setPriority(50 + mod);
        pitchGridLines->at(i + 7)->setPriority(20 + mod);
        pitchGridLines->at(i + 8)->setPriority(50 + mod);
        pitchGridLines->at(i + 9)->setPriority(40 + mod);
        pitchGridLines->at(i + 10)->setPriority(30 + mod);
        pitchGridLines->at(i + 11)->setPriority(40 + mod);
    }
    int mod = octaveMod[11];
    pitchGridLines->at(120)->setPriority(10 + mod);
    pitchGridLines->at(121)->setPriority(50 + mod);
    pitchGridLines->at(122)->setPriority(40 + mod);
    pitchGridLines->at(123)->setPriority(30 + mod);
    pitchGridLines->at(124)->setPriority(40 + mod);
    pitchGridLines->at(125)->setPriority(30 + mod);
    pitchGridLines->at(126)->setPriority(50 + mod);
    pitchGridLines->at(0)->setLabel("");
    pitchGridLines->at(0)->setPriority(0);
    pitchGridLines->at(60)->setPriority(0);
    pitchGridLines->at(127)->setLabel("");
    pitchGridLines->at(127)->setPriority(0);
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

    MainWidget *widget = new MainWidget(mw);
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
