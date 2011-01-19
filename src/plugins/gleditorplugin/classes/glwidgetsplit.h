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

#ifndef GLWIDGETSPLIT_H
#define GLWIDGETSPLIT_H

#include <gleditorplugin/gleditor_global.h>

#include <QtCore/QObject>

namespace GLEditor {
class GLViewport;
class GLWidget;

namespace Internal {
class GLWidgetSplitPrivate;
} // namespace Internal

class GLEDITOR_EXPORT GLWidgetSplit : public QObject
{
    Q_OBJECT

public:
    GLWidgetSplit(GLWidget *glWidget, const QSize &size);
    GLWidgetSplit(GLWidget *glWidget, int width, int height);
    virtual ~GLWidgetSplit();

    QPoint pos() const;
    QRect rect() const;
    QSize size() const;
    int width() const;
    int height() const;
    void resize(const QSize &size);
    void resize(int width, int height);

    bool isSplit() const;
    bool isSplitHorizontal() const;
    bool isSplitVertical() const;
    void splitHorizontal();
    void splitVertical();
    void removeSplit();

    GLViewport *viewport() const; // null if split
    GLWidgetSplit *sectionOne() const; // null if not split
    GLWidgetSplit *sectionTwo() const; // null if not split

    int splitLocation() const;
    void setSplitLocation(int location);

private:
    Internal::GLWidgetSplitPrivate *d;
};

} // namespace GLEditor

#endif // GLWIDGETSPLIT_H
