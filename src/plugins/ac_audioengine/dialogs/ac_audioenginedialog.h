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

#ifndef AC_AUDIOENGINEDIALOG_H
#define AC_AUDIOENGINEDIALOG_H

#include <ioptionspage.h>

class Ui_AudioEngineDialog;

class AudioEngineDialog : public Core::IOptionsPage
{
    Q_OBJECT

public:
    AudioEngineDialog(QObject *parent = 0);
    ~AudioEngineDialog();

    // Core::IOptionsPage
    QString id() const;
    QString displayName() const;
    QString category() const;
    QString displayCategory() const;
    QIcon categoryIcon() const;
    QWidget *createPage(QWidget *parent);
    void apply();
    void finish();

private slots:
    void updateDeviceList();
    void updateSettingsLists();
    void updateControlRateList();

private:
    void initialize();

    int controlRate() const;
    void setControlRate(int rate);

    int sampleRate() const;
    void setSampleRate(int rate);

    int sampleSize() const;
    void setSampleSize(int size);

    int bufferSize() const;
    void setBufferSize(int size);

    QString deviceName() const;
    void setDeviceName(const QString &name);

    Ui_AudioEngineDialog *ui;
};

#endif // AC_AUDIOENGINEDIALOG_H
