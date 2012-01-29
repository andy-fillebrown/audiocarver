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

#include "ac_selecteditemspropertyview.h"

#include <ac_colordelegate.h>
#include <ac_instrumentdelegate.h>
#include <ac_lengthdelegate.h>
#include <ac_noteselectionmodel.h>
#include <ac_selecteditemspropertymodel.h>
#include <ac_recordbuttondelegate.h>
#include <ac_trackselectionmodel.h>
#include <ac_volumedelegate.h>

#include <QHeaderView>
#include <QKeyEvent>

class SelectedItemsPropertyViewPrivate
{
public:
    SelectedItemsPropertyView *q;
    SelectedItemsPropertyModel *selectedItemsPropertyModel;
    ColorDelegate *colorDelegate;
    InstrumentDelegate *instrumentDelegate;
    LengthDelegate *lengthDelegate;
    RecordButtonDelegate *recordButtonDelegate;
    ToggleButtonDelegate *toggleButtonDelegate;
    VolumeDelegate *volumeDelegate;

    SelectedItemsPropertyViewPrivate(SelectedItemsPropertyView *q)
        :   q(q)
        ,   selectedItemsPropertyModel(new SelectedItemsPropertyModel(q))
        ,   colorDelegate(new ColorDelegate(q))
        ,   instrumentDelegate(new InstrumentDelegate(q))
        ,   lengthDelegate(new LengthDelegate(q))
        ,   recordButtonDelegate(new RecordButtonDelegate(q))
        ,   toggleButtonDelegate(new ToggleButtonDelegate(q))
        ,   volumeDelegate(new VolumeDelegate(q))
    {
        colorDelegate->setCustomColumn(1);
        instrumentDelegate->setCustomColumn(1);
        lengthDelegate->setCustomColumn(1);
        recordButtonDelegate->setCustomColumn(1);
        toggleButtonDelegate->setCustomColumn(1);
        volumeDelegate->setCustomColumn(1);

        recordButtonDelegate->setButtonColumnWidth(16);
        toggleButtonDelegate->setButtonColumnWidth(16);
    }

    void init()
    {
        selectedItemsPropertyModel->appendSelectionModel(TrackSelectionModel::instance());
        selectedItemsPropertyModel->appendSelectionModel(NoteSelectionModel::instance());
    }
};

SelectedItemsPropertyView::SelectedItemsPropertyView(QWidget *parent)
    :   PropertyView(parent)
    ,   d(new SelectedItemsPropertyViewPrivate(this))
{
    d->init();

    setModel(d->selectedItemsPropertyModel);
    connect(d->selectedItemsPropertyModel, SIGNAL(modelReset()), SLOT(updateDelegates()));
    updateDelegates();

    QHeaderView *v_header = verticalHeader();
    v_header->hideSection(0);

    QHeaderView *h_header = horizontalHeader();
    h_header->resizeSections(QHeaderView::ResizeToContents);
}

SelectedItemsPropertyView::~SelectedItemsPropertyView()
{
    delete d;
}

void SelectedItemsPropertyView::keyReleaseEvent(QKeyEvent *event)
{
    if (Qt::Key_Escape == event->key()) {
        NoteSelectionModel::instance()->clear();
        TrackSelectionModel::instance()->clear();
    }

    PropertyView::keyReleaseEvent(event);
}

void SelectedItemsPropertyView::updateDelegates()
{
    const int row_count = model()->rowCount();
    for (int i = 0;  i < row_count;  ++i) {
        int role_type = model()->data(model()->index(i, 0), Mi::RoleTypeRole).toInt();
        switch (role_type) {
        case Ac::ColorRole:
            setItemDelegateForRow(i, d->colorDelegate);
            break;
        case Ac::InstrumentRole:
            setItemDelegateForRow(i, d->instrumentDelegate);
            break;
        case Ac::LengthRole:
            setItemDelegateForRow(i, d->lengthDelegate);
            break;
        case Ac::RecordingRole:
            setItemDelegateForRow(i, d->recordButtonDelegate);
            break;
        case Ac::VisibilityRole:
            setItemDelegateForRow(i, d->toggleButtonDelegate);
            break;
        case Ac::VolumeRole:
            setItemDelegateForRow(i, d->volumeDelegate);
            break;
        default:
            setItemDelegateForRow(i, 0);
        }
    }
}
