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

#ifndef GLWIDGETSPLIT_H
#define GLWIDGETSPLIT_H

#include <gleditorplugin/gleditor_global.h>

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtCore/QSize>

namespace GLEditor {
namespace Internal {

class GLWidgetSplitPrivate;

} // namespace Internal

class GLViewport;
class GLWidget;

class GLEDITOR_EXPORT GLWidgetSplit : public QObject
{
    Q_OBJECT

public:
    enum SplitType
    {
        FirstSplit,
        SecondSplit
    };

    GLWidgetSplit(GLWidget *widget);
    GLWidgetSplit(GLWidgetSplit *parentSplit);
    virtual ~GLWidgetSplit();

    GLWidget *widget() const;
    GLWidgetSplit *parentSplit() const;

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

    GLViewport *viewport() const;    // null if split
    GLWidgetSplit *splitOne() const; // null if not split
    GLWidgetSplit *splitTwo() const; // null if not split

protected:
    virtual void paintGL();
    virtual void resize(int w, int h);

    void updateAnimation();

private:
    Internal::GLWidgetSplitPrivate *d;
    Q_DISABLE_COPY(GLWidgetSplit)

    friend class GLWidget;
};

} // namespace GLEditor

#endif // GLWIDGETSPLIT_H
