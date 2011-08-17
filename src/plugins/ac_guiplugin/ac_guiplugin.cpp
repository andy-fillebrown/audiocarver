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

#include <ac_model.h>

//#include <ac_guifactory.h>
#include <ac_mainwidget.h>
#include <ac_mainwindowimpl.h>
#include <ac_editorimpl.h>
#include <icore.h>
#include <mainwindow.h>

#include <QDockWidget>
#include <QTreeView>

#include <QtPlugin>

void populateModel(Model *model)
{
    Score *score = model->score();
    score->setLength(64.0f);
    List<Track> *tracks = score->tracks();
    Track *track = new Track;
    tracks->appendChild(track);
    List<Note> *notes = track->notes();
    for (int i = 0;  i < 10;  ++i) {
        Note *note = new Note;
        notes->appendChild(note);
        note->origin()->setPos(QPointF(i * 10.0f, 60.0f + (i * 2.0f)));
        note->setLength(5.0f);
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
    QDockWidget *dw = new QDockWidget(mw);
    mw->addDockWidget(Qt::LeftDockWidgetArea, dw);
    dw->setObjectName("Model Dock Widget");
    QTreeView *tv = new QTreeView(dw);
    tv->setModel(model);
    dw->setWidget(tv);
    populateModel(model);
}

Q_EXPORT_PLUGIN(AcGuiPlugin)
