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

#include "ac_doubledelegate.h"

#include <mi_doublespinbox.h>

QWidget *DoubleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (customColumn() != index.column())
        return Delegate::createEditor(parent, option, index);
    return new DoubleSpinBox(parent);
}

void DoubleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qreal value = index.data(Qt::EditRole).toReal();
    DoubleSpinBox *spin_box = static_cast<DoubleSpinBox*>(editor);
    spin_box->setValue(value);
}

void DoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    DoubleSpinBox *spin_box = static_cast<DoubleSpinBox*>(editor);
    spin_box->interpretText();
    qreal value = spin_box->value();
    model->setData(index, value);
}

void DoubleDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
