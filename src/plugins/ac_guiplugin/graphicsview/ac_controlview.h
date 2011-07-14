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

#ifndef AC_CONTROLVIEW_H
#define AC_CONTROLVIEW_H

#include <ac_editorview.h>

namespace Private {

class AcControlViewData;

} // namespace Private

class AcControlView : public AcEditorView
{
    Q_OBJECT

public:
    AcControlView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcControlView();

    virtual void updateTransform();

protected:
    virtual void updateViewSettings() const;

private:
    Q_DISABLE_COPY(AcControlView)
    Private::AcControlViewData *d;
};

#endif // AC_CONTROLVIEW_H
