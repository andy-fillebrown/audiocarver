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

#include <ac_namespace.h>

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

    QGraphicsView *view(Ac::SceneType type) const;

    void setModel(Model *model);

public slots:
    void dataChanged(const QModelIndex &topRight, const QModelIndex &bottomLeft);

signals:
    void scoreDataChanged();

private:
    Q_DISABLE_COPY(ViewManager)
    ViewManagerPrivate *d;
};

#endif // AC_VIEWMANAGER_H
