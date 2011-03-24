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

#ifndef GL_WIDGETSPLIT_H
#define GL_WIDGETSPLIT_H

#include <gleditorplugin/gleditor_global.h>

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtCore/QSize>

namespace GL {
namespace Internal {

class WidgetSplitPrivate;

} // namespace Internal

class Viewport;
class Widget;

class GLEDITOR_EXPORT WidgetSplit : public QObject
{
    Q_OBJECT

public:
    enum SplitType
    {
        FirstSplit,
        SecondSplit
    };

    WidgetSplit(Widget *widget);
    WidgetSplit(WidgetSplit *parentSplit);
    virtual ~WidgetSplit();

    Widget *widget() const;
    WidgetSplit *parentSplit() const;

    QPoint pos() const;
    QRect rect() const;
    QSize size() const;
    int width() const;
    int height() const;

    bool isSplit() const;
    bool isSplitHorizontal() const;
    bool isSplitVertical() const;
    void splitHorizontal();
    void splitVertical();
    void removeSplit();

    qreal splitLocation() const;
    void setSplitLocation(qreal location);

    Viewport *viewport() const;    // null if split
    WidgetSplit *splitOne() const; // null if not split
    WidgetSplit *splitTwo() const; // null if not split

protected:
    virtual void resize(int w, int h);

private:
    Internal::WidgetSplitPrivate *d;
    Q_DISABLE_COPY(WidgetSplit)

    friend class Widget;
};

} // namespace GL

#endif // GL_WIDGETSPLIT_H
