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

#ifndef AC_GRAPHICSSCENE_H
#define AC_GRAPHICSSCENE_H

#include <mi_graphicsscene.h>
#include <ac_scene_global.h>

class AcScore;
class AcViewSettings;

namespace Private {

class AcGraphicsSceneData;

} // namespace Private

class AC_SCENE_EXPORT AcGraphicsScene : public MiGraphicsScene
{
//    Q_OBJECT

//public:
//    AcGraphicsScene(QObject *parent = 0);
//    virtual ~AcGraphicsScene();

//    AcScore *score() const;
//    const QFont &font() const;
//    const QFontMetrics &fontMetrics() const;

//protected slots:
//    virtual void updateScoreProperty(const QString &propertyName);

//private:
//    Q_DISABLE_COPY(AcGraphicsScene)
//    Private::AcGraphicsSceneData *d;
};

#endif // AC_GRAPHICSSCENE_H
