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

#include <ac_gridline.h>
#include <ac_ifactory.h>
#include <ac_ifiler.h>

#include <mi_imodel.h>
#include <mi_imodelitem.h>
#include <mi_objectlist.h>

#include <QMetaProperty>

bool lessThan(const QList<QVariant> &a, const QList<QVariant> &b)
{
    return a.at(0).toReal() < b.at(0).toReal();
}

class GridLineModelPrivate
{
public:
    GridLineModel *q;
    int gridLineType;
    IModelItem *listItem;
    QList<QList<QVariant> > data;

    GridLineModelPrivate(GridLineModel *q)
        :   q(q)
        ,   gridLineType(0)
        ,   listItem(0)
    {}

    void updateListItem()
    {
        listItem = IModel::instance()->rootItem()->findModelItem(Ac::GridSettingsItem)->findModelItemList(gridLineType);
        Q_ASSERT(listItem);
        syncDataToList(listItem);
    }

    void syncDataToList(IModelItem *listItem)
    {
        data.clear();
        const int row_count = listItem->modelItemCount();
        const int column_count = q->columnCount();
        const int property_offset = GridLine::staticMetaObject.propertyOffset();
        for (int i = 0;  i < row_count;  ++i) {
            IModelItem *item = listItem->modelItemAt(i);
            QList<QVariant> item_data;
            for (int j = 0;  j < column_count;  ++j)
                item_data.append(item->data(item->persistentRoleAt(j + property_offset)));
            data.append(item_data);
        }
    }

    void syncListToData(IModelItem *listItem)
    {
        const int row_count = data.count();
        const int column_count = q->columnCount();
        const int property_offset = GridLine::staticMetaObject.propertyOffset();
        for (int i = 0;  i < row_count;  ++i) {
            IModelItem *item = 0;
            if (listItem->modelItemCount() <= i) {
                item = IObjectFactory::instance()->create(gridLineType);
                item->setParentModelItem(listItem);
            } else
                item = listItem->modelItemAt(i);
            for (int j = 0;  j < column_count;  ++j)
                item->setData(data.at(i).at(j), item->persistentRoleAt(property_offset + j));
        }

        // Remove the remaining items from the list.
        int item_count = listItem->modelItemCount();
        if (row_count < item_count) {
            IModel *model = IModel::instance();
            const QModelIndex list_index = model->indexFromItem(listItem);
            while (row_count < item_count) {
                listItem->modelItemAt(--item_count)->setData(false, Ac::VisibilityRole);
                model->removeItem(item_count, list_index);
            }
        }
    }
};

GridLineModel::GridLineModel(QObject *parent)
    :   QAbstractTableModel(parent)
    ,   d(new GridLineModelPrivate(this))
{}

GridLineModel::~GridLineModel()
{
    delete d;
}

void GridLineModel::setGridLineType(int type)
{
    if (d->gridLineType == type)
        return;
    d->gridLineType = type;
    d->updateListItem();
}

bool GridLineModel::isChanged() const
{
    if (!d->listItem)
        return false;
    const int item_count = d->listItem->modelItemCount();
    if (item_count != d->data.count())
        return true;
    const int property_offset = GridLine::staticMetaObject.propertyOffset();
    const int column_count = columnCount();
    for (int i = 0;  i < item_count;  ++i) {
        const IModelItem *item = d->listItem->modelItemAt(i);
        const QList<QVariant> &data = d->data.at(i);
        for (int j = 0;  j < column_count;  ++j)
            if (item->data(item->persistentRoleAt(property_offset + j)) != data.at(j))
                return true;
    }
    return false;
}

void GridLineModel::resetData()
{
    if (!isChanged())
        return;
    d->updateListItem();
    emit layoutChanged();
}

int GridLineModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    const QMetaObject *mo = &GridLine::staticMetaObject;
    return mo->propertyCount() - mo->propertyOffset();
}

int GridLineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->data.count();
}

bool GridLineModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(count);
    Q_UNUSED(parent);
    QList<QVariant> item_data;
    item_data.append(0);
    item_data.append("");
    item_data.append(0);
    item_data.append(QColor(Qt::lightGray));
    beginInsertRows(parent, 0, 0);
    d->data.insert(0, item_data);
    endInsertRows();
    return true;
}

bool GridLineModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count);
    for (int i = 0;  i < count;  ++i)
        d->data.removeAt(row);
    endRemoveRows();
    return true;
}

Qt::ItemFlags GridLineModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled
            | Qt::ItemIsSelectable
            | Qt::ItemIsEditable;
}

QVariant GridLineModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole != role
            || Qt::Horizontal != orientation
            || section < 0 || columnCount(QModelIndex()) <= section)
        return QVariant();
    const QMetaObject *mo = &GridLine::staticMetaObject;
    QString label(mo->property(mo->propertyOffset() + section).name());
    label[0] = label.at(0).toUpper();
    return label;
}

QVariant GridLineModel::data(const QModelIndex &index, int role) const
{
    if ((Qt::DisplayRole != role
         && Qt::EditRole != role)
            || !d->listItem)
        return QVariant();
    return d->data.at(index.row()).at(index.column());
}

bool GridLineModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (Qt::EditRole != role)
        return false;
    d->data[index.row()][index.column()] = value;
    qSort(d->data.begin(), d->data.end(), lessThan);
    return true;
}

void GridLineModel::importFromFile(const QString &fileName)
{
    ObjectList *list = 0;
    switch (d->gridLineType) {
    case Ac::TimeGridLineItem:
        list = new ObjectTList<TimeGridLine>();
        break;
    case Ac::PitchGridLineItem:
        list = new ObjectTList<PitchGridLine>();
        break;
    case Ac::ControlGridLineItem:
        list = new ObjectTList<ControlGridLine>();
        break;
    default:
        return;
    }
    IModelItem *list_item = objectToInterface_cast<IModelItem>(list);

    IReader *reader = IFilerFactory::instance()->createReader(Ac::XmlFileFiler);
    IFileFiler *filer = query<IFileFiler>(reader);
    filer->setFileName(fileName);
    reader->read(list_item);

    d->syncDataToList(list_item);
    emit layoutChanged();

    delete reader;
    delete list_item;
}

void GridLineModel::exportToFile(const QString &fileName)
{
    ObjectList *list = 0;
    switch (d->gridLineType) {
    case Ac::TimeGridLineItem:
        list = new ObjectTList<TimeGridLine>();
        break;
    case Ac::PitchGridLineItem:
        list = new ObjectTList<PitchGridLine>();
        break;
    case Ac::ControlGridLineItem:
        list = new ObjectTList<ControlGridLine>();
        break;
    default:
        return;
    }
    IModelItem *list_item = objectToInterface_cast<IModelItem>(list);
    d->syncListToData(list_item);

    IWriter *writer = IFilerFactory::instance()->createWriter(Ac::XmlFileFiler);
    IFileFiler *filer = query<IFileFiler>(writer);
    filer->setFileName(fileName);
    writer->write(list_item);

    delete writer;
    delete list;
}

void GridLineModel::apply()
{
    if (!isChanged())
        return;
    d->syncListToData(d->listItem);
}
