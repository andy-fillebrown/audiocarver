/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef UTILS_ENVIRONMENT_H
#define UTILS_ENVIRONMENT_H

#include "utils_global.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QList>

namespace Utils {

class UTILS_EXPORT EnvironmentItem
{
public:
    EnvironmentItem(QString n, QString v)
            : name(n), value(v), unset(false)
    {}

    QString name;
    QString value;
    bool unset;

    bool operator==(const EnvironmentItem &other) const
    {
        return (unset == other.unset) && (name == other.name) && (value == other.value);
    }

    static QList<EnvironmentItem> fromStringList(QStringList list);
    static QStringList toStringList(QList<EnvironmentItem> list);
};

class UTILS_EXPORT Environment {
public:
    typedef QMap<QString, QString>::const_iterator const_iterator;

    Environment();
    explicit Environment(QStringList env);
    static Environment systemEnvironment();

    QStringList toStringList() const;
    QString value(const QString &key) const;
    void set(const QString &key, const QString &value);
    void unset(const QString &key);
    void modify(const QList<EnvironmentItem> & list);
    bool hasKey(const QString &key);

    void appendOrSet(const QString &key, const QString &value, const QString &sep = QString());
    void prependOrSet(const QString &key, const QString &value, const QString &sep = QString());

    void appendOrSetPath(const QString &value);
    void prependOrSetPath(const QString &value);

    void clear();
    int size() const;

    QString key(Environment::const_iterator it) const;
    QString value(Environment::const_iterator it) const;

    Environment::const_iterator constBegin() const;
    Environment::const_iterator constEnd() const;
    Environment::const_iterator constFind(const QString &name) const;

    QString searchInPath(const QString &executable,
                         const QStringList & additionalDirs = QStringList()) const;
    QStringList path() const;

    QString expandVariables(const QString &) const;
    QStringList expandVariables(const QStringList &) const;

    bool operator!=(const Environment &other) const;
    bool operator==(const Environment &other) const;
private:
    QString searchInPath(const QStringList &executables,
                         const QStringList & additionalDirs = QStringList()) const;
    QMap<QString, QString> m_values;
};

} // namespace Utils

#endif // UTILS_ENVIRONMENT_H
