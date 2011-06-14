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

#ifndef AC_GRAPHICSVIEWMANAGER_H
#define AC_GRAPHICSVIEWMANAGER_H

#include <QObject>
#include <ac_editor_global.h>

class AcGraphicsSceneManager;
class AcMainWidget;
class AcPitchGraphicsView;
class AcScoreGraphicsView;
class AcTimeGraphicsView;

namespace Private {

class AcGraphicsViewManagerData;

} // namespace Private

class AcGraphicsViewManager : public QObject
{
    Q_OBJECT

public:
    AcGraphicsViewManager(AcMainWidget *mainWidget);
    ~AcGraphicsViewManager();

    AcPitchGraphicsView *pitchGraphicsView() const;
    AcScoreGraphicsView *scoreGraphicsView() const;
    AcTimeGraphicsView *timeGraphicsView() const;

    AcGraphicsSceneManager *graphicsSceneManager() const;

private slots:
    virtual void updateScoreProperty(const QString &propertyName);
    virtual void updateViewSettingsProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcGraphicsViewManager)
    Private::AcGraphicsViewManagerData *d;
};

#endif // AC_GRAPHICSVIEWMANAGER_H
