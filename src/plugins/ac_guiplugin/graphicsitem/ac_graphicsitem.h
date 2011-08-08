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

#ifndef AC_GRAPHICSITEM_H
#define AC_GRAPHICSITEM_H

#include <ac_guienums.h>
#include <QObject>

class AcGraphicsItem;
class AcScore;
class MiObject;
class QFont;
class QFontMetrics;
class QGraphicsItem;
class QGraphicsScene;

class AcGraphicsItemPrivate
{
public:
    AcGraphicsItem *q;
    MiObject *dataObject;

    AcGraphicsItemPrivate()
        :   q(0)
        ,   dataObject(0)
    {}

    virtual ~AcGraphicsItemPrivate()
    {}

    const AcScore *score() const;
    const QFont font() const;
    const QFontMetrics &fontMetrics() const;
    const QGraphicsScene *pitchScene() const;
    const QGraphicsScene *volumeScene() const;
    const QGraphicsScene *timeLabelScene() const;
    const QGraphicsScene *pitchLabelScene() const;
    const QGraphicsScene *volumeLabelScene() const;

    void connectDataObject();
};

class AcGraphicsItem : public QObject
{
    Q_OBJECT

public:
    ~AcGraphicsItem();

    void setDataObject(MiObject *object);

    virtual QGraphicsItem *sceneItem(SceneType sceneType) const = 0;

    bool isVisible() const;
    void show();
    void hide();

    void addItem(AcGraphicsItem *item);

    template <typename T>
    void addItems(const QList<T*> &items)
    {
        foreach (AcGraphicsItem *item, items)
            addItem(item);
    }

    virtual void highlight();
    virtual void unhighlight();

protected slots:
    virtual void updateDataObject(int i, const QVariant &value) = 0;

protected:
    AcGraphicsItem(AcGraphicsItemPrivate &dd, QObject *parent = 0);

    AcGraphicsItemPrivate *d_ptr;

private:
    Q_DISABLE_COPY(AcGraphicsItem)
    Q_DECLARE_PRIVATE(AcGraphicsItem)
};

#endif // AC_GRAPHICSITEM_H
