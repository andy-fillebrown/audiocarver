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

#ifndef AC_SCOREGRAPHICSVIEW_H
#define AC_SCOREGRAPHICSVIEW_H

#include <ac_graphicsview.h>
#include <ac_editor_global.h>

namespace Private {

class AcScoreGraphicsViewData;

} // namespace Private

class AcScoreGraphicsView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcScoreGraphicsView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcScoreGraphicsView();

    const QPointF &center() const;
    void setCenter(const QPointF &center);
    void setCenter(qreal x, qreal y);

public slots:
    void updateScoreProperty(const QString &propertyName);
    void updateCenter();

protected:
    virtual void updateViewSettings(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcScoreGraphicsView)
    Private::AcScoreGraphicsViewData *d;
};

#endif // AC_SCOREGRAPHICSVIEW_H
