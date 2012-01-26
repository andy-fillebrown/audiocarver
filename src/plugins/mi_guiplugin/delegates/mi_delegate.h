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

#ifndef MI_DELEGATE_H
#define MI_DELEGATE_H

#include <mi_global.h>

#include <QStyledItemDelegate>

class DelegatePrivate;
class MI_GUI_EXPORT Delegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    Delegate(QObject *parent = 0);
    ~Delegate();

    int customColumn() const;
    void setCustomColumn(int column);

    // QStyledItemDelegate
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize();
    }

private:
    DelegatePrivate *d;
};

#endif // MI_DELEGATE_H
