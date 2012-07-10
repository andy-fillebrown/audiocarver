/******************************************************************************
**
**   Copyright 2008, 2009 by Andrew Fillebrown. All rights reserved.
**   andy.fillebrown@gmail.com
**
**   This file is part of the MiQt project.
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 3 of the License, or
**   (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
**
**   Contact andy.fillebrown@gmail.com if any conditions of this licensing are
**   not clear to you.
**
******************************************************************************/

#ifndef AC_MIDIFILEIMPORTDIALOG_H
#define AC_MIDIFILEIMPORTDIALOG_H

#include <ac_midifileglobal.h>

#include <QDialog>

class Ui_MidiFileImportDialog;

class MidiFileImportDialogPrivate;
class AC_MIDIFILE_EXPORT MidiFileImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MidiFileImportDialog(QWidget *parent = 0);
    virtual ~MidiFileImportDialog();

private slots:
    void openFile();
    void import();

private:
    MidiFileImportDialogPrivate *d;
    Ui_MidiFileImportDialog *ui;

    friend class MidiFileImportDialogPrivate;
};

#endif // AC_MIDIFILEIMPORTDIALOG_H
