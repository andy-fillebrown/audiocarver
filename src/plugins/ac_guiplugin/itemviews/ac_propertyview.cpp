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

#include "ac_propertyview.h"

#include <ac_noteselectionmodel.h>
#include <ac_trackselectionmodel.h>

#include <QComboBox>

static const char * const TRACK_MODELNAME = "Track Properties";
static const char * const NOTE_MODELNAME  = "Note Properties";

class PropertyModelPrivate
{
public:
    PropertyModelPrivate()
    {}
};

class PropertyModel : public QAbstractItemModel
{
public:
    PropertyModel()
    {}

private:
    PropertyModelPrivate *d;
};

class PropertyViewPrivate
{
public:
    PropertyView *q;
    QComboBox *itemTypeComboBox;
    QItemSelectionModel *ssModel;
    QTableView *ssView;

    PropertyViewPrivate(PropertyView *q)
        :   q(q)
        ,   itemTypeComboBox(new QComboBox(q))
        ,   ssModel(TrackSelectionModel::instance())
        ,   ssView(new QTableView(q))
    {
        itemTypeComboBox->addItem(TRACK_MODELNAME);
        itemTypeComboBox->addItem(NOTE_MODELNAME);
    }

    void setSelectionModel(QItemSelectionModel *model)
    {
        if (ssModel == model)
            return;
        ssModel = model;
    }
};

PropertyView::PropertyView(QWidget *parent)
    :   QWidget(parent)
    ,   d(new PropertyViewPrivate(this))
{
    connect(d->itemTypeComboBox, SIGNAL(currentIndexChanged(QString)), SLOT(setSelectionModel(QString)));
}

void PropertyView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    d->itemTypeComboBox->setGeometry(0, 0, width(), d->itemTypeComboBox->height());
    d->ssView->setGeometry(0, d->itemTypeComboBox->height() + 3, width(), height() - (d->itemTypeComboBox->height() + 3));
}

void PropertyView::setSelectionModel(const QString &modelName)
{
    if (TRACK_MODELNAME == modelName)
        d->setSelectionModel(TrackSelectionModel::instance());
    else if (NOTE_MODELNAME == modelName)
        d->setSelectionModel(NoteSelectionModel::instance());
}
