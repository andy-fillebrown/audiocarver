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

#ifndef AC_TRACK_H
#define AC_TRACK_H

#include <ac_scoreobject.h>

#include <QColor>

class Note;
class Score;

class TrackPrivate;
class AC_CORE_EXPORT Track : public ScoreObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QString instrument READ instrument WRITE setInstrument)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(bool recording READ isRecording WRITE setRecording)

public:
    enum { Type = Ac::TrackItem };
    enum { ModelItemCount = ScoreObject::ModelItemCount + 1 };

    Track(QObject *parent = 0);

    Score *score() const;
    ObjectTList<Note> *notes() const;

    void setZValue(qreal z);

    // Properties
    const QColor &color() const;
    void setColor(const QColor &color);
    const QString &instrument() const;
    void setInstrument(const QString &instrument);
    bool isVisible() const;
    void setVisible(bool visible);
    bool isRecording() const;
    void setRecording(bool recording);

    // ScoreObject
    qreal length() const;

    // Object
    QString name() const { return objectName(); }

    // IModelItem
    int type() const { return Type; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(const IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItemList(int type) const;

    int persistentRoleAt(int i) const
    {
        switch (i - staticMetaObject.propertyOffset()) {
        case 0:
            return Ac::ColorRole;
        case 1:
            return Ac::InstrumentRole;
        case 2:
            return Ac::VisibilityRole;
        case 3:
            return Ac::RecordingRole;
        default:
            return ScoreObject::persistentRoleAt(i);
        }
    }

    QVariant data(int role) const;
    bool setData(const QVariant &value, int role);

private:
    Q_DECLARE_PRIVATE(Track)

    friend class NotePrivate;
};

class TrackPrivate : public ScoreObjectPrivate
{
    Q_DECLARE_PUBLIC(Track)

public:
    QColor color;
    QString instrument;
    ObjectTList<Note> *notes;
    int recording : 32;

    TrackPrivate(Track *q);
    void init();
    ~TrackPrivate();

    GraphicsParentPrivate *graphicsParent() const;
};

#endif // AC_TRACK_H
