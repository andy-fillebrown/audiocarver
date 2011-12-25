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
#include <ac_audioenginesettings.h>
#include <ac_audioengineutils.h>

#include <ac_iaudioengine.h>

#include <QAudioDeviceInfo>

class AudioEngineDialogPrivate
{
public:
    AudioEngineDialog *q;
    QList<int> sampleSizes;
    QList<int> sampleRates;
    QList<int> controlRates;
    QList<int> bufferSizes;
    QStringList deviceNameStrings;
    QStringList sampleSizeStrings;
    QStringList sampleRateStrings;
    QStringList controlRateStrings;
    QStringList bufferSizeStrings;
    QWidget *widget;

    AudioEngineDialogPrivate(AudioEngineDialog *q)
        :   q(q)
        ,   widget(new QWidget)
    {}

    ~AudioEngineDialogPrivate()
    {
        delete widget;
    }

    void updateDeviceNames()
    {
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        deviceNameStrings.clear();
        foreach (const QAudioDeviceInfo &device, devices)
            deviceNameStrings.append(device.deviceName());
    }

    void updateSampleSizes(const QString &deviceName)
    {
        sampleSizes = Ac::deviceInfo(deviceName).supportedSampleSizes();
        sampleSizeStrings.clear();
        foreach (int size, sampleSizes)
            sampleSizeStrings.append(QString("%1").arg(size));
    }

    void updateSampleRates(const QString &deviceName)
    {
        sampleRates = Ac::deviceInfo(deviceName).supportedSampleRates();
        sampleRateStrings.clear();
        foreach (int rate, sampleRates)
            sampleRateStrings.append(QString("%1").arg(rate));
    }

    void updateControlRates(int sampleRate)
    {
        controlRates.clear();
        for (int i = 1;  i <= sampleRate;  ++i) {
            if (0 == sampleRate % i)
                controlRates.append(i);
        }
        controlRateStrings.clear();
        foreach (int rate, controlRates)
            controlRateStrings.append(QString("%1").arg(rate));
    }

    void updateBufferSizes(int sampleRate, int controlRate)
    {
        if (sampleRate < controlRate)
            controlRate = sampleRate;
        const int control_samples = sampleRate / controlRate;
        bufferSizes.clear();
        for (int i = control_samples;  i <= sampleRate;  i += control_samples)
            bufferSizes.append(i);
        bufferSizeStrings.clear();
        foreach (int size, bufferSizes)
            bufferSizeStrings.append(QString("%1").arg(size));
    }

    void updateDeviceNamesUi()
    {
        Ui_AudioEngineDialog *ui = q->ui;
        ui->deviceComboBox->blockSignals(true);
        ui->deviceComboBox->clear();
        ui->deviceComboBox->addItems(deviceNameStrings);
        ui->deviceComboBox->blockSignals(false);
    }

    void updateSampleSizesUi()
    {
        Ui_AudioEngineDialog *ui = q->ui;
        ui->sampleSizeComboBox->blockSignals(true);
        ui->sampleSizeComboBox->clear();
        ui->sampleSizeComboBox->addItems(sampleSizeStrings);
        ui->sampleSizeComboBox->blockSignals(false);
    }

    void updateSampleRatesUi()
    {
        Ui_AudioEngineDialog *ui = q->ui;
        ui->sampleRateComboBox->blockSignals(true);
        ui->sampleRateComboBox->clear();
        ui->sampleRateComboBox->addItems(sampleRateStrings);
        ui->sampleRateComboBox->blockSignals(false);
    }

    void updateControlRatesUi()
    {
        Ui_AudioEngineDialog *ui = q->ui;
        ui->controlRateComboBox->blockSignals(true);
        ui->controlRateComboBox->clear();
        ui->controlRateComboBox->addItems(controlRateStrings);
        ui->controlRateComboBox->blockSignals(false);
    }

    void updateBufferSizesUi()
    {
        Ui_AudioEngineDialog *ui = q->ui;
        ui->bufferSizeComboBox->blockSignals(true);
        ui->bufferSizeComboBox->clear();
        ui->bufferSizeComboBox->addItems(bufferSizeStrings);
        ui->bufferSizeComboBox->blockSignals(false);
    }

    void setDeviceNameIndex(const QString &deviceName)
    {
        Ui_AudioEngineDialog *ui = q->ui;
        int index = ui->deviceComboBox->findText(deviceName);
        if (index == -1)
            index = ui->deviceComboBox->findText(QAudioDeviceInfo::defaultOutputDevice().deviceName());
        ui->deviceComboBox->setCurrentIndex(index);
    }

    void setSampleSizeIndex(int sampleSize)
    {
        Ui_AudioEngineDialog *ui = q->ui;
        const int index = ui->sampleSizeComboBox->findText(QString("%1").arg(sampleSize));
        ui->sampleSizeComboBox->setCurrentIndex(index);
    }

    void setSampleRateIndex(int sampleRate)
    {
        Ui_AudioEngineDialog *ui = q->ui;
        const int index = ui->sampleRateComboBox->findText(QString("%1").arg(sampleRate));
        ui->sampleRateComboBox->setCurrentIndex(index);
    }

    void setControlRateIndex(int controlRate)
    {
        Ui_AudioEngineDialog *ui = q->ui;
        const int index = ui->controlRateComboBox->findText(QString("%1").arg(controlRate));
        ui->controlRateComboBox->setCurrentIndex(index);
    }

    void setBufferSizeIndex(int bufferSize)
    {
        Ui_AudioEngineDialog *ui = q->ui;
        const int index = ui->bufferSizeComboBox->findText(QString("%1").arg(bufferSize));
        ui->bufferSizeComboBox->setCurrentIndex(index);
    }

    void resetSampleRate(int sampleRate, const QString &deviceName)
    {
        if (!sampleRates.contains(sampleRate))
            sampleRate = Ac::deviceInfo(deviceName).preferredFormat().sampleRate();
        setSampleRateIndex(sampleRate);
    }

    void resetControlRate(int controlRate, int sampleRate)
    {
        if (!Ac::controlRateIsValid(controlRate, sampleRate))
            controlRate = Ac::defaultControlRate(sampleRate);
        setControlRateIndex(controlRate);
    }

    void resetBufferSize(int bufferSize, int sampleRate, int controlRate)
    {
        if (!Ac::bufferSizeIsValid(bufferSize, sampleRate, controlRate))
            bufferSize = Ac::defaultBufferSize(sampleRate, controlRate);
        setBufferSizeIndex(bufferSize);
    }

    QString uiDeviceName() const
    {
        return q->ui->deviceComboBox->currentText();
    }

    int uiSampleSize() const
    {
        return q->ui->sampleSizeComboBox->currentText().toInt();
    }

    int uiSampleRate() const
    {
        return q->ui->sampleRateComboBox->currentText().toInt();
    }

    int uiControlRate() const
    {
        return q->ui->controlRateComboBox->currentText().toInt();
    }

    int uiBufferSize() const
    {
        return q->ui->bufferSizeComboBox->currentText().toInt();
    }

    AudioEngineSettings uiSettings() const
    {
        AudioEngineSettings ui_settings;
        Ui_AudioEngineDialog *ui = q->ui;
        ui_settings.setDeviceName(ui->deviceComboBox->currentText());
        ui_settings.setSampleSize(ui->sampleSizeComboBox->currentText().toInt());
        ui_settings.setSampleRate(ui->sampleRateComboBox->currentText().toInt());
        ui_settings.setControlRate(ui->controlRateComboBox->currentText().toInt());
        ui_settings.setBufferSize(ui->bufferSizeComboBox->currentText().toInt());
        return ui_settings;
    }
};

AudioEngineDialog::AudioEngineDialog(QObject *parent)
    :   IOptionsPage(parent)
    ,   d(new AudioEngineDialogPrivate(this))
    ,   ui(new Ui_AudioEngineDialog)
{
    engineSettingsChanged();

    ui->setupUi(d->widget);

    d->updateDeviceNamesUi();
    d->updateSampleSizesUi();
    d->updateSampleRatesUi();
    d->updateControlRatesUi();
    d->updateBufferSizesUi();

    const AudioEngineSettings &settings = IAudioEngine::instance()->settings();
    d->setDeviceNameIndex(settings.deviceName());
    d->setSampleSizeIndex(settings.sampleSize());
    d->setSampleRateIndex(settings.sampleRate());
    d->setControlRateIndex(settings.controlRate());
    d->setBufferSizeIndex(settings.bufferSize());

    connect(IAudioEngine::instance(), SIGNAL(settingsChanged()), SLOT(engineSettingsChanged()));
    connect(ui->deviceRefreshPushButton, SIGNAL(clicked()), SLOT(updateDeviceList()));
    connect(ui->deviceComboBox, SIGNAL(currentIndexChanged(int)), SLOT(deviceChanged()));
    connect(ui->sampleRateComboBox, SIGNAL(currentIndexChanged(int)), SLOT(sampleRateChanged()));
    connect(ui->controlRateComboBox, SIGNAL(currentIndexChanged(int)), SLOT(controlRateChanged()));
}

AudioEngineDialog::~AudioEngineDialog()
{
    delete ui;
    delete d;
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
    d->widget->setParent(parent);
    return d->widget;
}

void AudioEngineDialog::apply()
{
    IAudioEngine::instance()->setSettings(d->uiSettings());
}

void AudioEngineDialog::finish()
{
    d->widget->setParent(0);
}

void AudioEngineDialog::engineSettingsChanged()
{
    const AudioEngineSettings &settings = IAudioEngine::instance()->settings();

    d->updateDeviceNames();
    d->updateSampleSizes(settings.deviceName());
    d->updateSampleRates(settings.deviceName());
    d->updateControlRates(settings.sampleRate());
    d->updateBufferSizes(settings.sampleRate(), settings.controlRate());
}

void AudioEngineDialog::updateDeviceList()
{
    const QString device_name = d->uiDeviceName();

    d->updateDeviceNames();
    d->updateDeviceNamesUi();
    d->setDeviceNameIndex(device_name);
}

void AudioEngineDialog::deviceChanged()
{
    const QString device_name = d->uiDeviceName();
    int sample_size = d->uiSampleSize();
    const int sample_rate = d->uiSampleRate();
    const int control_rate = d->uiControlRate();
    const int buffer_size = d->uiBufferSize();

    d->updateSampleSizes(device_name);
    d->updateSampleSizesUi();
    if (!d->sampleSizes.contains(sample_size))
        sample_size = Ac::deviceInfo(device_name).preferredFormat().sampleSize();
    d->setSampleSizeIndex(sample_size);

    d->updateSampleRates(device_name);
    d->updateSampleRatesUi();
    d->resetSampleRate(sample_rate, device_name);

    d->updateControlRates(sample_rate);
    d->updateControlRatesUi();
    d->resetControlRate(control_rate, sample_rate);

    d->updateBufferSizes(sample_rate, control_rate);
    d->updateBufferSizesUi();
    d->resetBufferSize(buffer_size, sample_rate, control_rate);
}

void AudioEngineDialog::sampleRateChanged()
{
    const int sample_rate = d->uiSampleRate();
    const int control_rate = d->uiControlRate();
    const int buffer_size = d->uiBufferSize();

    d->updateControlRates(sample_rate);
    d->updateControlRatesUi();
    d->resetControlRate(control_rate, sample_rate);

    d->updateBufferSizes(sample_rate, control_rate);
    d->updateBufferSizesUi();
    d->resetBufferSize(buffer_size, sample_rate, control_rate);
}

void AudioEngineDialog::controlRateChanged()
{
    const int sample_rate = d->uiSampleRate();
    const int control_rate = d->uiControlRate();
    const int buffer_size = d->uiBufferSize();

    d->updateBufferSizes(sample_rate, control_rate);
    d->updateBufferSizesUi();
    d->resetBufferSize(buffer_size, sample_rate, control_rate);
}
