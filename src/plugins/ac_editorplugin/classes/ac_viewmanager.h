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

#ifndef AC_VIEWMANAGER_H
#define AC_VIEWMANAGER_H

#include <QObject>
#include <ac_editor_global.h>

class AcMainWidget;

namespace Private {

class AcViewManagerData;

} // namespace Private

class AcViewManager : public QObject
{
    Q_OBJECT

public:
    AcViewManager(AcMainWidget *mainWidget);
    ~AcViewManager();

private slots:
    virtual void updateScoreProperty(const QString &propertyName);
    virtual void updateViewSettingsProperty(const QString &propertyName);

private:
    Q_DISABLE_COPY(AcViewManager)
    Private::AcViewManagerData *d;
};

#endif // AC_VIEWMANAGER_H
