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

#include <ac_editor_global.h>

namespace Private {

class AcMainWidgetData;

} // namespace Private

class AcMainWidget : public QWidget
{
    Q_OBJECT

public:
    AcMainWidget(QWidget *parent = 0);
    ~AcMainWidget();

    static AcMainWidget *instance();

    qreal positionX() const;
    void setPositionX(qreal positionX);
    qreal positionY() const;
    void setPositionY(qreal positionY);

    qreal scaleX() const;
    void setScaleX(qreal scaleX);
    qreal scaleY() const;
    void setScaleY(qreal scaleY);

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Q_DISABLE_COPY(AcMainWidget)
    Private::AcMainWidgetData *d;
};

#endif // AC_MAINWIDGET_H