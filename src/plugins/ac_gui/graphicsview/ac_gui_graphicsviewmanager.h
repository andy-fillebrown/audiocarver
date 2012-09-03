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

#ifndef AC_GUI_GRAPHICSVIEWMANAGER_H
#define AC_GUI_GRAPHICSVIEWMANAGER_H

#include <QObject>

class IModelData;
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
    GraphicsViewManager(QWidget *widget);
    ~GraphicsViewManager();

    static GraphicsViewManager *instance();

    QGraphicsView *view(int type) const;
    qreal scoreLength() const;
    qreal position(int role) const;
    void setPosition(qreal position, int role);
    qreal scale(int role) const;
    void setScale(qreal scale, int role);
    void updateDatabase();
    void clearPickedGrips();
    QPointF snappedScenePos(const QPointF &pos, int sceneType) const;

public slots:
    void updateViews();
    void databaseAboutToBeRead();
    void databaseRead();
    void databaseAboutToBeWritten();
    void disableUpdates();
    void enableUpdates();
    void dataChanged(const IModelData *data);
    void modelReset();
    void startInsertingPoints();
    void finishInsertingPoints();
    void cancelPointInsertion();
    void selectAllGrips();
    void startGripDrag();

signals:
    void scoreLengthChanged();
    void viewPositionChanged(int role);
    void viewScaleChanged(int role);
};

#endif