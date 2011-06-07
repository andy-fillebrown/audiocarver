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

#ifndef AC_SCORESCENE_H
#define AC_SCORESCENE_H

#include <ac_graphicsscene.h>

#include <ac_scene_global.h>

namespace Private {

class AcScoreSceneData;

} // namespace Private

class AC_SCENE_EXPORT AcScoreScene : public AcGraphicsScene
{
    Q_OBJECT

public:
    AcScoreScene(QObject *parent = 0);
    virtual ~AcScoreScene();

protected:
    virtual void updateScoreProperty(const QString &propertyName);

private slots:
    void updateTunings();
    void updateTuningProperties();
    void updateBarlines();
    void updateBarlineProperties();

private:
    Q_DISABLE_COPY(AcScoreScene)
    Private::AcScoreSceneData *d;
};

#endif // AC_SCORESCENE_H
