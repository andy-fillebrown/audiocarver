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

#include <icore.h>

#include <QAudioDeviceInfo>

#include <qmath.h>
#include <QSettings>

using namespace Core;

AudioEngineDialog::AudioEngineDialog(QObject *parent)
    :   IOptionsPage(parent)
{}

AudioEngineDialog::~AudioEngineDialog()
{}

void AudioEngineDialog::initialize()
{
    updateDeviceList();
    updateSettingsLists();

    // Set device combo box index.
    QString device_name = deviceName();
    int current_index = ui->deviceComboBox->findText(device_name);
    if (device_name.isEmpty() || current_index < 0)
        device_name = QAudioDeviceInfo::defaultOutputDevice().deviceName();
    ui->deviceComboBox->setCurrentIndex(ui->deviceComboBox->findText(device_name));

    // Populate buffer size combo box.
    int buffer_size = 128;
    for (int i = 0;  i < 10;  ++i) {
        ui->bufferSizeComboBox->addItem(QString("%1").arg(buffer_size));
        buffer_size += buffer_size;
    }
}

QString AudioEngineDialog::id() const
{
    return QString(AUDIOENGINEDIALOG_ID);
}

QString AudioEngineDialog::displayName() const
{
    return QString(tr("Sound"));
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
    return QIcon(AUDIOENGINE_CATEGORY_ICON);
}

QWidget *AudioEngineDialog::createPage(QWidget *parent)
{
    ui = new Ui_AudioEngineDialog;
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    connect(ui->deviceRefreshPushButton, SIGNAL(clicked()), SLOT(updateDeviceList()));

    initialize();

    return w;
}

void AudioEngineDialog::apply()
{
    setDeviceName(ui->deviceComboBox->currentText());
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

void AudioEngineDialog::updateSettingsLists()
{
    const QString device_name = deviceName();
    QAudioDeviceInfo device_info;
    const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach (const QAudioDeviceInfo &device, devices) {
        if (device_name == device.deviceName()) {
            device_info = device;
            break;
        }
    }

    // Populate sample rate combo box.
    ui->sampleRateComboBox->clear();
    const QList<int> sample_rates = device_info.supportedSampleRates();
    foreach (int rate, sample_rates)
        ui->sampleRateComboBox->addItem(QString("%1").arg(rate));

    // Set sample rate combo box index.
    int sample_rate = -1;
    if (!sample_rates.contains(sampleRate()))
        sample_rate = device_info.preferredFormat().sampleRate();
    ui->sampleRateComboBox->setCurrentIndex(ui->sampleRateComboBox->findText(QString("%1").arg(sample_rate)));

    // Populate sample size combo box.
    ui->sampleSizeComboBox->clear();
    const QList<int> sample_sizes = device_info.supportedSampleSizes();
    foreach (int size, sample_sizes)
        ui->sampleSizeComboBox->addItem(QString("%1").arg(size));

    // Set sample size combo box index.
    int sample_size = -1;
    if (!sample_sizes.contains(sampleSize()))
        sample_size = device_info.preferredFormat().sampleSize();
    ui->sampleSizeComboBox->setCurrentIndex(ui->sampleSizeComboBox->findText(QString("%1").arg(sample_size)));
}

int AudioEngineDialog::controlRate() const
{
    return 0;
}

void AudioEngineDialog::setControlRate(int rate)
{
    Q_UNUSED(rate);
}

int AudioEngineDialog::sampleRate() const
{
    return 0;
}

void AudioEngineDialog::setSampleRate(int rate)
{
    Q_UNUSED(rate);
}

int AudioEngineDialog::sampleSize() const
{
    return 0;
}

void AudioEngineDialog::setSampleSize(int size)
{
    Q_UNUSED(size);
}

int AudioEngineDialog::bufferSize() const
{
    return 0;
}

void AudioEngineDialog::setBufferSize(int size)
{
    Q_UNUSED(size);
}

QString AudioEngineDialog::deviceName() const
{
    QSettings* settings = ICore::instance()->settings();
    return settings->value("AudioEngine/DeviceName").toString();
}

void AudioEngineDialog::setDeviceName(const QString &name)
{
    QSettings* settings = ICore::instance()->settings();
    settings->setValue("AudioEngine/DeviceName", name);
}
