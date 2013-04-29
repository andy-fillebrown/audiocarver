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

#ifndef AC_GRIPSELECTIONMODEL_H
#define AC_GRIPSELECTIONMODEL_H

#include <QAbstractTableModel>

namespace Object {
class GraphicsGrip;
}

class IGraphicsGrip;

class GripSelectionModelPrivate;
class GripSelectionModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    static GripSelectionModel *instance();

    GripSelectionModel(QObject *parent = 0);
    ~GripSelectionModel();

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

signals:
    void gripDeselected(IGraphicsGrip *grip);
    void gripsSelected();
    void gripsDeselected();

private slots:
    void delayedUpdate();

private:
    friend class Object::GraphicsGrip;
    void appendGrip(IGraphicsGrip *grip);
    void removeGrip(IGraphicsGrip *grip);
    void update();

    GripSelectionModelPrivate *d;
};

#endif
