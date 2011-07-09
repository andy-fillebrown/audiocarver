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

#ifndef AC_EDITORVIEW_H
#define AC_EDITORVIEW_H

#include <ac_graphicsview.h>
#include <ac_editor_global.h>

namespace Private {

class AcEditorViewData;

} // namespace Private

class AcEditorView : public AcGraphicsView
{
    Q_OBJECT

public:
    AcEditorView(QGraphicsScene *scene = 0, QWidget *parent = 0);
    ~AcEditorView();

    const QPointF &center() const;
    void setCenter(const QPointF &center);
    void setCenter(qreal x, qreal y);

    void updateCenter();
    virtual void updateTransform() = 0;

protected:
    virtual void updateViewSettings() const = 0;

private:
    Q_DISABLE_COPY(AcEditorView)
    Private::AcEditorViewData *d;
};

#endif // AC_EDITORVIEW_H
