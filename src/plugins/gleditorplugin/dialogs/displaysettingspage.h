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

#ifndef GL_DISPLAYSETTINGSPAGE_H
#define GL_DISPLAYSETTINGSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>

#include <gleditorplugin/settings/displaysettings.h>

namespace GL {

class DisplaySettings;
class Widget;

namespace Internal {
namespace Ui {

class DisplaySettingsPage;

} // namespace Ui

class DisplaySettingsPageData
{
public:
    DisplaySettingsPageData();
    ~DisplaySettingsPageData();

    DisplaySettings *settings;
    DisplaySettings previousSettings;
};

class DisplaySettingsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    DisplaySettingsPage();
    ~DisplaySettingsPage();

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
    void settingsChanged(const DisplaySettings &previousSettings);

private:
    DisplaySettingsPageData *d;
    Ui::DisplaySettingsPage *ui;

    friend class GL::Widget;
};

} // namespace Internal
} // namespace GL

#endif // GL_DISPLAYSETTINGSPAGE_H
