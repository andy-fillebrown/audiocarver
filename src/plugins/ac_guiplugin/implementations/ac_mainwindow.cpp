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

#include "ac_mainwindow.h"

#include <ac_guiconstants.h>
#include <ac_pitchview.h>
#include <ac_viewmanager.h>

#include <ac_iaudioengine.h>
#include <ac_ifactory.h>
#include <ac_isynthesizer.h>
#include <ac_namespace.h>
#include <ac_noteselectionmodel.h>
#include <ac_trackselectionmodel.h>

#include <mi_guiconstants.h>
#include <mi_ieditor.h>

#include <mi_idatabase.h>
#include <mi_imodel.h>

#include <actioncontainer.h>
#include <actionmanager.h>
#include <command.h>
#include <icontext.h>
#include <icore.h>
#include <mainwindow.h>
#include <versiondialog.h>

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QTimer>

class MainWindowPrivate
{
public:
    Core::VersionDialog *versionDialog;

    MainWindowPrivate()
        :   versionDialog(0)
    {}
};

MainWindow::MainWindow()
    :   d(new MainWindowPrivate)
{
    connect(IDatabase::instance(), SIGNAL(databaseReset()), SLOT(databaseReset()));

    QTimer *startup_timer = new QTimer;
    startup_timer->setSingleShot(true);
    connect(startup_timer, SIGNAL(timeout()), SLOT(databaseReset()));
    startup_timer->start();
}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::initMenuBarGroups(QStringList &groups) const
{
    const int editGroupIndex = groups.indexOf(G_EDIT);
    groups.insert(editGroupIndex + 1, G_CREATE);
    groups.insert(editGroupIndex + 2, G_MODIFY);
    groups.insert(editGroupIndex + 3, G_BUILD);
    groups.insert(editGroupIndex + 4, G_TRANSPORT);
}

void MainWindow::initMenuGroups(const QString &menuBarGroup, QString &id, QString &title, QStringList &groups) const
{
    if (G_CREATE == menuBarGroup) {
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
        groups  << G_HELP_ABOUTAUDIOCARVER;
}

void MainWindow::initActions()
{
    Core::ActionManager *am = Core::ICore::instance()->actionManager();

    Core::ActionContainer *createMenu = am->actionContainer(M_CREATE);
    Core::ActionContainer *modifyMenu = am->actionContainer(M_MODIFY);
    Core::ActionContainer *buildMenu = am->actionContainer(M_BUILD);
    Core::ActionContainer *transportMenu = am->actionContainer(M_TRANSPORT);
    Core::ActionContainer *helpMenu = am->actionContainer(Core::Constants::M_HELP);

    Core::Context globalContext(Core::Constants::C_GLOBAL);

    ViewManager *viewManager = ViewManager::instance();

    QIcon icon;
    QAction *action = 0;
    Core::Command *cmd = 0;

    // Create Track Action
    action = new QAction(tr("&Track"), this);
    cmd = am->registerAction(action, CREATETRACK, globalContext);
    createMenu->addAction(cmd, G_CREATE_OTHER);
    connect(action, SIGNAL(triggered()), SLOT(createTrack()));

    // Create Note Action
    action = new QAction(tr("&Note"), this);
    cmd = am->registerAction(action, CREATENOTE, globalContext);
    createMenu->addAction(cmd, G_CREATE_OTHER);
    connect(action, SIGNAL(triggered()), object_cast<PitchView>(viewManager->view(Ac::PitchScene)), SLOT(createNote()));

    // Insert Points Action
    action = new QAction(tr("&Insert Points"), this);
    cmd = am->registerAction(action, INSERTPOINTS, globalContext);
    cmd->setDefaultKeySequence(Qt::Key_Insert);
    modifyMenu->addAction(cmd, G_MODIFY_OTHER);
    connect(action, SIGNAL(triggered()), viewManager, SLOT(startInsertingPoints()));

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

void MainWindow::aboutAudioCarver()
{
    if (!d->versionDialog) {
        d->versionDialog = new Core::VersionDialog(Core::ICore::instance()->mainWindow());
        connect(d->versionDialog, SIGNAL(finished(int)), SLOT(destroyVersionDialog()));
    }
    d->versionDialog->show();
}

void MainWindow::destroyVersionDialog()
{
    if (d->versionDialog) {
        d->versionDialog->deleteLater();
        d->versionDialog = 0;
    }
}

void MainWindow::createTrack()
{
    IEditor *editor = IEditor::instance();
    editor->beginCommand();
    IModel *model = IModel::instance();
    IModelItem *track = IObjectFactory::instance()->create(Ac::TrackItem);
    model->insertItem(track, 0, model->listIndex(Ac::TrackItem));
    editor->endCommand();
}

void MainWindow::erase()
{
    IEditor *editor = IEditor::instance();
    bool commandStarted = false;

    // Erase selected points in pitch and control views.
    ViewManager *vm = ViewManager::instance();
    GraphicsView *view = object_cast<GraphicsView>(vm->view(Ac::PitchScene));
    if (view->pointsAreSelected()) {
        editor->beginCommand();
        commandStarted = true;
        view->removePoints();
    }
    view = object_cast<GraphicsView>(vm->view(Ac::ControlScene));
    if (view->pointsAreSelected()) {
        if (!commandStarted) {
            editor->beginCommand();
            commandStarted = true;
        }
        view->removePoints();
    }
    if (commandStarted) {
        editor->endCommand();
        return;
    }

    // If no points are selected, erase selected tracks in reverse row order so
    // higher row numbers don't change if lower rows are being erased, too.
    IModel *model = IModel::instance();

    TrackSelectionModel *trackSSModel = TrackSelectionModel::instance();
    const QModelIndex trackListIndex = model->listIndex(Ac::TrackItem);
    const QModelIndexList trackSS = trackSSModel->selectedRows();
    QList<int> rows;
    rows.reserve(trackSS.count());
    foreach (const QModelIndex &track, trackSS)
        rows.append(track.row());
    qSort(rows);
    const int n = rows.count();
    if (n) {
        editor->beginCommand();
        for (int i = n - 1;  0 <= i;  --i)
            model->removeItem(rows.at(i), trackListIndex);
        editor->endCommand();
        return;
    }

    // If no points or tracks are selected, erase selected notes.
    NoteSelectionModel *noteSSModel = NoteSelectionModel::instance();
    QModelIndexList noteSS = noteSSModel->selectedIndexes();
    if (!noteSS.isEmpty()) {
        editor->beginCommand();
        while (!noteSS.isEmpty()) {
            const QModelIndex noteIndex = noteSS.last();
            const QModelIndex noteListIndex = model->parent(noteIndex);
            model->removeItem(noteIndex.row(), noteListIndex);
            noteSS = noteSSModel->selectedIndexes();
        }
        editor->endCommand();
    }
}

void MainWindow::build()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::buildAll()
{
    const IModel *model = IModel::instance();
    const QModelIndex trackList = model->listIndex(Ac::TrackItem);
    const int n = model->rowCount(trackList);

    ISynthesizer *synth = ISynthesizer::instance();

    for (int i = 0;  i < n;  ++i)
        synth->renderTrack(i);
}

void MainWindow::startOrStop()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    if (!audio_engine)
        return;
    if (audio_engine->isStarted())
        audio_engine->stop();
    else
        audio_engine->start();
}

void MainWindow::start()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    if (audio_engine)
        audio_engine->start();
}

void MainWindow::stop()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    if (audio_engine)
        audio_engine->stop();
}

void MainWindow::databaseReset()
{
    static bool resetting = false;
    if (resetting)
        return;
    resetting = true;

    IDatabase *db = IDatabase::instance();

    QString file_name;
    while (file_name.isEmpty()) {
        file_name = QFileDialog::getSaveFileName(
                    Core::ICore::instance()->mainWindow(),
                    "Create/Open Project",
                    QDir::convertSeparators(QString("%1/untitled%2")
                        .arg(QDir::homePath())
                        .arg(db->fileExtension())),
                    tr(qPrintable(db->fileFilter())),
                    0,
                    QFileDialog::DontConfirmOverwrite);
    }
    if (!file_name.endsWith(db->fileExtension()))
        file_name.append(db->fileExtension());

    if (!QFile::exists(file_name))
        db->write(file_name);

    db->read(file_name);

    resetting = false;
}
