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

#ifndef MI_DOUBLESPINBOX_H
#define MI_DOUBLESPINBOX_H

#include <mi_global.h>

#include <QDoubleSpinBox>

class MI_GUI_EXPORT DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    DoubleSpinBox(QWidget *parent = 0)
        :   QDoubleSpinBox(parent)
    {
        setDecimals(12);
        setMaximum(Q_FLOAT_MAX);
    }

    QString textFromValue(double val) const
    {
        QString text = QString("%1").arg(val, 0, 'f', 12);
        while (text.endsWith('0'))
            text.chop(1);
        if (text.endsWith('.'))
            text.chop(1);
        return text;
    }
};

#endif // MI_DOUBLESPINBOX_H
