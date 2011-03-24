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

#ifndef GL_BEHAVIORSETTINGSPAGE_H
#define GL_BEHAVIORSETTINGSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>

#include <gleditorplugin/settings/behaviorsettings.h>

namespace GL {

class BehaviorSettings;
class Widget;

namespace Internal {
namespace Ui {

class BehaviorSettingsPage;

} // namespace Ui

class BehaviorSettingsPageData
{
public:
    BehaviorSettingsPageData();
    ~BehaviorSettingsPageData();

    BehaviorSettings *settings;
    BehaviorSettings prevSettings;
};

class BehaviorSettingsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    BehaviorSettingsPage();
    ~BehaviorSettingsPage();

    static BehaviorSettingsPage *instance();

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
    void settingsChanged(const BehaviorSettings &previousSettings);

private:
    BehaviorSettingsPageData *d;
    Ui::BehaviorSettingsPage *ui;

    friend class GL::Widget;
};

} // namespace Internal
} // namespace GL

#endif // GL_BEHAVIORSETTINGSPAGE_H
