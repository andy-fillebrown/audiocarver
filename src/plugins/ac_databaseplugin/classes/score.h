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

#ifndef AC_SCORE_H
#define AC_SCORE_H

#include <databaseplugin/classes/root.h>

namespace AudioCarver {

namespace Internal {
class ScorePrivate;
} // namespace Internal

class Score : public Database::Root
{
    Q_OBJECT

    Q_PROPERTY(Database::ObjectList* curves READ curves)
    Q_PROPERTY(Database::ObjectList* tracks READ tracks)

public:
    Score(QObject *parent = 0);
    virtual ~Score();

    virtual QString &normalizeClassName(QString &className) const;

    virtual Database::Object *createObject(const QString &className) const;

    Database::ObjectList *curves() const;
    Database::ObjectList *tracks() const;

private:
    Q_DISABLE_COPY(Score)
    Internal::ScorePrivate *d;
};

} // namespace AudioCarver

#endif // AC_SCORE_H
