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

#include "ac_guiplugin.h"

#include <ac_gui_database.h>
#include <ac_gui_editor.h>
//#include <ac_mainwidget.h>
//#include <ac_guimainwindowextension.h>
//#include <ac_selecteditemspropertyview.h>
//#include <ac_trackview.h>

//#include <mi_idatabase.h>

//#include <icore.h>
//#include <mainwindow.h>

//#include <QDockWidget>

#include <QtPlugin>

#ifdef QT_DEBUG
static bool test();
#endif

namespace Ac {

bool GuiPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    (new Gui::Database())->init();
    (new Gui::Editor)->init();
//    addAutoReleasedObject(new Ac::Gui::MainWindowExtension);
    return true;
}

void GuiPlugin::extensionsInitialized()
{
//    Core::MainWindow *mw = Core::ICore::instance()->mainWindow();

//    MainWidget *widget = new MainWidget(mw);
//    mw->setCentralWidget(widget);

#ifdef QT_DEBUG
    test();
#endif
}

} // namespace Ac

Q_EXPORT_PLUGIN(Ac::GuiPlugin)

#ifdef QT_DEBUG

#include <ac_ientity.h>
#include <mi_idataobjectfactory.h>
#include <mi_imodeldata.h>
#include <mi_imodelitem.h>

#define RUN(x) if (!x()) return false
#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

bool test_1()
{
    // Make sure querying super-aggregators succeeds.
    // Super-aggregators should create aggregates on demand.
    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(Ac::ControlCurveItem);
    CHECK(control_curve);
    IEntity *entity = query<IEntity>(control_curve);
    CHECK(entity);
    return true;
}

bool test_2()
{
    // Make sure querying constant super-aggregators fails.
    // Constant super-aggregators should not create aggregates on demand.
    const IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(Ac::ControlCurveItem);
    CHECK(control_curve);
    const IEntity *entity = query<IEntity>(control_curve);
    CHECK(!entity);
    return true;
}

bool test_3()
{
    // Make sure querying aggregates for other aggregates succeeds.
    // Aggregates should pass the query to their aggregator.
    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(Ac::ControlCurveItem);
    CHECK(control_curve);
    IModelData *data = query<IModelData>(control_curve);
    CHECK(data);
    IEntity *entity = query<IEntity>(data);
    CHECK(entity);
    return true;
}

bool test_4()
{
    // Make sure querying constant aggregates for other aggregates does not create aggregates on demand.
    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(Ac::ControlCurveItem);
    CHECK(control_curve);
    const IModelData *data = query<IModelData>(control_curve);
    CHECK(data);
    const IEntity *entity = query<IEntity>(data);
    CHECK(!entity);
    return true;
}

bool test_5()
{
    // Make sure querying constant aggregates succeeds for an aggregate that was previously created on demand.
    IAggregator *control_curve = query<IDataObjectFactory>(IDatabase::instance())->create(Ac::ControlCurveItem);
    CHECK(control_curve);
    IEntity *entity = query<IEntity>(control_curve);
    CHECK(entity);
    const IAggregator *const_control_curve = control_curve;
    const IEntity *const_entity = query<IEntity>(const_control_curve);
    CHECK(const_entity);
    return true;
}

bool test()
{
    RUN(test_5);
    RUN(test_4);
    RUN(test_3);
    RUN(test_2);
    RUN(test_1);
    qDebug() << "Ac::GuiPlugin tests passed.";
    return true;
}

#endif // #ifdef QT_DEBUG
