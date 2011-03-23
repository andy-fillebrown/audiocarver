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

#include "gleditorsettings.h"
#include "gleditorconstants.h"
#include "ui_gleditorsettings.h"

#include <coreplugin/icore.h>

#include <QtCore/QSettings>

using namespace GLEditor::Internal;

GLEditorSettings::GLEditorSettings()
    :   ui(0)
{
}

QString GLEditorSettings::id() const
{
    return QLatin1String(GLEditor::Constants::SETTINGS_ID_3D);
}

QString GLEditorSettings::displayName() const
{
    return QLatin1String("3D");
}

QString GLEditorSettings::category() const
{
    return QLatin1String(GLEditor::Constants::SETTINGS_CATEGORY_3D);
}

QString GLEditorSettings::displayCategory() const
{
    return QCoreApplication::translate("GLEditor", GLEditor::Constants::SETTINGS_TR_CATERGORY_3D);
}

QIcon GLEditorSettings::categoryIcon() const
{
    return QIcon(QLatin1String(GLEditor::Constants::SETTINGS_CATEGORY_3D_ICON));
}

QWidget *GLEditorSettings::createPage(QWidget *parent)
{
    ui = new Ui::GLEditorSettings();
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    QSettings* settings = Core::ICore::instance()->settings();
    Q_UNUSED(settings) // Windows

    ui->zoomFactorSpinBox->setValue(1.0);

    return w;
}

bool GLEditorSettings::matches(const QString &s) const
{
    Q_UNUSED(s);
    return false;
}

void GLEditorSettings::apply()
{
    qDebug() << Q_FUNC_INFO;
}

void GLEditorSettings::finish()
{
    qDebug() << Q_FUNC_INFO;
}
