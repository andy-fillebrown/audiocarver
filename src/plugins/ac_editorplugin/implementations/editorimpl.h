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

#ifndef AC_EDITORIMPL_H
#define AC_EDITORIMPL_H

#include <editorplugin/interfaces/ieditor.h>

namespace AudioCarver {
namespace Internal {

class EditorImpl : public Editor::IEditor
{
public:
    EditorImpl() {}
private:
    ~EditorImpl() {}
    Q_DISABLE_COPY(EditorImpl)

private:
    void undo();
    void redo();
    void cut();
    void copy() const;
    void paste();
    void selectAll();
};

} // namespace Internal
} // namespace AudioCarver

#endif // AC_EDITORIMPL_H
