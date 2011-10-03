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

#ifndef AC_GRIDSETTINGS_H
#define AC_GRIDSETTINGS_H

#include <ac_graphicsparent.h>
#include <ac_objectlist.h>

class ControlGridLine;
class PitchGridLine;
class Score;
class TimeGridLine;

class GridSettingsPrivate;
class AC_CORE_EXPORT GridSettings : public GraphicsParent
{
    Q_OBJECT

public:
    enum { ModelItemCount = 3 };

    explicit GridSettings(QObject *parent = 0);

    Score *score() const;

    ObjectList<TimeGridLine> *timeGridLines() const;
    ObjectList<PitchGridLine> *pitchGridLines() const;
    ObjectList<ControlGridLine> *controlGridLines() const;

    // IModelItem
    Ac::ItemType type() const { return Ac::GridSettingsItem; }
    int modelItemCount() const { return ModelItemCount; }
    int modelItemIndex(IModelItem *item) const;
    IModelItem *modelItemAt(int i) const;
    IModelItem *findModelItemList(Ac::ItemType type) const;

private:
    Q_DISABLE_COPY(GridSettings)
    Q_DECLARE_PRIVATE(GridSettings)

    friend class GridLinePrivate;
};

class GridSettingsPrivate : public GraphicsParentPrivate
{
    Q_DECLARE_PUBLIC(GridSettings)

public:
    ObjectList<TimeGridLine> *timeGridLines;
    ObjectList<PitchGridLine> *pitchGridLines;
    ObjectList<ControlGridLine> *controlGridLines;

    GridSettingsPrivate(GridSettings *q);
    void init();
    ~GridSettingsPrivate();

    GraphicsParentPrivate *graphicsParent() const;
};

#endif // AC_GRIDSETTINGS_H
