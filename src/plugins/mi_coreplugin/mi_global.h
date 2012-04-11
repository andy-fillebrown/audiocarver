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

#ifndef MI_GLOBAL_H
#define MI_GLOBAL_H

#include <qglobal.h>
#include <QDebug>

#if defined(MI_CORE_LIBRARY)
#  define MI_CORE_EXPORT Q_DECL_EXPORT
#else
#  define MI_CORE_EXPORT Q_DECL_IMPORT
#endif

#if defined(MI_GUI_LIBRARY)
#  define MI_GUI_EXPORT Q_DECL_EXPORT
#else
#  define MI_GUI_EXPORT Q_DECL_IMPORT
#endif

inline void mi_assert(const char *assertion, const char *file, int line)
{
    qDebug("ASSERT: \"%s\" in file %s, line %d", assertion, file, line);
    qt_assert(assertion, file, line);
}

#ifdef USE_MI_ASSERT
#  ifdef Q_ASSERT
#    undef Q_ASSERT
#  endif
#  ifndef QT_NO_DEBUG
#    define Q_ASSERT(cond) ((!(cond)) ? mi_assert(#cond,__FILE__,__LINE__) : qt_noop())
#  else
#    define Q_ASSERT(cond) qt_noop()
#  endif
#endif

#define Q_DECLARE_PRIVATE_TEMPLATE(Class) \
    inline Class##Private<T> *d_func() \
    { \
        return reinterpret_cast<Class##Private<T>*>(qGetPtrHelper(d_ptr)); \
    } \
    \
    inline const Class##Private<T> *d_func() const \
    { \
        return reinterpret_cast<const Class##Private<T>*>(qGetPtrHelper(d_ptr)); \
    } \
    \
    friend class Class##Private<T>;

#define Q_DECLARE_PUBLIC_TEMPLATE(Class) \
    inline Class<T> *q_func() \
    { \
        return static_cast<Class<T>*>(this->q_ptr); \
    } \
    \
    inline const Class<T> *q_func() const \
    { \
        return static_cast<const Class<T>*>(this->q_ptr); \
    } \
    \
    friend class Class<T>;

#define Q_TD(Class) Class##Private<T> *const d = d_func()
#define Q_TQ(Class) Class<T> *const q = q_func()

#define Q_COMMON_ROLECOUNT_DECLARATIONS(ClassRoleCount) \
    protected: \
        enum { RoleCount = ClassRoleCount }; \
        \
        static const int Roles[RoleCount];

#define Q_DECLARE_BASE_ROLECOUNT(ClassRoleCount) \
    Q_COMMON_ROLECOUNT_DECLARATIONS(ClassRoleCount) \
    \
        enum { \
            RoleCountOffset = 0, \
            TotalRoleCount = RoleCount \
        };

#define Q_DECLARE_ROLECOUNT(ClassRoleCount) \
    Q_COMMON_ROLECOUNT_DECLARATIONS(ClassRoleCount) \
    \
        enum { \
            RoleCountOffset = Base::TotalRoleCount, \
            TotalRoleCount = RoleCountOffset + RoleCount \
        };

#define Q_COMMON_ITEMCOUNT_DECLARATIONS(ClassItemCount) \
        enum { ItemCount = ClassItemCount }; \
        \
        static const int ItemTypes[ItemCount]; \
        IAggregator *Items[ItemCount];

#define Q_DECLARE_BASE_ITEMCOUNT(ClassItemCount) \
    Q_COMMON_ITEMCOUNT_DECLARATIONS(ClassItemCount) \
    \
        enum { \
            ItemCountOffset = 0, \
            TotalItemCount = ItemCount \
        };

#define Q_DECLARE_ITEMCOUNT(ClassItemCount) \
    Q_COMMON_ITEMCOUNT_DECLARATIONS(ClassItemCount) \
    \
        enum { \
            ItemCountOffset = Base::TotalItemCount, \
            TotalItemCount = ItemCountOffset + ItemCount \
        };

#define Q_COMMON_AGGREGATOR_DECLARATIONS(Class) \
    protected: \
        typedef Class A; \

#define Q_DECLARE_BASE_AGGREGATOR(Class) \
    Q_COMMON_AGGREGATOR_DECLARATIONS(Class) \
    \
        virtual IAggregator *init(); \
    \
    private:

#define Q_DECLARE_AGGREGATOR(Class, BaseClass) \
    Q_COMMON_AGGREGATOR_DECLARATIONS(Class) \
    \
        typedef BaseClass Base; \
        \
        IAggregator *init(); \
    \
    private:

#define Q_INIT_ROLES(Class) \
    const int Class::Roles[] =

#define Q_INIT_ITEMTYPES(Class) \
    const int Class::ItemTypes[] =

#define Q_INIT_ITEMLIST(ItemListInitializer) \
    DataObject *init_items[ItemCount] = { ItemListInitializer }; \
    for (int i = 0;  i < ItemCount;  ++i) \
        Items[i] = init_items[i]; \

#define Q_DECLARE_BASE_AGGREGATE(Class) \
    protected: \
        A *_a; \
        \
        A *a() const \
        { \
            return _a; \
        } \
        \
        IAggregator *aggregator() const \
        { \
            return _a; \
        } \
        \
    public: \
        Class(A *aggregator) \
            :   _a(aggregator) \
        {} \
        \
        virtual IAggregate* init(); \
        \
    protected:

#define Q_DECLARE_AGGREGATE(Class) \
    protected: \
        typedef A::Base::Class Base; \
        \
        A *a() const \
        { \
            return cast<A>(_a); \
        } \
        \
    public: \
        Class(A *aggregator) \
            :   Base(aggregator) \
        {} \
        \
        IAggregate* init(); \
        \
    protected:

#define Q_A(AggregatorClass) AggregatorClass *a = cast<AggregatorClass>(_a)

#define Q_CREATE(Class) (new Class)->init()
#define Q_CREATE_AGGREGATE(Class) Q_CREATE(Class(this))

#define Q_COMMON_MODELDATA_DECLARATIONS \

#define Q_DECLARE_BASE_MODELDATA \
    Q_DECLARE_BASE_AGGREGATE(ModelData) \
    Q_COMMON_MODELDATA_DECLARATIONS \
    \
        Qt::ItemFlags flags() const \
        { \
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable; \
        }

#define Q_DECLARE_MODELDATA \
    Q_DECLARE_AGGREGATE(ModelData) \
    Q_COMMON_MODELDATA_DECLARATIONS \

#define Q_DECLARE_MODELDATA_ROLECOUNT \
        int roleCount() const \
        { \
            return TotalRoleCount; \
        } \

#define Q_DECLARE_BASE_MODELDATA_ROLEAT \
        int roleAt(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            Q_ASSERT(i < RoleCount); \
            if (i < 0 || RoleCount <= i) \
                return -1; \
            return Roles[i]; \
        }

#define Q_DECLARE_MODELDATA_ROLEAT \
        int roleAt(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            Q_ASSERT(i < TotalRoleCount); \
            if (i < 0 || TotalRoleCount <= i) \
                return -1; \
            const int j = i - RoleCountOffset; \
            if (j < 0 || RoleCount <= j) \
                return -1; \
            if (j < RoleCount) \
                return Roles[j]; \
            return Base::roleAt(i); \
        }

#define Q_DECLARE_BASE_MODELDATA_FUNCTIONS \
    Q_DECLARE_MODELDATA_ROLECOUNT \
    Q_DECLARE_BASE_MODELDATA_ROLEAT

#define Q_DECLARE_MODELDATA_FUNCTIONS \
    Q_DECLARE_MODELDATA_ROLECOUNT \
    Q_DECLARE_MODELDATA_ROLEAT

#define Q_DECLARE_BASE_MODELITEM \
    Q_DECLARE_BASE_AGGREGATE(ModelItem)

#define Q_DECLARE_MODELITEM \
    Q_DECLARE_AGGREGATE(ModelItem)

#define Q_COMMON_MODELITEM_ITEMTYPE_DECLARATIONS(ClassItemType) \
        enum { ItemType = ClassItemType }; \
        \
        int itemType() const \
        { \
            return ItemType; \
        }

#define Q_DECLARE_BASE_MODELITEM_ITEMTYPE(ClassItemType) \
    Q_COMMON_MODELITEM_ITEMTYPE_DECLARATIONS(ClassItemType) \
    \
        bool isTypeOfItem(int itemType) const \
        { \
            return ItemType == itemType; \
        }

#define Q_DECLARE_MODELITEM_ITEMTYPE(ClassItemType) \
    Q_COMMON_MODELITEM_ITEMTYPE_DECLARATIONS(ClassItemType) \
    \
        bool isTypeOfItem(int itemType) const \
        { \
            if (ItemType == itemType) \
                return true; \
            return Base::isTypeOfItem(itemType); \
        }

#define Q_DECLARE_MODELITEM_COUNT \
        int count() const \
        { \
            return A::TotalItemCount; \
        }

#define Q_COMMON_MODELITEM_INDEXOF_DECLARATIONS(Return) \
        int indexOf(IModelItem *item) const \
        { \
            Q_A(const A); \
            const IAggregator *item_a = item->aggregator(); \
            for (int i = 0;  i < ItemCount;  ++i) \
                if (a->Items[i] == item_a) \
                    return ItemCountOffset + i; \
            Return; \
        }

#define Q_DECLARE_BASE_MODELITEM_INDEXOF \
    Q_COMMON_MODELITEM_INDEXOF_DECLARATIONS(return -1)

#define Q_DECLARE_MODELITEM_INDEXOF \
    Q_COMMON_MODELITEM_INDEXOF_DECLARATIONS(return Base::indexOf(item))

#define Q_COMMON_MODELITEM_AT_DECLARATIONS(Return) \
        IModelItem *at(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            if (i < TotalItemCount) \
                return query<IModelItem>(a()->Items[i - ItemCountOffset]); \
            Return; \
        }

#define Q_DECLARE_BASE_MODELITEM_AT \
    Q_COMMON_MODELITEM_AT_DECLARATIONS(return 0)

#define Q_DECLARE_MODELITEM_AT \
    Q_COMMON_MODELITEM_AT_DECLARATIONS(return Base::at(i))

#define Q_COMMON_MODELITEM_FINDITEM_DECLARATIONS(Return) \
        IModelItem *findItem(int itemType) const \
        { \
            Q_A(const A); \
            for (int i = 0;  i < ItemCount;  ++i) \
                if (itemType == a->ItemTypes[i]) \
                    return query<IModelItem>(a->Items[i]); \
            Return; \
        }

#define Q_DECLARE_BASE_MODELITEM_FINDITEM \
    Q_COMMON_MODELITEM_FINDITEM_DECLARATIONS(return 0)

#define Q_DECLARE_MODELITEM_FINDITEM \
    Q_COMMON_MODELITEM_FINDITEM_DECLARATIONS(return Base::findItem(itemType))

#define Q_COMMON_MODELITEM_FINDLIST_DECLARATIONS(Return) \
        IModelList *findList(int listType) const \
        { \
            Q_A(const A); \
            for (int i = 0;  i < ItemCount;  ++i) { \
                if (Mi::ListItem == a->ItemTypes[i]) { \
                    IModelList *list = query<IModelList>(a->Items[i]); \
                    if (listType == list->listType()) \
                        return list; \
                } \
            } \
            Return; \
        }

#define Q_DECLARE_BASE_MODELITEM_FINDLIST \
    Q_COMMON_MODELITEM_FINDLIST_DECLARATIONS(return 0)

#define Q_DECLARE_MODELITEM_FINDLIST \
    Q_COMMON_MODELITEM_FINDLIST_DECLARATIONS(return Base::findList(listType))

#define Q_DECLARE_BASE_MODELITEM_FUNCTIONS \
    Q_DECLARE_MODELITEM_COUNT \
    Q_DECLARE_BASE_MODELITEM_INDEXOF \
    Q_DECLARE_BASE_MODELITEM_AT \
    Q_DECLARE_BASE_MODELITEM_FINDITEM \
    Q_DECLARE_BASE_MODELITEM_FINDLIST \

#define Q_DECLARE_MODELITEM_FUNCTIONS \
    Q_DECLARE_MODELITEM_COUNT \
    Q_DECLARE_MODELITEM_INDEXOF \
    Q_DECLARE_MODELITEM_AT \
    Q_DECLARE_MODELITEM_FINDITEM \
    Q_DECLARE_MODELITEM_FINDLIST \

#define Q_DECLARE_BASE_MODELLIST \
    Q_DECLARE_BASE_AGGREGATE(ModelList)

template <typename Container, typename LessThan>
void qSort(Container &c, LessThan lessThan)
{
    qSort(c.begin(), c.end(), lessThan);
}

template <typename T, typename Object>
T *object_cast(Object *object)
{
    return qobject_cast<T*>(object);
}

template <typename T, typename Object>
T *object_cast(const Object *object)
{
    return qobject_cast<T*>(object);
}

#ifdef Q_MI_NO_REINTERPRET_CAST
#   define mi_cast static_cast
#else
#   define mi_cast reinterpret_cast
#endif

template <typename T, typename Object>
T *cast(Object *object)
{
    return mi_cast<T*>(object);
}

template <typename T, typename Object>
const T *cast(const Object *object)
{
    return mi_cast<const T*>(object);
}

#define bitcountof(x) (8 * sizeof(x))

#define Q_FLOAT_MIN 1E-37
#define Q_FLOAT_MAX 1E+37

#endif // MI_GLOBAL_H
