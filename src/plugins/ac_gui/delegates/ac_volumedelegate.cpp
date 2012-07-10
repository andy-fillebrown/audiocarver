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

#include "ac_volumedelegate.h"

#include <QDoubleSpinBox>

QWidget *VolumeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget *editor = DoubleDelegate::createEditor(parent, option, index);
    QDoubleSpinBox *spin_box = qobject_cast<QDoubleSpinBox*>(editor);
    if (spin_box) {
        spin_box->setDecimals(6);
        spin_box->setRange(0.0f, 1.0f);
        spin_box->setSingleStep(0.05f);
    }
    return editor;
}
