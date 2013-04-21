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

#include "ac_core_gridlinemodel.h"
#include "ac_core_gridline_aggregate.h"
#include "ac_core_namespace.h"
#include <idatabase.h>
#include <idatabaseobjectfactory.h>
#include <ifilefiler.h>
#include <ifilerfactory.h>
#include <imodel.h>
#include <imodelitem.h>
#include <ireader.h>
#include <iwriter.h>
#include <QMetaProperty>

using namespace Mi;
using namespace Qt;

bool lessThan(const QList<QVariant> &a, const QList<QVariant> &b)
{
    return a.at(0).toReal() < b.at(0).toReal();
}

namespace Ac {
namespace Core {

void GridLineModel::updateList()
{
    _list = IDatabase::instance()->rootItem()->findItem(GridSettingsItem)->findItem(_listType);
    syncDataToList(_list);
}

void GridLineModel::syncDataToList(IModelItem *list)
{
    _valueLists.clear();
    const int row_count = list->itemCount();
    const int column_count = columnCount();
    for (int i = 0;  i < row_count;  ++i) {
        IModelItem *item = list->itemAt(i);
        QList<QVariant> values;
        for (int j = 0;  j < column_count;  ++j)
            values.append(item->getValue(item->roleAt(GridLine::Aggregate::RoleCountOffset + j)));
        _valueLists.append(values);
    }
}

void GridLineModel::syncListToData(IModelItem *list)
{
    const int row_count = _valueLists.count();
    const int column_count = columnCount();
    for (int i = 0;  i < row_count;  ++i) {
        IModelItem *item = 0;
        if (list->itemCount() <= i) {
            QString grid_line_type_string = itemTypeString(_listType);
            grid_line_type_string.chop(4);
            int grid_line_type = itemType(grid_line_type_string);
            item = query<IModelItem>(IDatabaseObjectFactory::instance()->create(grid_line_type));
            list->insertItem(i, item);
        } else
            item = list->itemAt(i);
        for (int j = 0;  j < column_count;  ++j)
            item->set(item->roleAt(GridLine::Aggregate::RoleCountOffset + j), _valueLists.at(i).at(j));
    }

    // Remove the remaining items from the list.
    int item_count = list->itemCount();
    if (row_count < item_count) {
        while (row_count < item_count) {
            list->itemAt(--item_count)->set(VisibilityRole, false);
            list->removeItemAt(item_count);
        }
    }
}

void GridLineModel::setListType(int type)
{
    if (_listType == type)
        return;
    _listType = type;
    updateList();
}

bool GridLineModel::isChanged() const
{
    if (!_list)
        return false;
    const int item_count = _list->itemCount();
    if (item_count != _valueLists.count())
        return true;
    const int column_count = columnCount();
    for (int i = 0;  i < item_count;  ++i) {
        const QList<QVariant> &values = _valueLists.at(i);
        for (int j = 0;  j < column_count;  ++j)
            if (_list->itemAt(i)->getValue(GridLine::Aggregate::RoleCountOffset + j) != values.at(j))
                return true;
    }
    return false;
}

void GridLineModel::resetData()
{
    if (!isChanged())
        return;
    updateList();
    emit layoutChanged();
}

int GridLineModel::columnCount(const QModelIndex &parent) const
{
    return GridLine::Aggregate::RoleCount - GridLine::Aggregate::RoleCountOffset;
}

int GridLineModel::rowCount(const QModelIndex &parent) const
{
    return _valueLists.count();
}

bool GridLineModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QList<QVariant> values;
    values.append(0);
    values.append("");
    values.append(0);
    values.append(lightGray);
    beginInsertRows(parent, 0, 0);
    _valueLists.insert(0, values);
    endInsertRows();
    return true;
}

bool GridLineModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count);
    for (int i = 0;  i < count;  ++i)
        _valueLists.removeAt(row);
    endRemoveRows();
    return true;
}

Qt::ItemFlags GridLineModel::flags(const QModelIndex &index) const
{
    return ItemIsEnabled
            | ItemIsSelectable
            | ItemIsEditable;
}

QVariant GridLineModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (DisplayRole != role
            || Horizontal != orientation
            || section < 0 || columnCount(QModelIndex()) <= section)
        return QVariant();
    QString label(itemDataRoleString(GridLine::Aggregate::RoleCountOffset + section));
    label[0] = label.at(0).toUpper();
    return label;
}

QVariant GridLineModel::data(const QModelIndex &index, int role) const
{
    if ((DisplayRole != role
         && EditRole != role)
            || _list)
        return QVariant();
    return _valueLists.at(index.row()).at(index.column());
}

bool GridLineModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (EditRole != role)
        return false;
   _valueLists[index.row()][index.column()] = value;
    qSort(_valueLists.begin(), _valueLists.end(), lessThan);
    return true;
}

void GridLineModel::importFromFile(const QString &fileName)
{
    IAggregate *list_aggregate = 0;
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    switch (_listType) {
    case TimeGridLineItem:
        list_aggregate = factory->create(TimeGridLineListItem);
        break;
    case Ac::PitchGridLineItem:
        list_aggregate = factory->create(PitchGridLineListItem);
        break;
    case Ac::ControlGridLineItem:
        list_aggregate = factory->create(ControlGridLineListItem);
        break;
    default:
        return;
    }
    IModelItem *list = query<IModelItem>(list_aggregate);
    IAggregate *filer = query<IFilerFactory>(IFilerFactory::instance())->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    query<IReader>(filer)->read(list);
    syncDataToList(list);
    emit layoutChanged();
    delete filer;
    delete list_aggregate;
}

void GridLineModel::exportToFile(const QString &fileName)
{
    IAggregate *list_aggregate = 0;
    IDatabaseObjectFactory *factory = IDatabaseObjectFactory::instance();
    switch (_listType) {
    case TimeGridLineItem:
        list_aggregate = factory->create(TimeGridLineListItem);
        break;
    case Ac::PitchGridLineItem:
        list_aggregate = factory->create(PitchGridLineListItem);
        break;
    case Ac::ControlGridLineItem:
        list_aggregate = factory->create(ControlGridLineListItem);
        break;
    default:
        return;
    }
    IModelItem *list = query<IModelItem>(list_aggregate);
    syncListToData(list);
    IAggregate *filer = query<IFilerFactory>(IFilerFactory::instance())->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    query<IWriter>(filer)->write(list);
    delete filer;
    delete list_aggregate;
}

void GridLineModel::apply()
{
    if (isChanged())
        syncListToData(_list);
}

} // namespace Core
} // namespace Ac
