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

#include "ac_gui_selecteditemspropertymodel.h"
#include "ac_gui_namespace.h"
#include <idatabase.h>
#include <ieditor.h>
#include <igraphicsitem.h>
#include <imodel.h>
#include <imodelitem.h>
#include <iselectionset.h>
#include <iundomanager.h>

using namespace Ac;
using namespace Mi;
using namespace Qt;

class SelectedItemsPropertyModelPrivate
{
public:
    SelectedItemsPropertyModel *q;
    QList<IModelItem*> selectedItems;
    QMap<int, QVariant> dataMap;
    uint nothingSelected : 1;

    SelectedItemsPropertyModelPrivate(SelectedItemsPropertyModel *q)
        :   q(q)
        ,   nothingSelected(true)
    {}

    void update()
    {
        IEditor *editor = IEditor::instance();
        QList<IGraphicsItem*> graphics_items;
        graphics_items.append(editor->currentSelection(NoteItem)->items());
        graphics_items.append(editor->currentSelection(TrackItem)->items());
        selectedItems.clear();
        foreach (IGraphicsItem *graphics_item, graphics_items) {
            IModelItem *model_item = query<IModelItem>(graphics_item);
            if (!selectedItems.contains(model_item))
                selectedItems.append(model_item);
        }
        nothingSelected = selectedItems.isEmpty();
        if (nothingSelected) {
            IModelItem *score = IDatabase::instance()->rootItem();
            selectedItems.append(score);
            selectedItems.append(score->findItem(ProjectSettingsItem));
            selectedItems.append(score->findItem(GridSettingsItem));
        }
        dataMap.clear();
        foreach (IModelItem *selected_item, selectedItems) {
            const int role_count = selected_item->roleCount();
            for (int i = 0;  i < role_count;  ++i) {
                const int role = selected_item->roleAt(i);
                const QVariant value = selected_item->getValue(role);
                if (!dataMap.contains(role))
                    dataMap.insert(role, value);
                else if (value != dataMap.value(role)) {
                    dataMap.remove(role);
                    dataMap.insert(role, "<varies>");
                }
            }
        }
        q->reset();
    }
};

static SelectedItemsPropertyModel *instance = 0;

SelectedItemsPropertyModel *SelectedItemsPropertyModel::instance()
{
    return ::instance;
}

SelectedItemsPropertyModel::SelectedItemsPropertyModel(QObject *parent)
    :   PropertyModel(parent)
    ,   d(new SelectedItemsPropertyModelPrivate(this))
{
    ::instance = this;
    connect(IModel::instance(), SIGNAL(dataChanged(IModelItem*,int)), SLOT(update(IModelItem*,int)));
    update();
}

SelectedItemsPropertyModel::~SelectedItemsPropertyModel()
{
    delete d;
}

int SelectedItemsPropertyModel::rowCount(const QModelIndex &parent) const
{
    return d->dataMap.count();
}

ItemFlags SelectedItemsPropertyModel::flags(const QModelIndex &index) const
{
    if (d->nothingSelected) {
        IModelItem *grid_settings = IDatabase::instance()->rootItem()->findItem(GridSettingsItem);
        bool snap_enabled = get<bool>(grid_settings, SnapEnabledRole);

        // Disable snap settings if snap is off or grid snap is on.
        if (!snap_enabled
                || get<bool>(grid_settings, GridSnapEnabledRole)) {
            switch (index.data(RoleTypeRole).toInt()) {
            case TimeSnapRole:
            case PitchSnapRole:
            case ControlSnapRole:
                return NoItemFlags;
            default:
                break;
            }
        }

        // Disable grid snap setting if snap is off.
        if (!snap_enabled
                && GridSnapEnabledRole == index.data(RoleTypeRole).toInt())
            return NoItemFlags;
    }
    return PropertyModel::flags(index);
}

QVariant SelectedItemsPropertyModel::data(const QModelIndex &index, int role) const
{
    if (Mi::RoleTypeRole == role)
        return d->dataMap.keys().at(index.row());
    if (Qt::DisplayRole != role
            && Qt::EditRole != role)
        return QVariant();
    const int column = index.column();
    const int row = index.row();
    if (0 == row)
        return QVariant();
    QVariant value;
    if (0 == column) {
        const QList<int> keys = d->dataMap.keys();
        if (row < keys.count())
            value = itemDataRoleString(keys.at(row));
    } else if (1 == column) {
        const QList<QVariant> values = d->dataMap.values();
        if (row < values.count())
            value = values.at(row);
    }
    return value;
}

bool SelectedItemsPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ((DisplayRole != role && EditRole != role)
            ||  1 != index.column())
        return false;
    IUndoManager *undo_manager = IUndoManager::instance();
    undo_manager->beginCommand();
    int property_role = d->dataMap.keys().at(index.row());
    foreach (IModelItem *item, d->selectedItems)
        item->set(property_role, value);
    undo_manager->endCommand();
    return true;
}

void SelectedItemsPropertyModel::update(IModelItem *item, int role)
{
    if (PlaybackTimeRole == role)
        return;
    d->update();
}
