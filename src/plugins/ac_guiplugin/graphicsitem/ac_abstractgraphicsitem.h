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

#ifndef AC_ABSTRACTGRAPHICSITEM_H
#define AC_ABSTRACTGRAPHICSITEM_H

#include <ac_scene_util.h>

class AcScore;
class MiObject;
class QFont;
class QFontMetrics;
class QGraphicsItem;
class QGraphicsScene;

class AcAbstractGraphicsItemPrivate
{
public:
    AcAbstractGraphicsItemPrivate()
    {}

    virtual ~AcAbstractGraphicsItemPrivate()
    {}

    const AcScore *score() const;
    const QFont font() const;
    const QFontMetrics &fontMetrics() const;
    const QGraphicsScene *pitchScene() const;
    const QGraphicsScene *volumeScene() const;
    const QGraphicsScene *timeLabelScene() const;
    const QGraphicsScene *pitchLabelScene() const;
    const QGraphicsScene *volumeLabelScene() const;
};

class AcAbstractGraphicsItem : public QObject
{
    Q_OBJECT

public:
    virtual ~AcAbstractGraphicsItem();

    virtual MiObject *dataObject() const = 0;
    virtual QGraphicsItem *sceneItem(SceneType sceneType) const = 0;

    bool isVisible() const;
    void show();
    void hide();

    void addItem(AcAbstractGraphicsItem *item);

    template <typename T>
    void addItems(const QList<T*> &items)
    {
        foreach (AcAbstractGraphicsItem *item, items)
            addItem(item);
    }

    virtual void highlight()
    {}

    virtual void unhighlight()
    {}

protected:
    AcAbstractGraphicsItem(AcAbstractGraphicsItemPrivate &dd, QObject *parent = 0)
        :   QObject(parent)
        ,   d_ptr(&dd)
    {}

    void setDataObject(MiObject *object);

    AcAbstractGraphicsItemPrivate *d_ptr;

protected slots:
    virtual void updateDataObject(int i) = 0;

private:
    Q_DISABLE_COPY(AcAbstractGraphicsItem)
    Q_DECLARE_PRIVATE(AcAbstractGraphicsItem)
};

#endif // AC_ABSTRACTGRAPHICSITEM_H
