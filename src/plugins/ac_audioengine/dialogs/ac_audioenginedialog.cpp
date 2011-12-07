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

#include <ac_iaudioengine.h>

#include <icore.h>

#include <QAudioDeviceInfo>

#include <QSettings>

AudioEngineDialog::AudioEngineDialog(QObject *parent)
    :   IOptionsPage(parent)
{}

AudioEngineDialog::~AudioEngineDialog()
{}

void AudioEngineDialog::initialize()
{
    updateDeviceList();

    // Set device combo box index.
    QString device_name = deviceName();
    int current_index = ui->deviceComboBox->findText(device_name);
    if (device_name.isEmpty() || current_index < 0)
        device_name = QAudioDeviceInfo::defaultOutputDevice().deviceName();
    ui->deviceComboBox->setCurrentIndex(ui->deviceComboBox->findText(device_name));

    updateSettingsLists();

    // Populate buffer size combo box.
    int buffer_size = 128;
    for (int i = 0;  i < 10;  ++i) {
        ui->bufferSizeComboBox->addItem(QString("%1").arg(buffer_size));
        buffer_size += buffer_size;
    }

    // Set buffer size combo box index.
    buffer_size = bufferSize();
    if (0 == buffer_size)
        buffer_size = 2048;
    ui->bufferSizeComboBox->setCurrentIndex(ui->bufferSizeComboBox->findText(QString("%1").arg(buffer_size)));
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
    connect(ui->sampleRateComboBox, SIGNAL(currentIndexChanged(int)), SLOT(updateControlRateList()));

    initialize();

    return w;
}

void AudioEngineDialog::apply()
{
    setDeviceName(ui->deviceComboBox->currentText());
    setControlRate(ui->controlRateComboBox->currentText().toInt());
    setSampleRate(ui->sampleRateComboBox->currentText().toInt());
    setSampleSize(ui->sampleSizeComboBox->currentText().toInt());
    setBufferSize(ui->bufferSizeComboBox->currentText().toInt());
}

void AudioEngineDialog::finish()
{
    delete ui;
}

void AudioEngineDialog::updateDeviceList()
{
    QString device_name = ui->deviceComboBox->currentText();

    // Populate device combo box.
    ui->deviceComboBox->clear();
    const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    foreach (const QAudioDeviceInfo &device, devices)
        ui->deviceComboBox->addItem(device.deviceName());

    // Set device combo box index.
    if (device_name.isEmpty()
            || -1 == ui->deviceComboBox->findText(device_name))
        device_name = QAudioDeviceInfo::defaultOutputDevice().deviceName();
    ui->deviceComboBox->setCurrentIndex(ui->deviceComboBox->findText(device_name));
}

void AudioEngineDialog::updateSettingsLists()
{
    const QString device_name = ui->deviceComboBox->currentText();
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
    int sample_rate = sampleRate();
    if (!sample_rates.contains(sample_rate))
        sample_rate = device_info.preferredFormat().sampleRate();
    ui->sampleRateComboBox->setCurrentIndex(ui->sampleRateComboBox->findText(QString("%1").arg(sample_rate)));

    // Populate sample size combo box.
    ui->sampleSizeComboBox->clear();
    const QList<int> sample_sizes = device_info.supportedSampleSizes();
    foreach (int size, sample_sizes)
        ui->sampleSizeComboBox->addItem(QString("%1").arg(size));

    // Set sample size combo box index.
    int sample_size = sampleSize();
    if (!sample_sizes.contains(sample_size))
        sample_size = 32;
    if (!sample_sizes.contains(sample_size))
        sample_size = device_info.preferredFormat().sampleSize();
    ui->sampleSizeComboBox->setCurrentIndex(ui->sampleSizeComboBox->findText(QString("%1").arg(sample_size)));
}

void AudioEngineDialog::updateControlRateList()
{
    const int sample_rate = ui->sampleRateComboBox->currentText().toInt();

    // Populate control rate combo box.
    QList<int> control_rates;
    for (int i = 1;  i <= sample_rate;  ++i) {
        if (0 == sample_rate % i)
            control_rates.append(i);
    }
    ui->controlRateComboBox->clear();
    foreach (int rate, control_rates)
        ui->controlRateComboBox->addItem(QString("%1").arg(rate));

    // Set control rate combo box index.
    int control_rate = controlRate();
    if (!control_rates.contains(control_rate)) {
        const int n = control_rates.count();
        control_rate = control_rates.at(n - (n / 4));
    }
    ui->controlRateComboBox->setCurrentIndex(ui->controlRateComboBox->findText(QString("%1").arg(control_rate)));
}

int AudioEngineDialog::controlRate() const
{
    QSettings* settings = Core::ICore::instance()->settings();
    return settings->value("AudioEngine/ControlRate").toInt();
}

void AudioEngineDialog::setControlRate(int rate)
{
    QSettings* settings = Core::ICore::instance()->settings();
    settings->setValue("AudioEngine/ControlRate", rate);

    IAudioEngine::instance()->setControlRate(rate);
}

int AudioEngineDialog::sampleRate() const
{
    QSettings* settings = Core::ICore::instance()->settings();
    return settings->value("AudioEngine/SampleRate").toInt();
}

void AudioEngineDialog::setSampleRate(int rate)
{
    QSettings* settings = Core::ICore::instance()->settings();
    settings->setValue("AudioEngine/SampleRate", rate);

    IAudioEngine::instance()->setSampleRate(rate);
}

int AudioEngineDialog::sampleSize() const
{
    QSettings* settings = Core::ICore::instance()->settings();
    return settings->value("AudioEngine/SampleSize").toInt();
}

void AudioEngineDialog::setSampleSize(int size)
{
    QSettings* settings = Core::ICore::instance()->settings();
    settings->setValue("AudioEngine/SampleSize", size);

    IAudioEngine::instance()->setSampleSize(size);
}

int AudioEngineDialog::bufferSize() const
{
    QSettings* settings = Core::ICore::instance()->settings();
    return settings->value("AudioEngine/BufferSize").toInt();
}

void AudioEngineDialog::setBufferSize(int size)
{
    QSettings* settings = Core::ICore::instance()->settings();
    settings->setValue("AudioEngine/BufferSize", size);

    IAudioEngine::instance()->setBufferSize(size);
}

QString AudioEngineDialog::deviceName() const
{
    QSettings* settings = Core::ICore::instance()->settings();
    return settings->value("AudioEngine/DeviceName").toString();
}

void AudioEngineDialog::setDeviceName(const QString &name)
{
    QSettings* settings = Core::ICore::instance()->settings();
    settings->setValue("AudioEngine/DeviceName", name);

    IAudioEngine::instance()->setDeviceName(name);
}
