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
#include <ac_audioengineutils.h>

#include <ac_iaudioengine.h>

#include <QAudioDeviceInfo>

class AudioEngineDialogPrivate
{
public:
    AudioEngineDialog *q;

    AudioEngineDialogPrivate(AudioEngineDialog *q)
        :   q(q)
    {}

    void init()
    {
        updateDeviceList();

        // Set device combo box index.
        q->ui->deviceComboBox->setCurrentIndex(q->ui->deviceComboBox->findText(q->deviceName()));

        updateSettingsLists();
        updateControlRateList();
        updateBufferSizeList();
    }

    void updateDeviceList()
    {
        // Populate device combo box.
        q->ui->deviceComboBox->clear();
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        foreach (const QAudioDeviceInfo &device, devices)
            q->ui->deviceComboBox->addItem(device.deviceName());
    }

    void updateSettingsLists()
    {
        QAudioDeviceInfo device_info = Ac::deviceInfo(q->ui->deviceComboBox->currentText());

        // Populate sample rate combo box.
        q->ui->sampleRateComboBox->clear();
        const QList<int> sample_rates = device_info.supportedSampleRates();
        foreach (int rate, sample_rates)
            q->ui->sampleRateComboBox->addItem(QString("%1").arg(rate));

        // Set sample rate combo box index.
        q->ui->sampleRateComboBox->setCurrentIndex(q->ui->sampleRateComboBox->findText(QString("%1").arg(q->sampleRate())));

        // Populate sample size combo box.
        q->ui->sampleSizeComboBox->clear();
        const QList<int> sample_sizes = device_info.supportedSampleSizes();
        foreach (int size, sample_sizes)
            q->ui->sampleSizeComboBox->addItem(QString("%1").arg(size));

        // Set sample size combo box index.
        q->ui->sampleSizeComboBox->setCurrentIndex(q->ui->sampleSizeComboBox->findText(QString("%1").arg(q->sampleSize())));
    }

    void updateControlRateList()
    {
        const int sample_rate = q->ui->sampleRateComboBox->currentText().toInt();

        // Populate control rate combo box.
        QList<int> control_rates;
        for (int i = 1;  i <= sample_rate;  ++i) {
            if (0 == sample_rate % i)
                control_rates.append(i);
        }
        q->ui->controlRateComboBox->clear();
        foreach (int rate, control_rates)
            q->ui->controlRateComboBox->addItem(QString("%1").arg(rate));

        // Set control rate combo box index.
        int control_rate = q->controlRate();
        if (!IAudioEngine::instance()->controlRateIsValid(control_rate, sample_rate))
            control_rate = IAudioEngine::instance()->defaultControlRate(sample_rate);
        q->ui->controlRateComboBox->setCurrentIndex(q->ui->controlRateComboBox->findText(QString("%1").arg(control_rate)));
    }

    void updateBufferSizeList()
    {
        const int sample_rate = q->ui->sampleRateComboBox->currentText().toInt();
        const int control_rate = q->ui->controlRateComboBox->currentText().toInt();
        const int control_samples = sample_rate / control_rate;

        // Populate buffer size combo box.
        QList<int> buffer_sizes;
        int cur_ctrl_samples = control_samples;
        while (cur_ctrl_samples <= sample_rate) {
            buffer_sizes.append(cur_ctrl_samples);
            cur_ctrl_samples += control_samples;
        }
        q->ui->bufferSizeComboBox->clear();
        foreach (int size, buffer_sizes)
            q->ui->bufferSizeComboBox->addItem(QString("%1").arg(size));

        // Set buffer size combo box index.
        int buffer_size = q->bufferSize();
        if (!IAudioEngine::instance()->bufferSizeIsValid(buffer_size, control_samples))
            buffer_size = IAudioEngine::instance()->defaultBufferSize(control_samples, sample_rate);
        q->ui->bufferSizeComboBox->setCurrentIndex(q->ui->bufferSizeComboBox->findText(QString("%1").arg(buffer_size)));
    }
};

AudioEngineDialog::AudioEngineDialog(QObject *parent)
    :   IOptionsPage(parent)
    ,   d(new AudioEngineDialogPrivate(this))
{}

AudioEngineDialog::~AudioEngineDialog()
{
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
    ui = new Ui_AudioEngineDialog;
    QWidget *w = new QWidget(parent);
    ui->setupUi(w);

    d->init();

    connect(ui->deviceRefreshPushButton, SIGNAL(clicked()), SLOT(updateDeviceList()));
    connect(ui->sampleRateComboBox, SIGNAL(currentIndexChanged(int)), SLOT(updateControlRateList()));
    connect(ui->controlRateComboBox, SIGNAL(currentIndexChanged(int)), SLOT(updateBufferSizeList()));

    return w;
}

void AudioEngineDialog::apply()
{
    setDeviceName(ui->deviceComboBox->currentText());
    setControlRate(ui->controlRateComboBox->currentText().toInt());
    setSampleRate(ui->sampleRateComboBox->currentText().toInt());
    setSampleSize(ui->sampleSizeComboBox->currentText().toInt());
    setBufferSize(ui->bufferSizeComboBox->currentText().toInt());
    IAudioEngine::instance()->applySettings();
}

void AudioEngineDialog::finish()
{
    delete ui;
}

int AudioEngineDialog::controlRate() const
{
    return IAudioEngine::instance()->controlRate();
}

void AudioEngineDialog::setControlRate(int rate)
{
    IAudioEngine::instance()->setControlRate(rate);
}

int AudioEngineDialog::sampleRate() const
{
    return IAudioEngine::instance()->sampleRate();
}

void AudioEngineDialog::setSampleRate(int rate)
{
    IAudioEngine::instance()->setSampleRate(rate);
}

int AudioEngineDialog::sampleSize() const
{
    return IAudioEngine::instance()->sampleSize();
}

void AudioEngineDialog::setSampleSize(int size)
{
    IAudioEngine::instance()->setSampleSize(size);
}

int AudioEngineDialog::bufferSize() const
{
    return IAudioEngine::instance()->bufferSize();
}

void AudioEngineDialog::setBufferSize(int size)
{
    IAudioEngine::instance()->setBufferSize(size);
}

QString AudioEngineDialog::deviceName() const
{
    return IAudioEngine::instance()->deviceName();
}

void AudioEngineDialog::setDeviceName(const QString &name)
{
    IAudioEngine::instance()->setDeviceName(name);
}

void AudioEngineDialog::updateDeviceList()
{
    d->updateDeviceList();
}

void AudioEngineDialog::updateSettingsLists()
{
    d->updateSettingsLists();
}

void AudioEngineDialog::updateControlRateList()
{
    d->updateControlRateList();
}

void AudioEngineDialog::updateBufferSizeList()
{
    d->updateBufferSizeList();
}
