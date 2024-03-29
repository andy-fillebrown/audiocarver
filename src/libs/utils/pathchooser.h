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

#ifndef PATHCHOOSER_H
#define PATHCHOOSER_H

#include "utils_global.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QLineEdit;
QT_END_NAMESPACE


namespace Utils {

class Environment;
class PathChooserPrivate;

/**
 * A control that let's the user choose a path, consisting of a QLineEdit and
 * a "Browse" button. Has some validation logic for embedding into QWizardPage.
 */
class UTILS_EXPORT PathChooser : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Kind)
    Q_PROPERTY(QString path READ path WRITE setPath DESIGNABLE true)
    Q_PROPERTY(QString promptDialogTitle READ promptDialogTitle WRITE setPromptDialogTitle DESIGNABLE true)
    Q_PROPERTY(Kind expectedKind READ expectedKind WRITE setExpectedKind DESIGNABLE true)
    Q_PROPERTY(QString baseDirectory READ baseDirectory WRITE setBaseDirectory DESIGNABLE true)

public:
    static const char * const browseButtonLabel;

    explicit PathChooser(QWidget *parent = 0);
    virtual ~PathChooser();

    enum Kind {
        Directory,
        File,
        ExistingCommand, // A command that must exist at the time of selection
        Command, // A command that may or may not exist at the time of selection (e.g. result of a build)
        Any
    };

    // Default is <Directory>
    void setExpectedKind(Kind expected);
    Kind expectedKind() const;

    void setPromptDialogTitle(const QString &title);
    QString promptDialogTitle() const;

    void setPromptDialogFilter(const QString &filter);
    QString promptDialogFilter() const;

    void setInitialBrowsePathBackup(const QString &path);

    bool isValid() const;
    QString errorMessage() const;

    QString path() const;
    QString rawPath() const; // The raw unexpanded input.

    QString baseDirectory() const;
    void setBaseDirectory(const QString &directory);

    void setEnvironment(const Utils::Environment &env);

    /** Returns the suggested label title when used in a form layout. */
    static QString label();

    virtual bool validatePath(const QString &path, QString *errorMessage = 0);

    /** Return the home directory, which needs some fixing under Windows. */
    static QString homePath();

    void addButton(const QString &text, QObject *receiver, const char *slotFunc);
    QAbstractButton *buttonAtIndex(int index) const;

    QLineEdit *lineEdit() const;

private:
    // Returns overridden title or the one from <title>
    QString makeDialogTitle(const QString &title);

signals:
    void validChanged();
    void validChanged(bool validState);
    void changed(const QString &text);
    void editingFinished();
    void beforeBrowsing();
    void browsingFinished();
    void returnPressed();

public slots:
    void setPath(const QString &);

private slots:
    void slotBrowse();

private:
    PathChooserPrivate *m_d;
};

} // namespace Utils


#endif // PATHCHOOSER_H
