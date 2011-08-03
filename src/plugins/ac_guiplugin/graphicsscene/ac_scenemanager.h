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

#ifndef AC_SCENEMANAGER_H
#define AC_SCENEMANAGER_H

#include <QObject>
#include <ac_scene_util.h>

class AcGraphicsItem;
class QFontMetrics;
class QGraphicsScene;

class AcSceneManagerPrivate;

class AcSceneManager : public QObject
{
    Q_OBJECT

public:
    AcSceneManager(QObject *parent = 0);
    ~AcSceneManager();

    static AcSceneManager *instance();

    QGraphicsScene *scene(SceneType sceneType) const;

    void addItem(AcGraphicsItem *item);

    template <typename T> void addItems(const QList<T*> &items)
    {
        foreach (AcGraphicsItem *item, items)
            addItem(item);
    }

    const QFontMetrics &fontMetrics() const;

private slots:
    void updateScore(int i);
    void updateFontSettings(int i);
    void updateViewSettings(int i);

private:
    Q_DISABLE_COPY(AcSceneManager)
    AcSceneManagerPrivate *d;
};

#endif // AC_SCENEMANAGER_H
