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
#include <QFileDialog>

class GridLineDialogPrivate
{
public:
    GridLineDialog *q;
    Ui_GridLineDialog *ui;

    GridLineDialogPrivate(GridLineDialog *q)
        :   q(q)
        ,   ui(new Ui_GridLineDialog)
    {
        ui->setupUi(q);
    }

    ~GridLineDialogPrivate()
    {
        delete ui;
    }

    GridLineModel *currentModel() const
    {
        return qobject_cast<GridLineModel*>(currentView()->model());
    }

    GridLineView *currentView() const
    {
        return ui->tabWidget->currentWidget()->findChild<GridLineView*>();
    }
};

GridLineDialog::GridLineDialog(QWidget *parent)
    :   QDialog(parent)
    ,   d(new GridLineDialogPrivate(this))
{
    connect(d->ui->addRowButton, SIGNAL(clicked()), SLOT(addRow()));
    connect(d->ui->removeRowButton, SIGNAL(clicked()), SLOT(removeRow()));
    connect(d->ui->resetButton, SIGNAL(clicked()), SLOT(reset()));
    connect(d->ui->importButton, SIGNAL(clicked()), SLOT(importFromFile()));
    connect(d->ui->exportButton, SIGNAL(clicked()), SLOT(exportToFile()));
    connect(d->ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(apply()));
    connect(d->ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(close()));
    connect(d->ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(apply()));
    connect(d->ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(close()));
}

GridLineDialog::~GridLineDialog()
{
    delete d;
}

void GridLineDialog::addRow()
{
    d->currentView()->model()->insertRows(0, 1);
}

void GridLineDialog::removeRow()
{
    GridLineView *view = d->currentView();
    const QModelIndexList selected_row_indexes = view->selectionModel()->selectedRows();
    QList<int> selected_rows;
    foreach (const QModelIndex &index, selected_row_indexes)
        selected_rows.append(index.row());
    qSort(selected_rows);
    const int n = selected_rows.count();
    for (int i = n - 1;  0 <= i;  --i)
        view->model()->removeRow(selected_rows.at(i));
}

void GridLineDialog::reset()
{
    d->currentModel()->resetData();
}

void GridLineDialog::importFromFile()
{
}

void GridLineDialog::exportToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Grid", "", "Grid (*.aci-grid)");
    if (fileName.isEmpty())
        return;
    if (!fileName.endsWith("aci-grid"))
        fileName.append(".aci-grid");
    d->currentModel()->exportToFile(fileName);
}

void GridLineDialog::apply()
{
    GridLineModel *timeLinesModel = qobject_cast<GridLineModel*>(d->ui->timeLinesView->model());
    GridLineModel *pitchLinesModel = qobject_cast<GridLineModel*>(d->ui->pitchLinesView->model());
    GridLineModel *controlLinesModel = qobject_cast<GridLineModel*>(d->ui->controlLinesView->model());

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
