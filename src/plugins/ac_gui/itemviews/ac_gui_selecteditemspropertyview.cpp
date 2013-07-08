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

#include "ac_gui_selecteditemspropertyview.h"
#include "ac_gui_colordelegate.h"
#include "ac_gui_instrumentdelegate.h"
#include "ac_gui_lengthdelegate.h"
#include "ac_gui_selecteditemspropertymodel.h"
#include "ac_gui_togglebuttondelegate.h"
#include "ac_gui_volumedelegate.h"
#include <ac_core_namespace.h>
#include <ieditor.h>
#include <iselectionset.h>
#include <QHeaderView>
#include <QKeyEvent>

using namespace Ac;
using namespace Mi;
using namespace Qt;

class SelectedItemsPropertyViewPrivate
{
public:
    SelectedItemsPropertyView *q;
    SelectedItemsPropertyModel *selectedItemsPropertyModel;
    DoubleDelegate *doubleDelegate;
    ColorDelegate *colorDelegate;
    InstrumentDelegate *instrumentDelegate;
    LengthDelegate *lengthDelegate;
    ToggleButtonDelegate *toggleButtonDelegate;
    VolumeDelegate *volumeDelegate;

    SelectedItemsPropertyViewPrivate(SelectedItemsPropertyView *q)
        :   q(q)
        ,   selectedItemsPropertyModel(new SelectedItemsPropertyModel(q))
        ,   doubleDelegate(new DoubleDelegate(q))
        ,   colorDelegate(new ColorDelegate(q))
        ,   instrumentDelegate(new InstrumentDelegate(q))
        ,   lengthDelegate(new LengthDelegate(q))
        ,   toggleButtonDelegate(new ToggleButtonDelegate(q))
        ,   volumeDelegate(new VolumeDelegate(q))
    {
        doubleDelegate->setCustomColumn(1);
        colorDelegate->setCustomColumn(1);
        instrumentDelegate->setCustomColumn(1);
        lengthDelegate->setCustomColumn(1);
        toggleButtonDelegate->setCustomColumn(1);
        volumeDelegate->setCustomColumn(1);
        toggleButtonDelegate->setButtonColumnWidth(16);
    }
};

SelectedItemsPropertyView::SelectedItemsPropertyView(QWidget *parent)
    :   PropertyView(parent)
    ,   d(new SelectedItemsPropertyViewPrivate(this))
{
    setModel(d->selectedItemsPropertyModel);
    connect(d->selectedItemsPropertyModel, SIGNAL(modelReset()), SLOT(updateDelegates()));
    updateDelegates();
    QHeaderView *v_header = verticalHeader();
    v_header->hideSection(0);
    QHeaderView *h_header = horizontalHeader();
    h_header->resizeSections(QHeaderView::ResizeToContents);
    h_header->resizeSection(1, 0);
}

SelectedItemsPropertyView::~SelectedItemsPropertyView()
{
    delete d;
}

void SelectedItemsPropertyView::keyReleaseEvent(QKeyEvent *event)
{
    if (Key_Escape == event->key()) {
        IEditor *editor = IEditor::instance();
        editor->currentSelection(NoteItem)->clear();
        editor->currentSelection(TrackItem)->clear();
    }
    PropertyView::keyReleaseEvent(event);
}

void SelectedItemsPropertyView::updateDelegates()
{
    const int row_count = model()->rowCount();
    for (int i = 0;  i < row_count;  ++i) {
        int role_type = model()->data(model()->index(i, 0), RoleTypeRole).toInt();
        switch (role_type) {
        case StartTimeRole:
        case TimeSnapRole:
        case PitchSnapRole:
        case ControlSnapRole:
            setItemDelegateForRow(i, d->doubleDelegate);
            break;
        case ColorRole:
            setItemDelegateForRow(i, d->colorDelegate);
            break;
        case InstrumentRole:
            setItemDelegateForRow(i, d->instrumentDelegate);
            break;
        case LengthRole:
            setItemDelegateForRow(i, d->lengthDelegate);
            break;
        case VisibilityRole:
        case SnapEnabledRole:
        case GridSnapEnabledRole:
            setItemDelegateForRow(i, d->toggleButtonDelegate);
            break;
        case VolumeRole:
            setItemDelegateForRow(i, d->volumeDelegate);
            break;
        default:
            setItemDelegateForRow(i, 0);
        }
    }
}
