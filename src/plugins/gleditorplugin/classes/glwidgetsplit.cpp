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
    qreal splitLocation;
    GLViewport *viewport;
    GLWidgetSplit *splitOne;
    GLWidgetSplit *splitTwo;

    GLWidgetSplitPrivate(GLWidgetSplit *q, GLWidget *widget)
        :   q(q)
        ,   widget(widget)
        ,   parentSplit(0)
        ,   splitType(GLWidgetSplit::FirstSplit)
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
        splitLocation = 0.5;
        viewport = 0;
        splitOne = 0;
        splitTwo = 0;
    }

    ~GLWidgetSplitPrivate()
    {
        destroySplits();
        destroyViewport();
        splitLocation = 0.5;
        splitOrientation = NotSplit;
        splitType = GLWidgetSplit::FirstSplit;
        parentSplit = 0;
        widget = 0;
        q = 0;
    }

    void init()
    {
        createViewport();
    }

    void createViewport()
    {
        if (viewport)
            return;
        destroySplits();
        viewport = new GLViewport(q, parentSplit ? parentSplit->size() : widget->size());
    }

    void destroyViewport()
    {
        delete viewport;  viewport = 0;
    }

    void createSplits(SplitOrientation orientation = HorizontalSplit)
    {
        if (splitOne)
            return;
        destroyViewport();
        splitOne = new GLWidgetSplit(q, GLWidgetSplit::FirstSplit);
        splitTwo = new GLWidgetSplit(q, GLWidgetSplit::SecondSplit);
        splitOrientation = orientation;
    }

    void destroySplits()
    {
        delete splitTwo;  splitTwo = 0;
        delete splitOne;  splitOne = 0;
    }
};

} // namespace Internal
} // namespace Editor3D

GLWidgetSplit::GLWidgetSplit(GLWidget *widget)
    :   d(new GLWidgetSplitPrivate(this, widget))
{
    Q_CHECK_PTR(d);
    d->init();
}

GLWidgetSplit::GLWidgetSplit(GLWidgetSplit *parentSplit, SplitType splitType)
    :   d(new GLWidgetSplitPrivate(this, parentSplit, splitType))
{
    Q_CHECK_PTR(d);
    d->init();
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
    if (!p)
        return QPoint();

    QPoint parentPos = p->pos();
    if (d->splitType == FirstSplit)
        return parentPos;
    if (isSplitHorizontal())
        return QPoint(parentPos.x(), parentPos.y() + (p->splitLocation() * p->height()));
    return QPoint(parentPos.x() + (p->splitLocation() * p->width()), parentPos.y());
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
    if (!isSplit())
        return p->size();

    QSize parentSize = p->size();
    if (d->splitType == FirstSplit) {
        if (isSplitHorizontal())
            return QSize(parentSize.width(), p->splitLocation() * parentSize.height());
        return QSize(p->splitLocation(), parentSize.height());
    }
    if (isSplitHorizontal())
        return QSize(parentSize.width(), parentSize.height() - (p->splitLocation() * parentSize.height()));
    return QSize(parentSize.width() - (p->splitLocation() * parentSize.height()), parentSize.height());
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
    return d->viewport == 0;
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
    d->createSplits(HorizontalSplit);
}

void GLWidgetSplit::splitVertical()
{
    d->createSplits(VerticalSplit);
}

void GLWidgetSplit::removeSplit()
{
    d->createViewport();
}

qreal GLWidgetSplit::splitLocation() const
{
    return d->splitLocation;
}

void GLWidgetSplit::setSplitLocation(qreal location)
{
    d->splitLocation = location;
}

GLViewport *GLWidgetSplit::viewport() const
{
    if (isSplit())
        return 0;
    return d->viewport;
}

GLWidgetSplit *GLWidgetSplit::splitOne() const
{
    if (!isSplit())
        return 0;
    return d->splitOne;
}

GLWidgetSplit *GLWidgetSplit::splitTwo() const
{
    if (!isSplit())
        return 0;
    return d->splitTwo;
}

void GLWidgetSplit::draw()
{
    if (isSplit()) {
        d->splitOne->draw();
        d->splitTwo->draw();
    } else {
        d->viewport->draw();
    }
}
