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

#ifndef AC_MODEL_H
#define AC_MODEL_H

#include <ac_global.h>
#include <ac_namespace.h>

#include <mi_imodel.h>

class IModelItem;
class Score;

class QGraphicsItem;

class ModelPrivate;
class AC_CORE_EXPORT Model : public IModel
{
    Q_OBJECT

public:
    Model();
    ~Model();

    QGraphicsItem *sceneItem(int type) const;

    // IModel
    IModelItem *rootItem() const;
    QModelIndex itemIndex(int type) const;
    QModelIndex listIndex(int type) const;

    QModelIndexList findIndexes(int type, int role, const QVariant &value) const;

public slots:
    void rowCountChanged(const QModelIndex &parent);
    void clearTrackCount();

private:
    ModelPrivate *d;
};

#endif // AC_MODEL_H
