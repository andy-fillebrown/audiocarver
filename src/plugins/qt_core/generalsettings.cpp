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

#include "generalsettings.h"
#include "qt_core_constants.h"
#if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
#	include <utils/unixutils.h>
#endif
#include <qt_core/icore.h>
#include <qt_core/mainwindow.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include <QLibraryInfo>
#include <QSettings>
#include "ui_generalsettings.h"

using namespace Core::Internal;


GeneralSettings::GeneralSettings():
    m_dialog(0)
{
}

QString GeneralSettings::id() const
{
    return QLatin1String(Core::Constants::SETTINGS_ID_ENVIRONMENT_GENERAL);
}

QString GeneralSettings::displayName() const
{
    return tr("General");
}

QString GeneralSettings::category() const
{
    return QLatin1String(Core::Constants::SETTINGS_CATEGORY_ENVIRONMENT);
}

QString GeneralSettings::displayCategory() const
{
    return QCoreApplication::translate("Core", Core::Constants::SETTINGS_TR_CATEGORY_ENVIRONMENT);
}

QIcon GeneralSettings::categoryIcon() const
{
    return QIcon(QLatin1String(Core::Constants::SETTINGS_CATEGORY_ENVIRONMENT_ICON));
}

static bool hasQmFilesForLocale(const QString &locale, const QString &creatorTrPath)
{
    static const QString qtTrPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);

    const QString trFile = QLatin1String("qt_") + locale + QLatin1String(".qm");
    return QFile::exists(qtTrPath+'/'+trFile) || QFile::exists(creatorTrPath+'/'+trFile);
}

void GeneralSettings::fillLanguageBox() const
{
    const QString currentLocale = language();

    m_page->languageBox->addItem(tr("<System Language>"), QString());
    // need to add this explicitly, since there is no qm file for English
    m_page->languageBox->addItem(QLatin1String("English"), QLatin1String("C"));
    if (currentLocale == QLatin1String("C"))
        m_page->languageBox->setCurrentIndex(m_page->languageBox->count() - 1);

    const QString creatorTrPath =
            Core::ICore::instance()->resourcePath() + QLatin1String("/translations");
    const QStringList languageFiles = QDir(creatorTrPath).entryList(QStringList(QLatin1String("qtcreator*.qm")));

    Q_FOREACH(const QString &languageFile, languageFiles)
    {
        int start = languageFile.indexOf(QLatin1Char('_'))+1;
        int end = languageFile.lastIndexOf(QLatin1Char('.'));
        const QString locale = languageFile.mid(start, end-start);
        // no need to show a language that creator will not load anyway
        if (hasQmFilesForLocale(locale, creatorTrPath)) {
            m_page->languageBox->addItem(QLocale::languageToString(QLocale(locale).language()), locale);
            if (locale == currentLocale)
                m_page->languageBox->setCurrentIndex(m_page->languageBox->count() - 1);
        }
    }
}

QWidget *GeneralSettings::createPage(QWidget *parent)
{
    m_page = new Ui::GeneralSettings();
    QWidget *w = new QWidget(parent);
    m_page->setupUi(w);

    QSettings* settings = Core::ICore::instance()->settings();
    Q_UNUSED(settings) // Windows

    fillLanguageBox();

    return w;
}

bool GeneralSettings::matches(const QString &s) const
{
    return m_searchKeywords.contains(s, Qt::CaseInsensitive);
}

void GeneralSettings::apply()
{
    int currentIndex = m_page->languageBox->currentIndex();
    setLanguage(m_page->languageBox->itemData(currentIndex, Qt::UserRole).toString());
}

void GeneralSettings::finish()
{
    delete m_page;
}

void GeneralSettings::variableHelpDialogCreator(const QString &helpText)
{
    if (m_dialog) {
        if (m_dialog->text() != helpText)
            m_dialog->setText(helpText);

        m_dialog->show();
        m_dialog->raise();
        m_dialog->activateWindow();
        return;
    }
    QMessageBox *mb = new QMessageBox(QMessageBox::Information,
                                  tr("Variables"),
                                  helpText,
                                  QMessageBox::Close);
    mb->setWindowModality(Qt::NonModal);
    m_dialog = mb;
    mb->show();
}


#if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
void GeneralSettings::showHelpForFileBrowser()
{
    variableHelpDialogCreator(Utils::UnixUtils::fileBrowserHelpText());
}
#endif

void GeneralSettings::resetLanguage()
{
    // system language is default
    m_page->languageBox->setCurrentIndex(0);
}

QString GeneralSettings::language() const
{
    QSettings* settings = Core::ICore::instance()->settings();
    return settings->value(QLatin1String("General/OverrideLanguage")).toString();
}

void GeneralSettings::setLanguage(const QString &locale)
{
    QSettings* settings = Core::ICore::instance()->settings();
    if (settings->value(QLatin1String("General/OverrideLanguage")).toString() != locale)
    {
        QMessageBox::information(Core::ICore::instance()->mainWindow(), tr("Restart required"),
                                 tr("The language change will take effect after a restart of Qt Creator."));
    }
    if (locale.isEmpty())
        settings->remove(QLatin1String("General/OverrideLanguage"));
    else
        settings->setValue(QLatin1String("General/OverrideLanguage"), locale);
}
