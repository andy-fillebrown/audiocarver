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
    SplitOrientation splitOrientation;
    qreal splitLocation;
    QPoint pos;
    QSize size;
    GLViewport *viewport;
    GLWidgetSplit *splitOne;
    GLWidgetSplit *splitTwo;

    GLWidgetSplitPrivate(GLWidgetSplit *q, GLWidget *widget)
        :   q(q)
        ,   widget(widget)
        ,   parentSplit(0)
    {
        commonConstructor();

        pos = widget->pos();
        size = widget->size();
    }

    GLWidgetSplitPrivate(GLWidgetSplit *q, GLWidgetSplit *parentSplit)
        :   q(q)
        ,   widget(parentSplit->widget())
        ,   parentSplit(parentSplit)
    {
        commonConstructor();

        pos = parentSplit->pos();
        size = parentSplit->size();
    }

    void commonConstructor()
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
        viewport = new GLViewport(q);
        Q_CHECK_PTR(viewport);
    }

    void destroyViewport()
    {
        delete viewport;  viewport = 0;
    }

    void createSplits(SplitOrientation orientation)
    {
        if (splitOne)
            return;
        destroyViewport();
        splitOrientation = orientation;
        splitOne = new GLWidgetSplit(q);
        Q_CHECK_PTR(splitOne);
        splitTwo = new GLWidgetSplit(q);
        Q_CHECK_PTR(splitTwo);
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

GLWidgetSplit::GLWidgetSplit(GLWidgetSplit *parentSplit)
    :   d(new GLWidgetSplitPrivate(this, parentSplit))
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
    return d->pos;
}

QRect GLWidgetSplit::rect() const
{
    return QRect(pos(), size());
}

QSize GLWidgetSplit::size() const
{
    return d->size;
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
    resize(width(), height());
}

void GLWidgetSplit::splitVertical()
{
    d->createSplits(VerticalSplit);
    resize(width(), height());
}

void GLWidgetSplit::removeSplit()
{
    d->createViewport();
    resize(width(), height());
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
    } else
        d->viewport->draw();
}

void GLWidgetSplit::resize(int w, int h)
{
    if (w < 1)
        w = 1;
    if (h < 1)
        h = 1;
    d->size = QSize(w, h);

    if (isSplit()) {
        const QPoint pos = this->pos();
        d->splitOne->d->pos = pos;
        d->splitTwo->d->pos = pos;
        if (isSplitHorizontal()) {
            d->splitOne->resize(w, d->splitLocation * h);
            d->splitTwo->d->pos.ry() += (splitLocation() * qreal(h)) + 1;
            d->splitTwo->resize(w, h - d->splitTwo->d->pos.y());
        } else {
            d->splitOne->resize(d->splitLocation * w, h);
            d->splitTwo->d->pos.rx() += (splitLocation() * qreal(w)) + 1;
            d->splitTwo->resize(w - d->splitTwo->d->pos.x(), h);
        }
    } else
        d->viewport->resize(w, h);
}
