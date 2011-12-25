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

#include <icore.h>

#include <QAudioDeviceInfo>

#include <QSettings>

class AudioEngineDialogPrivate
{
public:
    AudioEngineDialog *q;
    QWidget *widget;
    QList<int> sampleSizes;
    QList<int> sampleRates;
    QList<int> controlRates;
    QList<int> bufferSizes;
    QStringList deviceNameStrings;
    QStringList sampleSizeStrings;
    QStringList sampleRateStrings;
    QStringList controlRateStrings;
    QStringList bufferSizeStrings;
    int prevSampleSize;
    int prevSampleRate;
    int prevControlRate;
    int prevBufferSize;
    QStringList deviceNameBlacklist;

    AudioEngineDialogPrivate(AudioEngineDialog *q)
        :   q(q)
        ,   widget(new QWidget)
        ,   prevSampleSize(0)
        ,   prevSampleRate(0)
        ,   prevControlRate(0)
        ,   prevBufferSize(0)
    {
        QSettings *settings = Core::ICore::instance()->settings();
        deviceNameBlacklist = settings->value("AudioEngine/DeviceNameBlacklist").toStringList();
    }

    ~AudioEngineDialogPrivate()
    {
        delete widget;
    }

    void updateDeviceNames()
    {
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        deviceNameStrings.clear();
        foreach (const QAudioDeviceInfo &device, devices) {
            if (deviceNameBlacklist.contains(device.deviceName()))
                continue;
            if (device.supportedSampleRates().isEmpty()) {
                addDeviceToBlacklist(device.deviceName());
                q->updateDeviceList();
                resetDeviceName(uiDeviceName());
                continue;
            }
            deviceNameStrings.append(device.deviceName());
        }
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
        if (sampleRates.isEmpty())
            addDeviceToBlacklist(deviceName);
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
        if (sampleRate == 0)
            qDebug() << Q_FUNC_INFO << ": sample rate is zero";
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

    void resetDeviceName(QString deviceName)
    {
        if (deviceNameBlacklist.contains(deviceName))
            deviceName = QAudioDeviceInfo::defaultOutputDevice().deviceName();
        if (deviceNameBlacklist.contains(deviceName))
            if (0 < q->ui->deviceComboBox->count())
                deviceName = q->ui->deviceComboBox->itemText(0);
        setDeviceNameIndex(deviceName);
    }

    void resetSampleSize(int sampleSize, const QString &deviceName)
    {
        if (!sampleSizes.contains(sampleSize))
            sampleSize = prevSampleSize;
        if (!sampleSizes.contains(sampleSize))
            sampleSize = Ac::deviceInfo(deviceName).preferredFormat().sampleSize();
        setSampleSizeIndex(sampleSize);
        prevSampleSize = sampleSize;
    }

    void resetSampleRate(int sampleRate, const QString &deviceName)
    {
        if (!sampleRates.contains(sampleRate))
            sampleRate = prevSampleRate;
        if (!sampleRates.contains(sampleRate))
            sampleRate = Ac::deviceInfo(deviceName).preferredFormat().sampleRate();
        setSampleRateIndex(sampleRate);
        prevSampleRate = sampleRate;
    }

    void resetControlRate(int controlRate, int sampleRate)
    {
        if (!Ac::controlRateIsValid(controlRate, sampleRate))
            controlRate = prevControlRate;
        if (!Ac::controlRateIsValid(controlRate, sampleRate))
            controlRate = Ac::defaultControlRate(sampleRate);
        setControlRateIndex(controlRate);
        prevControlRate = controlRate;
    }

    void resetBufferSize(int bufferSize, int sampleRate, int controlRate)
    {
        if (!Ac::bufferSizeIsValid(bufferSize, sampleRate, controlRate))
            bufferSize = prevBufferSize;
        if (!Ac::bufferSizeIsValid(bufferSize, sampleRate, controlRate))
            bufferSize = Ac::defaultBufferSize(sampleRate, controlRate);
        setBufferSizeIndex(bufferSize);
        prevBufferSize = bufferSize;
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
        int rate = q->ui->sampleRateComboBox->currentText().toInt();
        if (rate == 0)
            qDebug() << Q_FUNC_INFO << ": sample rate is zero";
        return rate;
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

    void addDeviceToBlacklist(const QString &deviceName)
    {
        if (deviceNameBlacklist.contains(deviceName))
            return;
        deviceNameBlacklist.append(deviceName);
        Core::ICore::instance()->settings()->setValue("AudioEngine/DeviceNameBlacklist", deviceNameBlacklist);
    }
};

AudioEngineDialog::AudioEngineDialog(QObject *parent)
    :   IOptionsPage(parent)
    ,   d(new AudioEngineDialogPrivate(this))
    ,   ui(new Ui_AudioEngineDialog)
{
    engineSettingsChanged();

    ui->setupUi(d->widget);

    d->updateDeviceNames();
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

    ui->deviceComboBox->installEventFilter(this);
    ui->sampleSizeComboBox->installEventFilter(this);
    ui->sampleRateComboBox->installEventFilter(this);
    ui->controlRateComboBox->installEventFilter(this);
    ui->bufferSizeComboBox->installEventFilter(this);
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
    AudioEngineSettings settings = IAudioEngine::instance()->settings();
    d->resetSampleRate(settings.sampleRate(), settings.deviceName());
    d->resetControlRate(settings.controlRate(), settings.sampleRate());
    d->resetBufferSize(settings.bufferSize(), settings.sampleRate(), settings.controlRate());

    d->widget->setParent(parent);
    return d->widget;
}

void AudioEngineDialog::apply()
{
    IAudioEngine *audio_engine = IAudioEngine::instance();
    audio_engine->setSettings(d->uiSettings());

    AudioEngineSettings settings = audio_engine->settings();
    d->resetSampleRate(settings.sampleRate(), settings.deviceName());
    d->resetControlRate(settings.controlRate(), settings.sampleRate());
    d->resetBufferSize(settings.bufferSize(), settings.sampleRate(), settings.controlRate());
    d->resetDeviceName(settings.deviceName());

    if (settings.deviceName() != d->uiDeviceName())
        audio_engine->setSettings(d->uiSettings());
}

void AudioEngineDialog::finish()
{
    d->widget->setParent(0);
}

void AudioEngineDialog::engineSettingsChanged()
{
    const AudioEngineSettings &settings = IAudioEngine::instance()->settings();

    d->updateSampleSizes(settings.deviceName());
    d->updateSampleRates(settings.deviceName());
    d->updateControlRates(settings.sampleRate());
    d->updateBufferSizes(settings.sampleRate(), settings.controlRate());
}

void AudioEngineDialog::updateDeviceList()
{
    const QString device_name = d->uiDeviceName();

    QStringList device_names = d->deviceNameStrings;
    d->updateDeviceNames();
    if (device_names == d->deviceNameStrings)
        return;
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

    d->resetDeviceName(device_name);
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

bool AudioEngineDialog::eventFilter(QObject *object, QEvent *event)
{
    if (QEvent::FocusIn == event->type()) {
        if (ui->deviceComboBox == object)
            updateDeviceList();
    } else if (QEvent::FocusOut == event->type()) {
        if (ui->sampleSizeComboBox == object)
            d->resetSampleSize(d->uiSampleSize(), d->uiDeviceName());
        else if (ui->sampleRateComboBox == object)
            d->resetSampleRate(d->uiSampleRate(), d->uiDeviceName());
        else if (ui->controlRateComboBox == object)
            d->resetControlRate(d->uiControlRate(), d->uiSampleRate());
        else if (ui->bufferSizeComboBox == object)
            d->resetBufferSize(d->uiBufferSize(), d->uiSampleRate(), d->uiControlRate());
    }
    return false;
}
