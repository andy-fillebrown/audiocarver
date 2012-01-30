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

#include <ac_gridlinemodel.h>

#include <mi_ieditor.h>

#include <QDialogButtonBox>

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
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(close()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(apply()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(apply()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(close()));
    connect(ui->addRowButton, SIGNAL(clicked()), SLOT(addRow()));
}

GridLineDialog::~GridLineDialog()
{
    delete ui;
    delete d;
}

void GridLineDialog::apply()
{
    GridLineModel *timeLinesModel = qobject_cast<GridLineModel*>(ui->timeLinesView->model());
    GridLineModel *pitchLinesModel = qobject_cast<GridLineModel*>(ui->pitchLinesView->model());
    GridLineModel *controlLinesModel = qobject_cast<GridLineModel*>(ui->controlLinesView->model());

    if (!timeLinesModel->isChanged()
            && !pitchLinesModel->isChanged()
            && !controlLinesModel->isChanged())
        return;

    IEditor *editor = IEditor::instance();
    editor->beginCommand();
    timeLinesModel->apply();
    pitchLinesModel->apply();
    controlLinesModel->apply();
    editor->endCommand();
}

void GridLineDialog::addRow()
{
    GridLineView *view = ui->tabWidget->currentWidget()->findChild<GridLineView*>();
    view->model()->insertRows(0, 1);
}
