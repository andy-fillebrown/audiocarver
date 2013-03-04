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

#include "ac_gui_mainwindowextension.h"
//#include "ac_gridlinedialog.h"
#include "ac_gui_constants.h"
//#include "ac_gui_pitchview.h"
//#include "ac_gui_viewmanager.h"
#include "ac_gui_interfaces.h"
//#include "ac_noteselectionmodel.h"
//#include "ac_trackselectionmodel.h"
#include <ac_core_namespace.h>
#include <iaggregate.h>
#include <icontext.h>
#include <icore.h>
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <ieditor.h>
#include <imodel.h>
#include <imodeldata.h>
#include <imodelitemlist.h>
//#include <iqaudioengine.h>
//#include <isynthesizer.h>
#include <mi_gui_constants.h>
#include <actioncontainer.h>
#include <actionmanager.h>
#include <command.h>
#include <mainwindow.h>
#include <versiondialog.h>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QtDebug>

using namespace Ac;

namespace Gui {

void MainWindowExtension::initMenuBarGroups(QStringList &groups) const
{
    const int editGroupIndex = groups.indexOf(G_EDIT);
    groups.insert(editGroupIndex + 1, G_CREATE);
    groups.insert(editGroupIndex + 2, G_MODIFY);
    groups.insert(editGroupIndex + 3, G_BUILD);
    groups.insert(editGroupIndex + 4, G_TRANSPORT);
}

void MainWindowExtension::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (G_EDIT == menuBarGroup) {
        const int g_edit_other = groups.indexOf(G_EDIT_OTHER);
        groups.insert(g_edit_other, G_EDIT_SETTINGS);
    } else if (G_CREATE == menuBarGroup) {
        title = tr("&Create");
        id = M_CREATE;
        groups << G_CREATE_OTHER;
    } else if (G_MODIFY == menuBarGroup) {
        title = tr("&Modify");
        id = M_MODIFY;
        groups << G_MODIFY_OTHER;
    } else if (G_BUILD == menuBarGroup) {
        title = tr("&Build");
        id = M_BUILD;
        groups << G_BUILD_OTHER;
    } else if (G_TRANSPORT == menuBarGroup) {
        title = tr("T&ransport");
        id = M_TRANSPORT;
        groups << G_TRANSPORT_OTHER;
    } else if (Core::Constants::G_HELP == menuBarGroup)
        groups << G_HELP_ABOUTAUDIOCARVER;
}

void MainWindowExtension::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();
    Core::ActionContainer *editMenu = am->actionContainer(M_EDIT);
    Core::ActionContainer *createMenu = am->actionContainer(M_CREATE);
    Core::ActionContainer *modifyMenu = am->actionContainer(M_MODIFY);
    Core::ActionContainer *buildMenu = am->actionContainer(M_BUILD);
    Core::ActionContainer *transportMenu = am->actionContainer(M_TRANSPORT);
    Core::ActionContainer *helpMenu = am->actionContainer(Core::Constants::M_HELP);
    Core::Context globalContext(Core::Constants::C_GLOBAL);
//    ViewManager *viewManager = ViewManager::instance();
    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;

    // Settings Separator
    action = new QAction(this);
    action->setSeparator(true);
    cmd = am->registerAction(action, PRO_NAME_STR".Edit.Sep.Settings", globalContext);
    editMenu->addAction(cmd, G_EDIT_SETTINGS);

    // Grid Settings Action
    action = new QAction(tr("&Grid Settings..."), this);
    cmd = am->registerAction(action, SHOWGRIDSETTINGS, globalContext);
    editMenu->addAction(cmd, G_EDIT_SETTINGS);
    connect(action, SIGNAL(triggered()), SLOT(showGridSettings()));

    // Create Track Action
    action = new QAction(tr("&Track"), this);
    cmd = am->registerAction(action, CREATETRACK, globalContext);
    cmd->setDefaultKeySequence(QKeySequence("Ctrl+T"));
    createMenu->addAction(cmd, G_CREATE_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(createTrack()));

    // Create Note Action
    action = new QAction(tr("&Note"), this);
    cmd = am->registerAction(action, CREATENOTE, globalContext);
    createMenu->addAction(cmd, G_CREATE_OTHER);
//    connect(action, SIGNAL(triggered()), qobject_cast<PitchView*>(viewManager->view(PitchScene)), SLOT(createNote()));

    // Insert Points Action
    action = new QAction(tr("&Insert Points"), this);
    cmd = am->registerAction(action, INSERTPOINTS, globalContext);
    cmd->setDefaultKeySequence(Qt::Key_Insert);
    modifyMenu->addAction(cmd, G_MODIFY_OTHER);
//    connect(action, SIGNAL(triggered()), viewManager, SLOT(startInsertingPoints()));

    // Erase Action
    action = new QAction(tr("&Erase"), this);
    cmd = am->registerAction(action, ERASE, globalContext);
    cmd->setDefaultKeySequence(QKeySequence::Delete);
    modifyMenu->addAction(cmd, G_MODIFY_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(erase()));

    // Build Action
    action = new QAction(tr("&Build"), this);
    cmd = am->registerAction(action, BUILD, globalContext);
    cmd->setDefaultKeySequence(tr("Ctrl+B"));
    buildMenu->addAction(cmd, G_BUILD_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(build()));

    // Build All Action
    action = new QAction(tr("Build &All"), this);
    cmd = am->registerAction(action, BUILDALL, globalContext);
    cmd->setDefaultKeySequence(tr("Ctrl+Shift+B"));
    buildMenu->addAction(cmd, G_BUILD_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(buildAll()));

    // Start/Stop Action
    action = new QAction(tr("&Start/Stop"), this);
    cmd = am->registerAction(action, START_STOP, globalContext);
    cmd->setDefaultKeySequence(tr(" "));
    transportMenu->addAction(cmd, G_TRANSPORT_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(startOrStop()));

    // Start Action
    action = new QAction(tr("S&tart"), this);
    cmd = am->registerAction(action, START, globalContext);
    transportMenu->addAction(cmd, G_TRANSPORT_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(start()));

    // Stop Action
    action = new QAction(tr("St&op"), this);
    cmd = am->registerAction(action, STOP, globalContext);
    transportMenu->addAction(cmd, G_TRANSPORT_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(stop()));

    // About Project Action
    icon = QIcon::fromTheme(QLatin1String("help-about"));
#   ifdef Q_WS_MAC
    {   action = new QAction(icon, tr("About &"PRO_NAME_STR), this); // it's convention not to add dots to the about menu
    }
#   else
    {   action = new QAction(icon, tr("About &"PRO_NAME_STR"..."), this);
    }
#   endif
    cmd = am->registerAction(action, ABOUTAUDIOCARVER, globalContext);
    helpMenu->addAction(cmd, G_HELP_ABOUTAUDIOCARVER);
    action->setEnabled(true);
#   ifdef Q_WS_MAC
    {   cmd->action()->setMenuRole(QAction::ApplicationSpecificRole);
    }
#   endif
    connect(action, SIGNAL(triggered()), SLOT(aboutAudioCarver()));
}

void MainWindowExtension::showGridSettings()
{
//    GridLineDialog *dlg = new GridLineDialog(Core::ICore::instance()->mainWindow());
//    dlg->exec();
//    delete dlg;
}

void MainWindowExtension::createTrack()
{
    IEditor *editor = IEditor::instance();
    editor->beginCommand();
    IModelItemList *track_list = IDatabase::instance()->rootItem()->findList(TrackItem);
    IModelItem *track = QUERY(IModelItem, IDatabaseObjectFactory::instance()->create(TrackItem));
    track_list->append(track);
    editor->endCommand();
}

void MainWindowExtension::erase()
{
    IEditor *editor = IEditor::instance();

    // Erase selected points in pitch and control views.
//    ViewManager *vm = ViewManager::instance();
//    GraphicsView *view = qobject_cast<GraphicsView*>(vm->view(PitchScene));
//    if (view->pointsAreSelected()) {
//        editor->beginCommand();
//        view->removePoints();
//    }
//    view = qobject_cast<GraphicsView*>(vm->view(ControlScene));
//    if (view->pointsAreSelected()) {
//        if (!editor->isInCommand())
//            editor->beginCommand();
//        view->removePoints();
//    }
    if (editor->isInCommand()) {
        editor->endCommand();
        return;
    }

    // If no points are selected, erase selected tracks in reverse row order so
    // higher row numbers don't change if lower rows are being erased, too.
//    IModel *model = QUERY(IModel, IDatabase::instance());
//    const QModelIndexList track_ss = TrackSelectionModel::instance()->selectedRows();
//    QList<int> rows;
//    rows.reserve(track_ss.count());
//    foreach (const QModelIndex &track, track_ss)
//        rows.append(track.row());
//    qSort(rows);
//    const int n = rows.count();
//    IModelList *track_list = model->rootItem()->findList(TrackItem);
//    if (n) {
//        editor->beginCommand();
//        for (int i = n - 1;  0 <= i;  --i)
//            track_list->removeAt(rows.at(i));
//        editor->endCommand();
//        return;
//    }

    // If no points or tracks are selected, erase selected notes.
//    QModelIndexList note_ss = NoteSelectionModel::instance()->selectedIndexes();
//    if (!note_ss.isEmpty()) {
//        editor->beginCommand();
//        while (!note_ss.isEmpty()) {
//            IModelItem *note_item = model->itemFromIndex(note_ss.last());
//            note_item->list()->remove(note_item);
//            note_ss.removeLast();
//        }
//        editor->endCommand();
//    }
}

void MainWindowExtension::build()
{
    if (!maybeSaveDatabase())
        return;
    qDebug() << Q_FUNC_INFO;
}

void MainWindowExtension::buildAll()
{
    if (!maybeSaveDatabase())
        return;
//    const int track_count = IDatabase::instance()->rootItem()->findList(TrackItem)->count();
//    ISynthesizer *synth = ISynthesizer::instance();
//    for (int i = 0;  i < track_count;  ++i)
//        synth->renderTrack(i);
}

void MainWindowExtension::startOrStop()
{
//    IQAudioEngine *audio_engine = IQAudioEngine::instance();
//    if (!audio_engine)
//        return;
//    if (audio_engine->isStarted())
//        stop();
//    else
//        start();
}

void MainWindowExtension::start()
{
    IModelData *score = QUERY(IModelData, IDatabase::instance()->rootItem());
    if (score->get<int>(StartTimeRole) == score->get<int>(LengthRole)) {
        QMessageBox::warning(Core::ICore::instance()->mainWindow(), PRO_NAME_STR, "Playback start time is at the end of the score.");
        return;
    }
//    IQAudioEngine *audio_engine = IQAudioEngine::instance();
//    if (audio_engine)
//        audio_engine->start();
}

void MainWindowExtension::stop()
{
//    IQAudioEngine *audio_engine = IQAudioEngine::instance();
//    if (audio_engine)
//        audio_engine->stop();
}

void MainWindowExtension::aboutAudioCarver()
{
    if (!_versionDialog) {
        _versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(_versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    _versionDialog->show();
}

void MainWindowExtension::destroyVersionDialog()
{
    if (_versionDialog) {
        _versionDialog->deleteLater();
        _versionDialog = 0;
    }
}

bool MainWindowExtension::maybeSaveDatabase()
{
    IDatabase *database = IDatabase::instance();
    if (!database->fileName().isEmpty())
        return true;
    QWidget *main_window = Core::ICore::instance()->mainWindow();
    QMessageBox::information(main_window, "AudioCarver", "The score must be saved first");
    QString filename = QFileDialog::getSaveFileName(main_window, "", "", QObject::tr(qPrintable(database->fileFilter())));
    if (filename.isEmpty())
        return false;
    if (!filename.endsWith(database->fileExtension()))
        filename.append(database->fileExtension());
    database->write(filename);
    return !database->fileName().isEmpty();
}

}
