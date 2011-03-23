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

#include <QtCore/QSettings>

using namespace GLEditor::Internal;

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
    d->settings->fromSettings(displayCategory(), Core::ICore::instance()->settings());
    d->previousSettings = *d->settings;
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
    return QLatin1String(GLEditor::Constants::SETTINGS_ID_3D_BEHAVIOR);
}

QString BehaviorSettingsPage::displayName() const
{
    return QLatin1String("Behavior");
}

QString BehaviorSettingsPage::category() const
{
    return QLatin1String(GLEditor::Constants::SETTINGS_CATEGORY_3D);
}

QString BehaviorSettingsPage::displayCategory() const
{
    return QCoreApplication::translate("GLEditor", GLEditor::Constants::SETTINGS_TR_CATERGORY_3D);
}

QIcon BehaviorSettingsPage::categoryIcon() const
{
    return QIcon(QLatin1String(GLEditor::Constants::SETTINGS_CATEGORY_3D_ICON));
}

QWidget *BehaviorSettingsPage::createPage(QWidget *parent)
{
    ui = new Ui::BehaviorSettingsPage();
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    ui->zoomSpeedSpinBox->setValue(d->settings->d.zoomSpeed);

    return w;
}

bool BehaviorSettingsPage::matches(const QString &s) const
{
    Q_UNUSED(s);
    return false;
}

void BehaviorSettingsPage::apply()
{
    d->settings->d.zoomSpeed = ui->zoomSpeedSpinBox->value();

    if (d->previousSettings == *d->settings)
        return;

    emit settingsChanged(d->previousSettings);
    d->previousSettings = *d->settings;
    d->settings->toSettings(displayCategory(), Core::ICore::instance()->settings());
}

void BehaviorSettingsPage::finish()
{
    qDebug() << Q_FUNC_INFO;
}
