/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2010 Andrew Fillebrown.
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

#include "editor3dimpl.h"

#include <extensionsystem/pluginmanager.h>

using namespace Editor3D;

Editor3DImpl::Editor3DImpl()
{
}

Editor3DImpl::~Editor3DImpl()
{
}

void Editor3DImpl::viewAll()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewAll();
}

void Editor3DImpl::viewFront()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewFront();
}

void Editor3DImpl::viewSide()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewSide();
}

void Editor3DImpl::viewBottom()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewBottom();
}

void Editor3DImpl::viewZoom()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewZoom();
}

void Editor3DImpl::viewPan()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewPan();
}

void Editor3DImpl::viewRotate()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewRotate();
}

void Editor3DImpl::viewParallel()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewParallel();
}

void Editor3DImpl::viewPerspective()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewPerspective();
}

void Editor3DImpl::viewScaleIncreaseX()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewScaleIncreaseX();
}

void Editor3DImpl::viewScaleDecreaseX()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewScaleDecreaseX();
}

void Editor3DImpl::viewScaleIncreaseZ()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewScaleIncreaseZ();
}

void Editor3DImpl::viewScaleDecreaseZ()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewScaleDecreaseZ();
}

void Editor3DImpl::viewTransparencyNone()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewTransparencyNone();
}

void Editor3DImpl::viewTransparencyScreen()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewTransparencyScreen();
}

void Editor3DImpl::viewTransparencyFull()
{
    qDebug() << Q_FUNC_INFO;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    IEditor3D *ed = pm->getObject<IEditor3D>();
    if (!ed)
        return;
    ed->viewTransparencyFull();
}
