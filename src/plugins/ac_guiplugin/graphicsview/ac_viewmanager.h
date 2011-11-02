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

#ifndef AC_VIEWMANAGER_H
#define AC_VIEWMANAGER_H

#include <QObject>

class Model;

class QGraphicsView;
class QWidget;

class QModelIndex;

class ViewManagerPrivate;
class ViewManager : public QObject
{
    Q_OBJECT

public:
    ViewManager(QWidget *widget);
    ~ViewManager();

    static ViewManager *instance();

    QGraphicsView *view(int type) const;

    qreal scoreLength() const;
    qreal position(int role) const;
    void setPosition(qreal position, int role);
    qreal scale(int role) const;
    void setScale(qreal scale, int role);

    void updateDatabase();
    void updateViews();

public slots:
    void databaseAboutToBeRead();
    void databaseRead();
    void databaseAboutToBeWritten();

    void disableUpdates();
    void enableUpdates();

    void dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft);
    void modelReset();

signals:
    void scoreLengthChanged();
    void viewPositionChanged(int role);
    void viewScaleChanged(int role);

private:
    Q_DISABLE_COPY(ViewManager)
    ViewManagerPrivate *d;
    friend class ViewManagerPrivate;
};

#endif // AC_VIEWMANAGER_H
