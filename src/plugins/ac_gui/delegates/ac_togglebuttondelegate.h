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

#ifndef AC_TOGGLEBUTTONDELEGATE_H
#define AC_TOGGLEBUTTONDELEGATE_H

#include <mi_gui_delegate.h>

class ToggleButtonDelegatePrivate;
class ToggleButtonDelegate : public Mi::Gui::Delegate
{
public:
    ToggleButtonDelegate(QObject *parent = 0);
    ~ToggleButtonDelegate();

    void setButtonColumnWidth(int width);
    virtual void setPainterColors(QPainter *painter, const QModelIndex &index) const;

    // QStyledItemDelegate
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    ToggleButtonDelegatePrivate *d;
};

#endif // AC_TOGGLEBUTTONDELEGATE_H
