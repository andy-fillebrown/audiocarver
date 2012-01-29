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

#include "ac_gridlinedialog.h"

#include <ui_ac_gridlinedialog.h>

class GridLineDialogPrivate
{
public:
    GridLineDialogPrivate()
    {}
};

GridLineDialog::GridLineDialog(QWidget *parent)
    :   QDialog(parent)
    ,   d(new GridLineDialogPrivate)
    ,   ui(new Ui_GridLineDialog)
{
    ui->setupUi(this);
    connect(ui->addRowButton, SIGNAL(clicked()), SLOT(addRow()));
}

GridLineDialog::~GridLineDialog()
{
    delete ui;
    delete d;
}

void GridLineDialog::addRow()
{
    GridLineView *view = ui->tabWidget->currentWidget()->findChild<GridLineView*>();
    view->model()->insertRows(0, 1);
}
