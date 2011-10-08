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

#ifndef AC_GRIDLINE_H
#define AC_GRIDLINE_H

#include <ac_graphicsitem.h>
#include <ac_graphicsobject.h>

#include <QColor>

class GridSettings;

class QGraphicsItem;

class GridLinePrivate;
class AC_CORE_EXPORT GridLine : public GraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal location READ location WRITE setLocation)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int priority READ priority WRITE setPriority)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    qreal location() const;
    void setLocation(qreal location);
    const QString &label() const;
    void setLabel(const QString &label);
    int priority() const;
    void setPriority(int priority);
    const QColor &color() const;
    void setColor(const QColor &color);

    GridSettings *gridSettings() const;

    virtual void show() {}
    virtual void hide() {}

protected:
    GridLine(GridLinePrivate &dd, QObject *parent);

private:
    Q_DISABLE_COPY(GridLine)
    Q_DECLARE_PRIVATE(GridLine)
};

class GridLinePrivate : public GraphicsObjectPrivate
{
    Q_DECLARE_PUBLIC(GridLine)

public:
    qreal location;
    QString label;
    int priority;
    QColor color;

    GridLinePrivate(GridLine *q);

    GraphicsParentPrivate *graphicsParent() const;
    virtual void updateGraphicsItems() = 0;
};

class TimeGridLinePrivate;
class AC_CORE_EXPORT TimeGridLine : public GridLine
{
    Q_OBJECT

public:
    explicit TimeGridLine(QObject *parent = 0);

    Ac::ItemType type() const { return Ac::TimeGridLineItem; }

    void show();
    void hide();

private:
    Q_DISABLE_COPY(TimeGridLine)
    Q_DECLARE_PRIVATE(TimeGridLine)

//    friend class GridSettingsPrivate;
};

class PitchGridLinePrivate;
class AC_CORE_EXPORT PitchGridLine : public GridLine
{
    Q_OBJECT

public:
    explicit PitchGridLine(QObject *parent = 0);

    Ac::ItemType type() const { return Ac::PitchGridLineItem; }

private:
    Q_DISABLE_COPY(PitchGridLine)
    Q_DECLARE_PRIVATE(PitchGridLine)

//    friend class GridSettingsPrivate;
};

class ControlGridLinePrivate;
class AC_CORE_EXPORT ControlGridLine : public GridLine
{
    Q_OBJECT

public:
    explicit ControlGridLine(QObject *parent = 0);

    Ac::ItemType type() const { return Ac::ControlGridLineItem; }

private:
    Q_DISABLE_COPY(ControlGridLine)
    Q_DECLARE_PRIVATE(ControlGridLine)

//    friend class GridSettingsPrivate;
};

#endif // AC_GRIDLINE_H
