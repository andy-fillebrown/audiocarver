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

#ifndef AC_GRIDLINEVIEW_H
#define AC_GRIDLINEVIEW_H

#include <QTableView>

class GridLineView : public QTableView
{
    Q_OBJECT

public:
    GridLineView(QWidget *parent = 0);
};

class TimeLineView : public GridLineView
{
    Q_OBJECT

public:
    TimeLineView(QWidget *parent = 0);
};

class PitchLineView : public GridLineView
{
    Q_OBJECT

public:
    PitchLineView(QWidget *parent = 0);
};

class ControlLineView : public GridLineView
{
    Q_OBJECT

public:
    ControlLineView(QWidget *parent = 0);
};

#endif // AC_GRIDLINEVIEW_H
