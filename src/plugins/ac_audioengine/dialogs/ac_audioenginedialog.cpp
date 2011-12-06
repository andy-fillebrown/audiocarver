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

#include <ac_audioenginedialog.h>

#include <ui_ac_audioenginedialog.h>

#include <ac_audioengineconstants.h>

#include <QAudioDeviceInfo>

#include <QDebug>

using namespace Core;

AudioEngineDialog::AudioEngineDialog(QObject *parent)
    :   IOptionsPage(parent)
{}

AudioEngineDialog::~AudioEngineDialog()
{}

QString AudioEngineDialog::id() const
{
    return QString(AUDIOENGINEDIALOG_ID);
}

QString AudioEngineDialog::displayName() const
{
    return QString(tr("Audio Engine"));
}

QString AudioEngineDialog::category() const
{
    return QString(AUDIOENGINE_CATEGORY);
}

QString AudioEngineDialog::displayCategory() const
{
    return QCoreApplication::translate("AudioEngine", AUDIOENGINE_CATEGORY_TR);
}

QIcon AudioEngineDialog::categoryIcon() const
{
    return QIcon();
}

QWidget *AudioEngineDialog::createPage(QWidget *parent)
{
    ui = new Ui_AudioEngineDialog;
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    connect(ui->deviceRefreshPushButton, SIGNAL(clicked()), SLOT(updateDeviceList()));

    updateDeviceList();

    return w;
}

void AudioEngineDialog::apply()
{
}

void AudioEngineDialog::finish()
{
    delete ui;
}

void AudioEngineDialog::updateDeviceList()
{
    ui->deviceComboBox->clear();
    const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach (const QAudioDeviceInfo &device, devices)
        ui->deviceComboBox->addItem(device.deviceName());
}
