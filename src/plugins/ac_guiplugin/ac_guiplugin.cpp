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

#include <ac_item.h>

#include <ac_mainwidget.h>
#include <ac_mainwindowimpl.h>
#include <ac_editorimpl.h>
#include <ac_scene.h>

#include <icore.h>
#include <mainwindow.h>

#include <QDockWidget>
#include <QTreeView>

#include <QtPlugin>

void populateModel(Model *model)
{
    Score *score = model->score();
    score->setLength(64.0f);
    ItemList<Track> *tracks = score->tracks();
    Track *track = new Track;
    tracks->appendChild(track);
    ItemList<Note> *notes = track->notes();
    for (int i = 0;  i < 5;  ++i) {
        Note *note = new Note;
        PointList pts;
        pts.append(Point(10 - i, 30 + i));
        pts.append(Point(10 - i + 100, 60 + i));
        note->setPoints(pts);
        notes->appendChild(note);
    }
    track = new Track;
    tracks->appendChild(track);
    notes = track->notes();
    for (int i = 0;  i < 5;  ++i) {
        Note *note = new Note;
        PointList pts;
        pts.append(Point(10 - i, 60 + i));
        pts.append(Point(10 - i + 100, 90 + i));
        note->setPoints(pts);
        notes->appendChild(note);
    }
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

    Model *model = new Model(mw);
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
