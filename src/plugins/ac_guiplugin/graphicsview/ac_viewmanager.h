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

#ifndef AC_VIEWMANAGER_H
#define AC_VIEWMANAGER_H

#include <QObject>

class QGraphicsView;
class QWidget;

class AcViewManagerPrivate;

class AcViewManager : public QObject
{
    Q_OBJECT

public:
    AcViewManager(QWidget *widget);
    ~AcViewManager();

    QGraphicsView *pitchView() const;
    QGraphicsView *volumeView() const;
    QGraphicsView *timeLabelView() const;
    QGraphicsView *pitchLabelView() const;
    QGraphicsView *volumeLabelView() const;

    qreal timePosition() const;
    void setTimePosition(qreal position);
    qreal pitchPosition() const;
    void setPitchPosition(qreal position);
    qreal volumePosition() const;
    void setVolumePosition(qreal position);
    qreal timeScale() const;
    void setTimeScale(qreal scale);
    qreal pitchScale() const;
    void setPitchScale(qreal scale);
    qreal volumeScale() const;
    void setVolumeScale(qreal scale);

    void updateViews();

//private slots:
//    void updateViewSettings(int i, const QVariant &value);

private:
    Q_DISABLE_COPY(AcViewManager)
    AcViewManagerPrivate *d;
};

#endif // AC_VIEWMANAGER_H
