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

#ifndef AC_GUIFACTORY_H
#define AC_GUIFACTORY_H

#include <QObject>

class AcGraphicsItem;
class AcSceneManager;
class AcScore;
class MiObject;

class AcGuiFactoryPrivate;
class AcGuiFactory : public QObject
{
    Q_OBJECT

public:
    explicit AcGuiFactory(QObject *parent = 0);
    inline ~AcGuiFactory();

    static AcGuiFactory *instance();

    AcSceneManager *createSceneManager(QObject *parent = 0);

protected:
    AcGuiFactoryPrivate *d_ptr;

private:
    Q_DISABLE_COPY(AcGuiFactory)
    Q_DECLARE_PRIVATE(AcGuiFactory)
};

class AcGuiFactoryPrivate
{
    Q_DECLARE_PUBLIC(AcGuiFactory)

public:
    AcGuiFactory *q_ptr;

    AcGuiFactoryPrivate(AcGuiFactory *q)
        :   q_ptr(q)
    {}

    AcScore *score();

    void connectGraphicsItem(AcGraphicsItem *item, MiObject *object);
};

inline AcGuiFactory::~AcGuiFactory()
{
    delete d_ptr;
}

#endif // AC_GUIFACTORY_H
