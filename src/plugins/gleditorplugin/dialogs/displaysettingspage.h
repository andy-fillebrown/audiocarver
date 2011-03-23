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

#ifndef GLEDITOR_DISPLAYSETTINGSPAGE_H
#define GLEDITOR_DISPLAYSETTINGSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>

namespace GLEditor {

class DisplaySettings;

namespace Internal {
namespace Ui {

class DisplaySettingsPage;

} // namespace Ui

class DisplaySettingsPageData
{
public:
    DisplaySettingsPageData();

    DisplaySettings *settings;
};

class DisplaySettingsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    DisplaySettingsPage();

    static DisplaySettingsPage *instance();

    QString id() const;
    QString displayName() const;
    QString category() const;
    QString displayCategory() const;
    QIcon categoryIcon() const;
    QWidget* createPage(QWidget *parent);
    virtual bool matches(const QString &s) const;

    void apply();
    void finish();

signals:
    void changed();

private:
    Ui::DisplaySettingsPage *ui;
};

} // namespace Internal
} // namespace GLEditor

#endif // GLEDITOR_DISPLAYSETTINGSPAGE_H
