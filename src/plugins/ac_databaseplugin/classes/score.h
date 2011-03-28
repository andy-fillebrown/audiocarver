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

#ifndef AC_SCORE_H
#define AC_SCORE_H

#include <databaseplugin/classes/root.h>

#include <ac_databaseplugin/ac_database_global.h>

namespace AudioCarver {
namespace Internal {

class ScoreData;

} // namespace Internal

class AC_DATABASE_EXPORT Score : public Database::Root
{
    Q_OBJECT

    Q_PROPERTY(Database::List* settings READ settings)
    Q_PROPERTY(Database::List* tunings READ tunings)
    Q_PROPERTY(Database::List* curves READ curves)
    Q_PROPERTY(Database::List* tracks READ tracks)

public:
    Score(QObject *parent = 0);
private:
    virtual ~Score();
    Q_DISABLE_COPY(Score)

public:
    static Score *instance();

    Database::List *settings() const;
    Database::List *tunings() const;
    Database::List *curves() const;
    Database::List *tracks() const;

    void clear();

    QString &normalizeClassName(QString &className) const;
    Database::Object *createObject(const QString &className);
    Database::Object *findObject(const QString &className) const;

private:
    Internal::ScoreData *d;
};

} // namespace AudioCarver

#endif // AC_SCORE_H
