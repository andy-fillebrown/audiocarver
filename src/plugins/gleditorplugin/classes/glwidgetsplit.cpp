/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "glwidgetsplit.h"

#include "glviewport.h"
#include "glwidget.h"

#include <QtCore/QSize>

using namespace GLEditor;
using namespace GLEditor::Internal;

namespace GLEditor {
namespace Internal {

enum SplitOrientation
{
    NotSplit,
    HorizontalSplit,
    VerticalSplit
};

class GLWidgetSplitPrivate
{
public:
    GLWidgetSplit *q;
    GLWidget *widget;
    GLWidgetSplit *parentSplit;
    GLWidgetSplit::SplitType splitType;
    SplitOrientation splitOrientation;
    int splitLocation;
    GLViewport *viewport;
    GLWidgetSplit *splitOne;
    GLWidgetSplit *splitTwo;

    GLWidgetSplitPrivate(GLWidgetSplit *q, GLWidget *widget)
        :   q(q)
        ,   widget(widget)
        ,   parentSplit(0)
        ,   splitType(GLWidgetSplit::ParentSplit)
    {
        finishConstruction();
    }

    GLWidgetSplitPrivate(GLWidgetSplit *q, GLWidgetSplit *parentSplit, GLWidgetSplit::SplitType splitType)
        :   q(q)
        ,   widget(parentSplit->widget())
        ,   parentSplit(parentSplit)
        ,   splitType(splitType)
    {
        finishConstruction();
    }

    void finishConstruction()
    {
        splitOrientation = NotSplit;
        splitLocation = 0;
        viewport = 0;
        splitOne = 0;
        splitTwo = 0;
    }

    ~GLWidgetSplitPrivate()
    {
        delete splitTwo;  splitTwo = 0;
        delete splitOne;  splitOne = 0;
        delete viewport;  viewport = 0;
        splitLocation = 0;
        splitOrientation = NotSplit;
        splitType = GLWidgetSplit::ParentSplit;
        parentSplit = 0;
        widget = 0;
        q = 0;
    }

    void createViewport()
    {
        if (viewport)
            return;
        viewport = new GLViewport(widget, q->size());
    }
};

} // namespace Internal
} // namespace Editor3D

GLWidgetSplit::GLWidgetSplit(GLWidget *widget)
    :   d(new GLWidgetSplitPrivate(this, widget))
{
    Q_CHECK_PTR(d);
}

GLWidgetSplit::GLWidgetSplit(GLWidgetSplit *parentSplit, SplitType splitType)
    :   d(new GLWidgetSplitPrivate(this, parentSplit, splitType))
{
    Q_CHECK_PTR(d);
}

GLWidgetSplit::~GLWidgetSplit()
{
    delete d;  d = 0;
}

GLWidget *GLWidgetSplit::widget() const
{
    return d->widget;
}

GLWidgetSplit *GLWidgetSplit::parentSplit() const
{
    return d->parentSplit;
}

QPoint GLWidgetSplit::pos() const
{
    GLWidgetSplit *p = parentSplit();

    if (d->splitType == ParentSplit || d->splitType == FirstSplit) {
        if (p)
            return p->pos();
        return QPoint(0, 0);
    }
    QPoint parentPos = p->pos();
    if (isSplitHorizontal())
        return QPoint(parentPos.x(), parentPos.y() + p->splitLocation());
    return QPoint(parentPos.x() + p->splitLocation(), parentPos.y());
}

QRect GLWidgetSplit::rect() const
{
    return QRect(pos(), size());
}

QSize GLWidgetSplit::size() const
{
    GLWidgetSplit *p = parentSplit();
    if (!p)
        return widget()->size();
    if (d->splitType == ParentSplit)
        return p->size();

    QSize parentSize = p->size();
    if (d->splitType == FirstSplit) {
        if (isSplitHorizontal())
            return QSize(parentSize.width(), p->splitLocation());
        return QSize(p->splitLocation(), parentSize.height());
    }
    if (isSplitHorizontal())
        return QSize(parentSize.width(), parentSize.height() - p->splitLocation());
    return QSize(parentSize.width() - p->splitLocation(), parentSize.height());
}

int GLWidgetSplit::width() const
{
    return size().width();
}

int GLWidgetSplit::height() const
{
    return size().height();
}

bool GLWidgetSplit::isSplit() const
{
    return d->splitType != ParentSplit;
}

bool GLWidgetSplit::isSplitHorizontal() const
{
    return d->splitOrientation == HorizontalSplit;
}

bool GLWidgetSplit::isSplitVertical() const
{
    return d->splitOrientation == VerticalSplit;
}

void GLWidgetSplit::splitHorizontal()
{
}

void GLWidgetSplit::splitVertical()
{
}

void GLWidgetSplit::removeSplit()
{
}

int GLWidgetSplit::splitLocation() const
{
    return d->splitLocation;
}

void GLWidgetSplit::setSplitLocation(int location)
{
    d->splitLocation = location;
}

GLViewport *GLWidgetSplit::viewport() const
{
    if (isSplit())
        return 0;

    d->createViewport();
    return d->viewport;
}

GLWidgetSplit *GLWidgetSplit::splitOne() const
{
    return d->splitOne;
}

GLWidgetSplit *GLWidgetSplit::splitTwo() const
{
    return d->splitTwo;
}
