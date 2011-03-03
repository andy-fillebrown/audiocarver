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

#ifndef IEDITOR_H
#define IEDITOR_H

#include <editorplugin/editor_global.h>

#include <QtCore/QObject>

namespace Editor {

class EDITOR_EXPORT IEditor : public QObject
{
    Q_OBJECT

public:
    IEditor();
    virtual ~IEditor();

    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void cut() = 0;
    virtual void copy() const = 0;
    virtual void paste() = 0;
    virtual void selectAll() = 0;
};

} // namespace Editor

#endif // IEDITOR_H
