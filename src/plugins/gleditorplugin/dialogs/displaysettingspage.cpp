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

#include "displaysettingspage.h"
#include "ui_displaysettingspage.h"

#include <gleditorplugin/gleditorconstants.h>
#include <coreplugin/icore.h>

using namespace GLEditor;
using namespace GLEditor::Internal;

static DisplaySettingsPage *instance = 0;

DisplaySettingsPageData::DisplaySettingsPageData()
    :   settings(new DisplaySettings)
{
}

DisplaySettingsPageData::~DisplaySettingsPageData()
{
    delete settings;  settings = 0;
}

DisplaySettingsPage::DisplaySettingsPage()
    :   d(new DisplaySettingsPageData)
    ,   ui(0)
{
    ::instance = this;

    d->settings->load(displayCategory(), Core::ICore::instance()->settings());
    d->previousSettings = *d->settings;
}

DisplaySettingsPage::~DisplaySettingsPage()
{
    delete ui;  ui = 0;
    delete d;  d = 0;
}

DisplaySettingsPage *DisplaySettingsPage::instance()
{
    return ::instance;
}

QString DisplaySettingsPage::id() const
{
    return QLatin1String(GLEditor::Constants::SETTINGS_ID_3D_DISPLAY);
}

QString DisplaySettingsPage::displayName() const
{
    return QLatin1String("Display");
}

QString DisplaySettingsPage::category() const
{
    return QLatin1String(GLEditor::Constants::SETTINGS_CATEGORY_3D);
}

QString DisplaySettingsPage::displayCategory() const
{
    return QCoreApplication::translate("GLEditor", GLEditor::Constants::SETTINGS_TR_CATERGORY_3D);
}

QIcon DisplaySettingsPage::categoryIcon() const
{
    return QIcon(QLatin1String(GLEditor::Constants::SETTINGS_CATEGORY_3D_ICON));
}

QWidget *DisplaySettingsPage::createPage(QWidget *parent)
{
    ui = new Ui::DisplaySettingsPage();
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    QSettings* settings = Core::ICore::instance()->settings();
    ui->zoomFactorSpinBox->setValue(settings->value(QLatin1String("GLEditor/ZoomFactor"), 1.0).toDouble());

    return w;
}

bool DisplaySettingsPage::matches(const QString &s) const
{
    Q_UNUSED(s);
    return false;
}

void DisplaySettingsPage::apply()
{
    if (d->previousSettings == *d->settings)
        return;

    emit settingsChanged(d->previousSettings);
    d->previousSettings = *d->settings;

    d->settings->save(displayCategory(), Core::ICore::instance()->settings());
}

void DisplaySettingsPage::finish()
{
}
