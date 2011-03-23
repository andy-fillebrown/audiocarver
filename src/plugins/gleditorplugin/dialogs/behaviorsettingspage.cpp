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

BehaviorSettingsPage::BehaviorSettingsPage()
    :   ui(0)
{
}

QString BehaviorSettingsPage::id() const
{
    return QLatin1String(GLEditor::Constants::SETTINGS_ID_3D);
}

QString BehaviorSettingsPage::displayName() const
{
    return QLatin1String("3D");
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

    QSettings* settings = Core::ICore::instance()->settings();
    ui->zoomFactorSpinBox->setValue(settings->value(QLatin1String("GLEditor/ZoomFactor"), 1.0).toDouble());

    return w;
}

bool BehaviorSettingsPage::matches(const QString &s) const
{
    Q_UNUSED(s);
    return false;
}

void BehaviorSettingsPage::apply()
{
    qDebug() << Q_FUNC_INFO;
    QSettings *settings = Core::ICore::instance()->settings();
    settings->setValue(QLatin1String("GLEditor/ZoomFactor"), ui->zoomFactorSpinBox->value());
}

void BehaviorSettingsPage::finish()
{
    qDebug() << Q_FUNC_INFO;
}
