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

#ifndef AC_BARLINEITEM_H
#define AC_BARLINEITEM_H

#include <ac_guidelineitem.h>

class AcBarline;

class AC_SCENE_EXPORT AcBarlineItem : public AcGuidelineItem
{
public:
    AcBarlineItem(AcBarline *barline = 0);
    virtual ~AcBarlineItem();

private:
    Q_DISABLE_COPY(AcBarlineItem)
};

#endif // AC_BARLINEITEM_H
