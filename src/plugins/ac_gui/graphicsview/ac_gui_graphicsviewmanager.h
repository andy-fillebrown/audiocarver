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

#ifndef AC_GUI_GRAPHICSVIEWMANAGER_H
#define AC_GUI_GRAPHICSVIEWMANAGER_H

#include <QObject>

class IGraphicsItem;
class IModelItem;
class QGraphicsView;
class QModelIndex;
class QPointF;
class QWidget;

class GraphicsViewManagerPrivate;
class GraphicsViewManager : public QObject
{
    Q_OBJECT

    friend class GraphicsViewManagerPrivate;
    GraphicsViewManagerPrivate *d;

public:
    static GraphicsViewManager *instance();

    GraphicsViewManager(QWidget *widget);
    ~GraphicsViewManager();

    QGraphicsView *view(int type) const;
    qreal scoreLength() const;
    qreal position(int role) const;
    void setPosition(int role, qreal position);
    qreal scale(int role) const;
    void setScale(int role, qreal scale);
    void updateDatabase();
    void clearPickedGrips();
    QPointF snappedScenePos(int sceneType, const QPointF &pos) const;
    void updateSelection(const QList<IGraphicsItem*> &ss);

public slots:
    void updateViews();
    void databaseAboutToBeRead();
    void databaseRead();
    void databaseAboutToBeWritten();
    void disableUpdates();
    void enableUpdates();
    void dataChanged(IModelItem *item);
    void modelReset();
    void startInsertingPoints();
    void finishInsertingPoints();
    void cancelPointInsertion();

signals:
    void scoreLengthChanged();
    void viewPositionChanged(int role);
    void viewScaleChanged(int role);
};

#endif
