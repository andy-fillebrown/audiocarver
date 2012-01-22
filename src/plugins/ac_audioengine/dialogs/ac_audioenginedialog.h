/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2012 Andrew Fillebrown.
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

class AudioEngineDialogPrivate;
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
    void engineSettingsChanged();
    void updateDeviceList();
    void deviceChanged();
    void sampleRateChanged();
    void controlRateChanged();

private:
    bool eventFilter(QObject *object, QEvent *event);

    AudioEngineDialogPrivate *d;
    Ui_AudioEngineDialog *ui;

    friend class AudioEngineDialogPrivate;
};

#endif // AC_AUDIOENGINEDIALOG_H
