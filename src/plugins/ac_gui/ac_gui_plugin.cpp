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

#include "ac_gui_plugin.h"
#include "ac_gui_databaseobjectfactory.h"
#include "ac_gui_editor.h"
#include "ac_gui_mainwidget.h"
#include "ac_gui_mainwindowextension.h"
//#include "ac_selecteditemspropertyview.h"
//#include "ac_trackview.h"
#include <ac_core_database.h>
#include <ac_core_namespace.h>
#include <mainwindow.h>
#include <icore.h>
#include <QtPlugin>

#ifdef QT_DEBUG
static bool test();
#endif

using namespace Core;
using namespace Gui;

namespace Ac {
namespace Gui {

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    (new ::Gui::DatabaseObjectFactory)->initialize();
    (new Core::Database)->initialize();
    (new Editor)->initialize();
    addAutoReleasedObject(new MainWindowExtension);
    return true;
}

void Plugin::extensionsInitialized()
{
    MainWindow *main_window = ICore::instance()->mainWindow();
    MainWidget *widget = new MainWidget(main_window);
    main_window->setCentralWidget(widget);
#ifdef QT_DEBUG
    test();
#endif
}

}
}

Q_EXPORT_PLUGIN(Ac::Gui::Plugin)

#ifdef QT_DEBUG

#include <iaggregate.h>
#include <idatabaseobjectfactory.h>
#include <imodeldata.h>
#include <imodelitem.h>
#include <QtDebug>

#define RUN(x) if (!x()) return false
#define CHECK(x) if (!(x)) { Q_ASSERT(x); return false; }

using namespace Ac;

bool test_create_item(IDatabaseObjectFactory *factory, int itemType)
{
    IAggregate *item = factory->create(itemType);
    if (!item)
        return false;
    delete item;
    return true;
}

bool test_1()
{
    // Make sure all item types can be created.
    // Note:  Don't create a score item since it makes IDatabase::rootItem() return
    // an unused score.
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    CHECK(test_create_item(factory, TrackItem));
    CHECK(test_create_item(factory, TrackListItem));
    CHECK(test_create_item(factory, NoteItem));
    CHECK(test_create_item(factory, NoteListItem));
    CHECK(test_create_item(factory, PitchCurveItem));
    CHECK(test_create_item(factory, ControlCurveItem));
    CHECK(test_create_item(factory, ControlCurveListItem));
    CHECK(test_create_item(factory, GridSettingsItem));
    CHECK(test_create_item(factory, TimeGridLineItem));
    CHECK(test_create_item(factory, TimeGridLineListItem));
    CHECK(test_create_item(factory, PitchGridLineItem));
    CHECK(test_create_item(factory, PitchGridLineListItem));
    CHECK(test_create_item(factory, ControlGridLineItem));
    CHECK(test_create_item(factory, ControlGridLineListItem));
    CHECK(test_create_item(factory, ViewSettingsItem));
    CHECK(test_create_item(factory, ProjectSettingsItem));
    return true;
}

bool test()
{
    RUN(test_1);
    qDebug() << "Ac::Gui::Plugin tests passed.";
    return true;
}

#endif
