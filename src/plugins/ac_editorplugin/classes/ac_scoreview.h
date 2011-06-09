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

#ifndef AC_SCOREVIEW_H
#define AC_SCOREVIEW_H

#include <ac_graphicsview.h>

#include <ac_editor_global.h>

namespace Private {

class AcScoreViewData;

} // namespace Private

class AcScoreView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcScoreView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcScoreView();

    static AcScoreView *instance();

    const QPointF &center() const;
    void setCenter(const QPointF &center);
    void setCenter(qreal x, qreal y);

public slots:
    void updateScoreProperty(const QString &propertyName);
    void updateCenter();

protected:
    virtual void updateViewSettings(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcScoreView)
    Private::AcScoreViewData *d;
};

#endif // AC_SCOREVIEW_H