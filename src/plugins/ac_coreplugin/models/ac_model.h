/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#include <QAbstractItemModel>

class IModelItem;
class Score;

class QGraphicsItem;

class ModelPrivate;
class AC_CORE_EXPORT Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0);
    ~Model();

    Score *score() const;
    QGraphicsItem *sceneItem(int type) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &) const { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QModelIndex index(int row, const QModelIndex &parent = QModelIndex()) const
    {
        return index(row, 0, parent);
    }

    bool insertItem(IModelItem *item, int row, const QModelIndex &parent);
    IModelItem *takeItem(int row, const QModelIndex &parent);

    QModelIndex scoreIndex() const { return index(0); }
    QModelIndex trackListIndex() const;
    QModelIndex timeGridLineListIndex() const;
    QModelIndex pitchGridLineListIndex() const;
    QModelIndex controlGridLineListIndex() const;
    QModelIndex viewSettingsIndex() const;

signals:
    void dataAboutToBeChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    Q_DISABLE_COPY(Model)
    ModelPrivate *d;

    friend class ObjectPrivate;
    friend class ModelPrivate;
};

class ModelPrivate
{
public:
    Model *q;
    Score *score;
    bool layoutAboutToBeChangedEmitted;

    ModelPrivate(Model *q)
        :   q(q)
        ,   score(0)
        ,   layoutAboutToBeChangedEmitted(false)
    {}

    void init();
    ~ModelPrivate();

    QModelIndex indexFromItem(IModelItem *item) const;
    IModelItem *itemFromIndex(const QModelIndex &index) const;

    void maybeEmitLayoutAboutToBeChanged()
    {
        if (layoutAboutToBeChangedEmitted)
            return;
        layoutAboutToBeChangedEmitted = true;
        emit q->layoutAboutToBeChanged();
    }

    void maybeEmitLayoutChanged()
    {
        if (!layoutAboutToBeChangedEmitted)
            return;
        layoutAboutToBeChangedEmitted = false;
        emit q->layoutChanged();
    }
};

#endif // AC_MODEL_H
