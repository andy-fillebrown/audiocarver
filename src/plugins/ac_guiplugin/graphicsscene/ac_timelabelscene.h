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

#ifndef AC_TIMELABELSCENE_H
#define AC_TIMELABELSCENE_H

#include <ac_labelscene.h>

class AcTimeLabelScenePrivate;

class AcTimeLabelScene : public AcLabelScene
{
    Q_OBJECT

public:
    AcTimeLabelScene(QObject *parent = 0);
    virtual ~AcTimeLabelScene();

    static AcTimeLabelScene *instance();

protected:
    void updateViewSettings(int i, const QVariant &value);

protected slots:
    void updateScore(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcTimeLabelScene)
    AcTimeLabelScenePrivate *d;
};

#endif // AC_TIMELABELSCENE_H
