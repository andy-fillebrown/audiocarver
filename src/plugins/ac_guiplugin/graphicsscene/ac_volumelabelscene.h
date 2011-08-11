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

#ifndef AC_VOLUMELABELSCENE_H
#define AC_VOLUMELABELSCENE_H

#include <ac_labelscene.h>

class AcVolumeLabelScenePrivate;

class AcVolumeLabelScene : public AcLabelScene
{
    Q_OBJECT

public:
    AcVolumeLabelScene(QObject *parent = 0);
    ~AcVolumeLabelScene();

    static AcVolumeLabelScene *instance();

//protected:
//    void updateViewSettings(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcVolumeLabelScene)
    AcVolumeLabelScenePrivate *d;
};

#endif // AC_VOLUMELABELSCENE_H
