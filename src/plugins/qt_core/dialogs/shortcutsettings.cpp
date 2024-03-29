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

#include "shortcutsettings.h"
#include "actionmanager_p.h"
#include "actionmanager/command.h"
#include "command_p.h"
#include "commandsfile.h"
#include "filemanager.h"
#include "icore.h"
#include "qt_core_constants.h"
#include "uniqueidmanager.h"
#include <utils/treewidgetcolumnstretcher.h>
#include <QShortcut>
#include <QHeaderView>
#include <QFileDialog>
#include <QLineEdit>
#include <QAction>
#include <QTreeWidgetItem>
#include <QKeyEvent>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QVariant>
#include <QtDebug>

Q_DECLARE_METATYPE(Core::Internal::ShortcutItem*)

using namespace Core;
using namespace Core::Internal;

ShortcutSettings::ShortcutSettings(QObject *parent)
    : CommandMappings(parent)
{
}

ShortcutSettings::~ShortcutSettings()
{
}

// IOptionsPage


QString ShortcutSettings::id() const
{
    return QLatin1String(Core::Constants::SETTINGS_ID_ENVIRONMENT_KEYBOARD);
}

QString ShortcutSettings::displayName() const
{
    return tr("Keyboard");
}

QString ShortcutSettings::category() const
{
    return QLatin1String(Core::Constants::SETTINGS_CATEGORY_ENVIRONMENT);
}

QString ShortcutSettings::displayCategory() const
{
    return QCoreApplication::translate("Core", Core::Constants::SETTINGS_TR_CATEGORY_ENVIRONMENT);
}

QIcon ShortcutSettings::categoryIcon() const
{
    return QIcon(QLatin1String(Core::Constants::SETTINGS_CATEGORY_ENVIRONMENT_ICON));
}

QWidget *ShortcutSettings::createPage(QWidget *parent)
{
    m_keyNum = m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;

    QWidget *w = CommandMappings::createPage(parent);

    const QString pageTitle = tr("Keyboard Shortcuts");
    const QString targetLabelText = tr("Key sequence:");
    const QString editTitle = tr("Shortcut");

    setPageTitle(pageTitle);
    setTargetLabelText(targetLabelText);
    setTargetEditTitle(editTitle);
    setTargetHeader(editTitle);

    if (m_searchKeywords.isEmpty()) {
        QTextStream(&m_searchKeywords) << ' ' << pageTitle
                << ' ' << targetLabelText
                << ' ' << editTitle;
    }

    return w;
}

void ShortcutSettings::apply()
{
    foreach (ShortcutItem *item, m_scitems)
        item->m_cmd->setKeySequence(item->m_key);
}

void ShortcutSettings::finish()
{
    qDeleteAll(m_scitems);
    m_scitems.clear();

    CommandMappings::finish();
}

bool ShortcutSettings::matches(const QString &s) const
{
    return m_searchKeywords.contains(s, Qt::CaseInsensitive);
}

bool ShortcutSettings::eventFilter(QObject *o, QEvent *e)
{
    Q_UNUSED(o)

    if ( e->type() == QEvent::KeyPress ) {
        QKeyEvent *k = static_cast<QKeyEvent*>(e);
        handleKeyEvent(k);
        return true;
    }

    if ( e->type() == QEvent::Shortcut ||
         e->type() == QEvent::KeyRelease ) {
        return true;
    }

    if (e->type() == QEvent::ShortcutOverride) {
        // for shortcut overrides, we need to accept as well
        e->accept();
        return true;
    }

    return false;
}

void ShortcutSettings::commandChanged(QTreeWidgetItem *current)
{
    CommandMappings::commandChanged(current);
    if (!current || !current->data(0, Qt::UserRole).isValid())
        return;
    ShortcutItem *scitem = current->data(0, Qt::UserRole).value<ShortcutItem*>();
    setKeySequence(scitem->m_key);
}

void ShortcutSettings::targetIdentifierChanged()
{
    QTreeWidgetItem *current = commandList()->currentItem();
    if (current && current->data(0, Qt::UserRole).isValid()) {
        ShortcutItem *scitem = current->data(0, Qt::UserRole).value<ShortcutItem*>();
        scitem->m_key = QKeySequence(m_key[0], m_key[1], m_key[2], m_key[3]);
        if (scitem->m_cmd->defaultKeySequence() != scitem->m_key)
            setModified(current, true);
        else
            setModified(current, false);
        current->setText(2, scitem->m_key.toString());
        resetCollisionMarker(scitem);
        markPossibleCollisions(scitem);
    }
}

void ShortcutSettings::setKeySequence(const QKeySequence &key)
{
    m_keyNum = m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    m_keyNum = key.count();
    for (int i = 0; i < m_keyNum; ++i) {
        m_key[i] = key[i];
    }
    targetEdit()->setText(key.toString());
}

void ShortcutSettings::resetTargetIdentifier()
{
    QTreeWidgetItem *current = commandList()->currentItem();
    if (current && current->data(0, Qt::UserRole).isValid()) {
        ShortcutItem *scitem = current->data(0, Qt::UserRole).value<ShortcutItem*>();
        setKeySequence(scitem->m_cmd->defaultKeySequence());
    }
}

void ShortcutSettings::removeTargetIdentifier()
{
    m_keyNum = m_key[0] = m_key[1] = m_key[2] = m_key[3] = 0;
    targetEdit()->clear();
}

void ShortcutSettings::importAction()
{
    UniqueIDManager *uidm = UniqueIDManager::instance();

    QString fileName = QFileDialog::getOpenFileName(0, tr("Import Keyboard Mapping Scheme"),
        ICore::instance()->resourcePath() + "/schemes/",
        tr("Keyboard Mapping Scheme (*.kms)"));
    if (!fileName.isEmpty()) {

        CommandsFile cf(fileName);
        QMap<QString, QKeySequence> mapping = cf.importCommands();

        foreach (ShortcutItem *item, m_scitems) {
            QString sid = uidm->stringForUniqueIdentifier(item->m_cmd->id());
            if (mapping.contains(sid)) {
                item->m_key = mapping.value(sid);
                item->m_item->setText(2, item->m_key.toString());
                if (item->m_item == commandList()->currentItem())
                    commandChanged(item->m_item);

                if (item->m_cmd->defaultKeySequence() != item->m_key)
                    setModified(item->m_item, true);
                else
                    setModified(item->m_item, false);
            }
        }

        foreach (ShortcutItem *item, m_scitems) {
            resetCollisionMarker(item);
            markPossibleCollisions(item);
        }
    }
}

void ShortcutSettings::defaultAction()
{
    foreach (ShortcutItem *item, m_scitems) {
        item->m_key = item->m_cmd->defaultKeySequence();
        item->m_item->setText(2, item->m_key.toString());
        setModified(item->m_item, false);
        if (item->m_item == commandList()->currentItem())
            commandChanged(item->m_item);
    }

    foreach (ShortcutItem *item, m_scitems) {
        resetCollisionMarker(item);
        markPossibleCollisions(item);
    }
}

void ShortcutSettings::exportAction()
{
    QString fileName = ICore::instance()->fileManager()->getSaveFileNameWithExtension(
        tr("Export Keyboard Mapping Scheme"),
        ICore::instance()->resourcePath() + "/schemes/",
        tr("Keyboard Mapping Scheme (*.kms)"));
    if (!fileName.isEmpty()) {
        CommandsFile cf(fileName);
        cf.exportCommands(m_scitems);
    }
}

void ShortcutSettings::initialize()
{
    Core::Internal::ActionManagerPrivate *am = ActionManagerPrivate::instance();
    UniqueIDManager *uidm = UniqueIDManager::instance();

    QMap<QString, QTreeWidgetItem *> sections;

    foreach (Command *c, am->commands()) {
        if (c->hasAttribute(Command::CA_NonConfigureable))
            continue;
        if (c->action() && c->action()->isSeparator())
            continue;

        QTreeWidgetItem *item = 0;
        ShortcutItem *s = new ShortcutItem;
        m_scitems << s;
        item = new QTreeWidgetItem;
        s->m_cmd = c;
        s->m_item = item;

        const QString identifier = uidm->stringForUniqueIdentifier(c->id());
        int pos = identifier.indexOf(QLatin1Char('.'));
        const QString section = identifier.left(pos);
        const QString subId = identifier.mid(pos+1);
        if (!sections.contains(section)) {
            QTreeWidgetItem *categoryItem = new QTreeWidgetItem(commandList(), QStringList() << section);
            QFont f = categoryItem->font(0);
            f.setBold(true);
            categoryItem->setFont(0, f);
            sections.insert(section, categoryItem);
            commandList()->expandItem(categoryItem);
        }
        sections[section]->addChild(item);

        item->setText(0, subId);

        if (c->action()) {
            QString text = c->hasAttribute(Command::CA_UpdateText) && !c->defaultText().isNull() ? c->defaultText() : c->action()->text();
            text.remove(QRegExp("&(?!&)"));
            s->m_key = c->action()->shortcut();
            item->setText(1, text);
        } else {
            s->m_key = c->shortcut()->key();
            item->setText(1, c->shortcut()->whatsThis());
        }

        item->setText(2, s->m_key.toString());
        if (s->m_cmd->defaultKeySequence() != s->m_key)
            setModified(item, true);

        item->setData(0, Qt::UserRole, qVariantFromValue(s));

        markPossibleCollisions(s);
    }
}

void ShortcutSettings::handleKeyEvent(QKeyEvent *e)
{
    int nextKey = e->key();
    if ( m_keyNum > 3 ||
         nextKey == Qt::Key_Control ||
         nextKey == Qt::Key_Shift ||
         nextKey == Qt::Key_Meta ||
         nextKey == Qt::Key_Alt )
         return;

    nextKey |= translateModifiers(e->modifiers(), e->text());
    switch (m_keyNum) {
        case 0:
            m_key[0] = nextKey;
            break;
        case 1:
            m_key[1] = nextKey;
            break;
        case 2:
            m_key[2] = nextKey;
            break;
        case 3:
            m_key[3] = nextKey;
            break;
        default:
            break;
    }
    m_keyNum++;
    QKeySequence ks(m_key[0], m_key[1], m_key[2], m_key[3]);
    targetEdit()->setText(ks.toString());
    e->accept();
}

int ShortcutSettings::translateModifiers(Qt::KeyboardModifiers state,
                                         const QString &text)
{
    int result = 0;
    // The shift modifier only counts when it is not used to type a symbol
    // that is only reachable using the shift key anyway
    if ((state & Qt::ShiftModifier) && (text.size() == 0
                                        || !text.at(0).isPrint()
                                        || text.at(0).isLetter()
                                        || text.at(0).isSpace()))
        result |= Qt::SHIFT;
    if (state & Qt::ControlModifier)
        result |= Qt::CTRL;
    if (state & Qt::MetaModifier)
        result |= Qt::META;
    if (state & Qt::AltModifier)
        result |= Qt::ALT;
    return result;
}

void ShortcutSettings::markPossibleCollisions(ShortcutItem *item)
{
    if (item->m_key.isEmpty())
        return;

    int globalId = Context(Constants::C_GLOBAL).at(0);

    foreach (ShortcutItem *currentItem, m_scitems) {

        if (currentItem->m_key.isEmpty() || item == currentItem ||
            item->m_key != currentItem->m_key) {
            continue;
        }

        foreach (int context, currentItem->m_cmd->context()) {

            // conflict if context is identical, OR if one
            // of the contexts is the global context
            if (item->m_cmd->context().contains(context) ||
               (item->m_cmd->context().contains(globalId) &&
                !currentItem->m_cmd->context().isEmpty()) ||
                (currentItem->m_cmd->context().contains(globalId) &&
                !item->m_cmd->context().isEmpty())) {
                currentItem->m_item->setForeground(2, Qt::red);
                item->m_item->setForeground(2, Qt::red);

            }
        }
    }
}

void ShortcutSettings::resetCollisionMarker(ShortcutItem *item)
{
    item->m_item->setForeground(2, commandList()->palette().foreground());
}


void ShortcutSettings::resetCollisionMarkers()
{
    foreach (ShortcutItem *item, m_scitems)
        resetCollisionMarker(item);
}
