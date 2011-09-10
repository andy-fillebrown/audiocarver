/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
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

#ifndef AC_MAINWIDGET_H
#define AC_MAINWIDGET_H

#include <QWidget>

class AcMainWidgetPrivate;
class AbstractItemModel;

class AcMainWidget : public QWidget
{
    Q_OBJECT

public:
    AcMainWidget(QWidget *parent = 0);
    ~AcMainWidget();

    void setModel(AbstractItemModel *model);
    void viewAll();

    bool isPointInVolumeViews(QWidget *widget, const QPoint &pos) const;

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Q_DISABLE_COPY(AcMainWidget)
    AcMainWidgetPrivate *d;
};

#endif // AC_MAINWIDGET_H
