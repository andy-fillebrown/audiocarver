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

#ifndef AC_GRIDLINEDIALOG_H
#define AC_GRIDLINEDIALOG_H

#include <QDialog>

class Ui_GridLineDialog;

class GridLineDialogPrivate;
class GridLineDialog : public QDialog
{
    Q_OBJECT

public:
    GridLineDialog(QWidget *parent = 0);
    ~GridLineDialog();

public slots:
    void apply();
    void addRow();

private:
    friend class GridLineDialogPrivate;
    GridLineDialogPrivate *d;
    Ui_GridLineDialog *ui;
};

#endif // AC_GRIDLINEDIALOG_H
