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

#include <QtCore/QSize>

using namespace GLEditor;
using namespace GLEditor::Internal;

namespace GLEditor {
namespace Internal {

class GLWidgetSplitPrivate
{
public:
    GLWidgetSplitPrivate(GLWidgetSplit *q, GLWidget *glWidget, int w, int h)
    {
    }

    ~GLWidgetSplitPrivate()
    {
    }
};

} // namespace Internal
} // namespace Editor3D

GLWidgetSplit::GLWidgetSplit(GLWidget *glWidget, const QSize &size)
    :   d(new GLWidgetSplitPrivate(this, glWidget, size.width(), size.height()))
{
    Q_CHECK_PTR(d);
}

GLWidgetSplit::GLWidgetSplit(GLWidget *glWidget, int w, int h)
    :   d(new GLWidgetSplitPrivate(this, glWidget, w, h))
{
    Q_CHECK_PTR(d);
}

GLWidgetSplit::~GLWidgetSplit()
{
    delete d;  d = 0;
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
