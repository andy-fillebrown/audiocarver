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

#include "widgetsplit.h"

#include "viewport.h"
#include "widget.h"

#include <QtCore/QSize>

using namespace GL;
using namespace GL::Internal;

namespace GL {
namespace Internal {

enum SplitOrientation
{
    NotSplit,
    HorizontalSplit,
    VerticalSplit
};

class WidgetSplitPrivate
{
public:
    WidgetSplit *q;
    Widget *widget;
    WidgetSplit *parentSplit;
    SplitOrientation splitOrientation;
    qreal splitLocation;
    QPoint pos;
    QSize size;
    Viewport *viewport;
    WidgetSplit *splitOne;
    WidgetSplit *splitTwo;

    WidgetSplitPrivate(WidgetSplit *q, Widget *widget)
        :   q(q)
        ,   widget(widget)
        ,   parentSplit(0)
    {
        commonConstructor();

        pos = widget->pos();
        size = widget->size();
    }

    WidgetSplitPrivate(WidgetSplit *q, WidgetSplit *parentSplit)
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

    ~WidgetSplitPrivate()
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
        viewport = new Viewport(q);
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
        splitLocation = 0.5;
        splitOne = new WidgetSplit(q);
        Q_CHECK_PTR(splitOne);
        splitTwo = new WidgetSplit(q);
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

WidgetSplit::WidgetSplit(Widget *widget)
    :   d(new WidgetSplitPrivate(this, widget))
{
    Q_CHECK_PTR(d);
    d->init();
}

WidgetSplit::WidgetSplit(WidgetSplit *parentSplit)
    :   d(new WidgetSplitPrivate(this, parentSplit))
{
    Q_CHECK_PTR(d);
    d->init();
}

WidgetSplit::~WidgetSplit()
{
    delete d;  d = 0;
}

Widget *WidgetSplit::widget() const
{
    return d->widget;
}

WidgetSplit *WidgetSplit::parentSplit() const
{
    return d->parentSplit;
}

QPoint WidgetSplit::pos() const
{
    return d->pos;
}

QRect WidgetSplit::rect() const
{
    return QRect(pos(), size());
}

QSize WidgetSplit::size() const
{
    return d->size;
}

int WidgetSplit::width() const
{
    return size().width();
}

int WidgetSplit::height() const
{
    return size().height();
}

bool WidgetSplit::isSplit() const
{
    return d->viewport == 0;
}

bool WidgetSplit::isSplitHorizontal() const
{
    return d->splitOrientation == HorizontalSplit;
}

bool WidgetSplit::isSplitVertical() const
{
    return d->splitOrientation == VerticalSplit;
}

void WidgetSplit::splitHorizontal()
{
    d->createSplits(HorizontalSplit);
    resize(width(), height());
}

void WidgetSplit::splitVertical()
{
    d->createSplits(VerticalSplit);
    resize(width(), height());
}

void WidgetSplit::removeSplit()
{
    d->createViewport();
    resize(width(), height());
}

qreal WidgetSplit::splitLocation() const
{
    return d->splitLocation;
}

void WidgetSplit::setSplitLocation(qreal location)
{
    if (d->splitLocation == location)
        return;

    // Make sure sub-split width and height won't be smaller than 3 pixels.
    if (isSplitHorizontal()) {
        const qreal h = height();
        const int newSplitHeight = location * h;
        if (newSplitHeight < 3)
            location = 3.0 / h;
        if (h - newSplitHeight < 3)
            location = (h - 3.0) / h;
    } else {
        const qreal w = width();
        const int newSplitWidth = location * w;
        if (newSplitWidth < 3)
            location = 3.0 / w;
        if (w - newSplitWidth < 3)
            location = (w - 3.0) / w;
    }

    d->splitLocation = location;
}

Viewport *WidgetSplit::viewport() const
{
    if (isSplit())
        return 0;
    return d->viewport;
}

WidgetSplit *WidgetSplit::splitOne() const
{
    if (!isSplit())
        return 0;
    return d->splitOne;
}

WidgetSplit *WidgetSplit::splitTwo() const
{
    if (!isSplit())
        return 0;
    return d->splitTwo;
}

void WidgetSplit::resize(int w, int h)
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
            d->splitTwo->d->pos.ry() += (d->splitLocation * qreal(h)) + 1; // +1 for border
            d->splitTwo->resize(w, pos.y() + h - d->splitTwo->d->pos.y());
        } else {
            d->splitOne->resize(d->splitLocation * w, h);
            d->splitTwo->d->pos.rx() += (d->splitLocation * qreal(w)) + 1; // +1 for border
            d->splitTwo->resize(pos.x() + w - d->splitTwo->d->pos.x(), h);
        }
    } else
        d->viewport->resize(w, h);
}
