/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2013 Andrew Fillebrown.
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

#ifndef AC_GUI_TOGGLEBUTTONDELEGATE_H
#define AC_GUI_TOGGLEBUTTONDELEGATE_H

#include <mi_gui_delegate.h>

class ToggleButtonDelegatePrivate;
class ToggleButtonDelegate : public Base::Delegate
{
public:
    ToggleButtonDelegate(QObject *parent = 0)
        :   Delegate(parent)
        ,   _buttonColumnWidth(0)
    {}

    void setButtonColumnWidth(int width)
    {
        _buttonColumnWidth = width;
    }

    virtual void setPainterColors(QPainter *painter, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int _buttonColumnWidth;
};

#endif
