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

#ifndef AC_LABELVIEW_H
#define AC_LABELVIEW_H

#include <ac_graphicsview.h>

class QModelIndex;

class LabelViewPrivate;
class LabelView : public GraphicsView
{
    Q_OBJECT

public:
    LabelView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~LabelView();

    // GraphicsView
    void updateView();
    void viewScaleChanged(int role);
    void scoreLengthChanged();

    void dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft);

protected:
    virtual qreal paddingScale() const = 0;
    virtual QModelIndex gridLineListIndex() const = 0;
    virtual int scaleRole() const = 0;

    QPointF sceneOffset() const { return QPointF(0.0f, qreal(10.0f) / (qreal(height()) / sceneHeight())); }

    void panFinished();
    void zoomFinished();

    void updateViewSettings();
    void paintGlyphs(QPaintEvent *event) { Q_UNUSED(event); }

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    LabelViewPrivate *d;
    friend class LabelViewPrivate;
};

class LabelVView : public LabelView
{
    Q_OBJECT

public:
    LabelVView(QGraphicsScene *scene = 0, QWidget *parent = 0)
        :   LabelView(scene, parent)
    {}

protected:
    qreal paddingScale() const { return -sceneTransform().m22(); }
    int scaleRole() const { return scaleRoleY(); }

    QPointF sceneOffset() const { return QPointF(qreal(-2.0f) / (qreal(width()) / sceneWidth()), qreal(10.0f) / (qreal(height()) / sceneHeight())); }
    QPointF sceneCenter() const;

    void zoomStarting();
};

#endif // AC_LABELVIEW_H
