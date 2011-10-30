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

#ifndef MI_IDATABASE_H
#define MI_IDATABASE_H

#include <QObject>
#include <mi_global.h>

class QAbstractItemModel;

class MI_CORE_EXPORT IDatabase : public QObject
{
    Q_OBJECT

public:
    IDatabase();

    static IDatabase *instance();

    virtual const QString &fileExtension() const = 0;
    virtual const QString &fileFilter() const = 0;
    virtual QString fileName() const = 0;
    virtual void reset() = 0;
    virtual void read(const QString &fileName) = 0;
    virtual void write(const QString &fileName) = 0;
    virtual QAbstractItemModel *model() const = 0;

signals:
    void databaseAboutToBeRead();
    void databaseRead();
    void databaseAboutToBeWritten();
    void databaseWritten();

private:
    Q_DISABLE_COPY(IDatabase)
};

#endif // MI_IDATABASE_H
