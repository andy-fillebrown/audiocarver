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

#include "ac_gridlinemodel.h"

#include <mi_idatabase.h>
#include <mi_idataobjectfactory.h>
#include <mi_ifiler.h>
#include <mi_ifilerfactory.h>
#include <mi_imodel.h>
#include <mi_imodellist.h>

#include <ac_core_gridline.h>

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
    _list = query<IModel>(IDatabase::instance())->rootItem()->findItem(GridSettingsItem)->findList(_gridLineType);
    syncDataToList(_list);
}

void GridLineModel::syncDataToList(IModelList *list)
{
    _valueLists.clear();
    const int row_count = list->count();
    const int column_count = columnCount();
    for (int i = 0;  i < row_count;  ++i) {
        IModelItem *item = list->at(i);
        const IModelData *data = query<IModelData>(item);
        QList<QVariant> values;
        for (int j = 0;  j < column_count;  ++j)
            values.append(data->getVariant(data->roleAt(GridLine::RoleCountOffset + j)));
        _valueLists.append(values);
    }
}

void GridLineModel::syncListToData(IModelList *list)
{
    const int row_count = _valueLists.count();
    const int column_count = columnCount();
    for (int i = 0;  i < row_count;  ++i) {
        IModelItem *item = 0;
        if (list->count() <= i) {
            item = query<IModelItem>(query<IDataObjectFactory>(IDatabase::instance())->create(_gridLineType));
            list->insert(i, item);
        } else
            item = list->at(i);
        IModelData *data = query<IModelData>(item);
        for (int j = 0;  j < column_count;  ++j)
            data->set(_valueLists.at(i).at(j), data->roleAt(GridLine::RoleCountOffset + j));
    }

    // Remove the remaining items from the list.
    int item_count = list->count();
    if (row_count < item_count) {
        while (row_count < item_count) {
            query<IModelData>(list->at(--item_count))->set(false, VisibilityRole);
            list->removeAt(item_count);
        }
    }
}

void GridLineModel::setGridLineType(int type)
{
    if (_gridLineType == type)
        return;
    _gridLineType = type;
    updateList();
}

bool GridLineModel::isChanged() const
{
    if (!_list)
        return false;
    const int item_count = _list->count();
    if (item_count != _valueLists.count())
        return true;
    const int column_count = columnCount();
    for (int i = 0;  i < item_count;  ++i) {
        IModelData *data = query<IModelData>(_list->at(i));
        const QList<QVariant> &values = _valueLists.at(i);
        for (int j = 0;  j < column_count;  ++j)
            if (data->getVariant(GridLine::RoleCountOffset + j) != values.at(j))
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
    return GridLine::RoleCount - GridLine::RoleCountOffset;
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
    QString label(itemDataRoleString(GridLine::RoleCountOffset + section));
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
    IAggregator *list_a = 0;
    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
    switch (_gridLineType) {
    case TimeGridLineItem:
        list_a = factory->create(TimeGridLineListItem);
        break;
    case Ac::PitchGridLineItem:
        list_a = factory->create(PitchGridLineListItem);
        break;
    case Ac::ControlGridLineItem:
        list_a = factory->create(ControlGridLineListItem);
        break;
    default:
        return;
    }
    IModelList *list = query<IModelList>(list_a);
    IAggregator *filer = query<IFilerFactory>(IDatabase::instance())->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    query<IReader>(filer)->read(list);
    syncDataToList(list);
    emit layoutChanged();
    delete filer;
    delete list_a;
}

void GridLineModel::exportToFile(const QString &fileName)
{
    IAggregator *list_a = 0;
    IDataObjectFactory *factory = query<IDataObjectFactory>(IDatabase::instance());
    switch (_gridLineType) {
    case TimeGridLineItem:
        list_a = factory->create(TimeGridLineListItem);
        break;
    case Ac::PitchGridLineItem:
        list_a = factory->create(PitchGridLineListItem);
        break;
    case Ac::ControlGridLineItem:
        list_a = factory->create(ControlGridLineListItem);
        break;
    default:
        return;
    }
    IModelList *list = query<IModelList>(list_a);
    syncListToData(list);
    IAggregator *filer = query<IFilerFactory>(IDatabase::instance())->create(FileFiler);
    query<IFileFiler>(filer)->setFileName(fileName);
    query<IWriter>(filer)->write(list);
    delete filer;
    delete list_a;
}

void GridLineModel::apply()
{
    if (isChanged())
        syncListToData(_list);
}

} // namespace Core
} // namespace Ac
