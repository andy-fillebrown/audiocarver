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

#include "behaviorsettingspage.h"
#include "ui_behaviorsettingspage.h"

#include <gleditorplugin/gleditorconstants.h>
#include <coreplugin/icore.h>

using namespace GL;
using namespace GL::Internal;

static BehaviorSettingsPage *instance = 0;

BehaviorSettingsPageData::BehaviorSettingsPageData()
    :   settings(new BehaviorSettings)
{
}

BehaviorSettingsPageData::~BehaviorSettingsPageData()
{
    delete settings;  settings = 0;
}

BehaviorSettingsPage::BehaviorSettingsPage()
    :   d(new BehaviorSettingsPageData)
    ,   ui(0)
{
    ::instance = this;

    d->settings->load(displayCategory(), Core::ICore::instance()->settings());
    d->prevSettings = *d->settings;
}

BehaviorSettingsPage::~BehaviorSettingsPage()
{
    delete ui;  ui = 0;
    delete d;  d = 0;
}

BehaviorSettingsPage *BehaviorSettingsPage::instance()
{
    return ::instance;
}

QString BehaviorSettingsPage::id() const
{
    return QLatin1String(Constants::SETTINGS_ID_3D_BEHAVIOR);
}

QString BehaviorSettingsPage::displayName() const
{
    return QLatin1String("Behavior");
}

QString BehaviorSettingsPage::category() const
{
    return QLatin1String(Constants::SETTINGS_CATEGORY_3D);
}

QString BehaviorSettingsPage::displayCategory() const
{
    return QCoreApplication::translate("GLEditor", Constants::SETTINGS_TR_CATERGORY_3D);
}

QIcon BehaviorSettingsPage::categoryIcon() const
{
    return QIcon(QLatin1String(Constants::SETTINGS_CATEGORY_3D_ICON));
}

QWidget *BehaviorSettingsPage::createPage(QWidget *parent)
{
    ui = new Ui::BehaviorSettingsPage();
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    const BehaviorSettingsData &data = d->settings->d;
    ui->zoomSpeedSpinBox->setValue(data.zoomSpeed);
    ui->linkModelTranslationsCheckBox->setChecked(data.linkModelTranslations);

    return w;
}

bool BehaviorSettingsPage::matches(const QString &s) const
{
    Q_UNUSED(s);
    return false;
}

void BehaviorSettingsPage::apply()
{
    BehaviorSettingsData &data = d->settings->d;
    data.zoomSpeed = ui->zoomSpeedSpinBox->value();
    data.linkModelTranslations = ui->linkModelTranslationsCheckBox->isChecked();

    if (d->prevSettings == *d->settings)
        return;

    emit settingsChanged(d->prevSettings);
    d->prevSettings = *d->settings;

    d->settings->save(displayCategory(), Core::ICore::instance()->settings());
}

void BehaviorSettingsPage::finish()
{
}
