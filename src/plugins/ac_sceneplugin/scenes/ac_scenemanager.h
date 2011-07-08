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
#include <ac_scene_global.h>

class QFontMetrics;
class QGraphicsScene;

namespace Private {

class AcSceneManagerData;

} // namespace Private

class AC_SCENE_EXPORT AcSceneManager : public QObject
{
    Q_OBJECT

public:
    AcSceneManager(QObject *parent = 0);
    ~AcSceneManager();

    static AcSceneManager *instance();

    QGraphicsScene *scoreScene() const;
    QGraphicsScene *controllerScene() const;
    QGraphicsScene *timeScene() const;
    QGraphicsScene *pitchScene() const;

    const QFontMetrics &fontMetrics() const;

private slots:
    void updateScoreProperty(const QString &propertyName);
    void updateFontSettingsProperty(const QString &propertyName);
    void updateViewSettingsProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcSceneManager)
    Private::AcSceneManagerData *d;
};

#endif // AC_SCENEMANAGER_H
