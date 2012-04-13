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

#ifndef MI_GLOBALINTERFACE_H
#define MI_GLOBALINTERFACE_H

// UNKNOWN__INTERFACE_TYPE

#define Q_I_COMMON__UNKNOWN__INTERFACE_TYPE(Interface) \
        enum { InterfaceType = I::Interface }; \
    \
        int interfaceType() const \
        { \
            return InterfaceType; \
        } \

#define Q_I_BASE__UNKNOWN__INTERFACE_TYPE(Interface) \
    Q_I_COMMON__UNKNOWN__INTERFACE_TYPE(Interface) \
    \
        bool isTypeOfInterface(int interfaceType) const \
        { \
            return InterfaceType == interfaceType; \
        }

#define Q_I_DERIVED__UNKNOWN__INTERFACE_TYPE(Interface, BaseInterface) \
    Q_I_COMMON__UNKNOWN__INTERFACE_TYPE(Interface) \
    \
        bool isTypeOfInterface(int interfaceType) const \
        { \
            if (InterfaceType == interfaceType) \
                return true; \
            return BaseInterface::isTypeOfInterface(interfaceType); \
        }


#define Q_I_COMMON__AGGREGATOR(Class) \
    protected: \
        typedef Class A; \

#define Q_I_BASE__AGGREGATOR(Class) \
    Q_I_COMMON__AGGREGATOR(Class) \
    \
    public: \
        virtual IAggregator *init(); \
    \
    private:

#define Q_I_DERIVED__AGGREGATOR(Class, BaseClass) \
    Q_I_COMMON__AGGREGATOR(Class) \
    \
        typedef BaseClass Base; \
    \
    public: \
        IAggregator *init(); \
    \
    private:

// AGGREGATOR__ROLE_COUNT

#define Q_I_COMMON__AGGREGATOR__ROLE_COUNT(ClassRoleCount) \
    protected: \
        enum { RoleCount = ClassRoleCount }; \
    \
        static const int Roles[RoleCount];

#define Q_I_BASE__AGGREGATOR__ROLE_COUNT(ClassRoleCount) \
    Q_I_COMMON__AGGREGATOR__ROLE_COUNT(ClassRoleCount) \
    \
        enum { \
            RoleCountOffset = 0, \
            TotalRoleCount = RoleCount \
        }; \
    \
    private:

#define Q_I_DERIVED__AGGREGATOR__ROLE_COUNT(ClassRoleCount) \
    Q_I_COMMON__AGGREGATOR__ROLE_COUNT(ClassRoleCount) \
    \
        enum { \
            RoleCountOffset = Base::TotalRoleCount, \
            TotalRoleCount = RoleCountOffset + RoleCount \
        }; \
    \
    private: \

// AGGREGATOR__ITEM_COUNT

#define Q_I_COMMON__AGGREGATOR__ITEM_COUNT(ClassItemCount) \
    protected: \
        enum { ItemCount = ClassItemCount }; \
    \
        static const int ItemTypes[ItemCount]; \
        IAggregator *Items[ItemCount];

#define Q_I_BASE__AGGREGATOR__ITEM_COUNT(ClassItemCount) \
    Q_I_COMMON__AGGREGATOR__ITEM_COUNT(ClassItemCount) \
    \
        enum { \
            ItemCountOffset = 0, \
            TotalItemCount = ItemCount \
        }; \
    \
    private:

#define Q_I_DERIVED__AGGREGATOR__ITEM_COUNT(ClassItemCount) \
    Q_I_COMMON__AGGREGATOR__ITEM_COUNT(ClassItemCount) \
    \
        enum { \
            ItemCountOffset = Base::TotalItemCount, \
            TotalItemCount = ItemCountOffset + ItemCount \
        }; \
    \
    private:

// INIT__AGGREGATOR

#define Q_I_INIT__AGGREGATOR__ROLES(Class) \
    const int Class::Roles[] =

#define Q_I_INIT__AGGREGATOR__ITEM_TYPES(Class) \
    const int Class::ItemTypes[] =

#define Q_I_INIT__AGGREGATOR__ITEM_LIST(ItemListInitializer) \
    DataObject *init_items[ItemCount] = { ItemListInitializer }; \
    for (int i = 0;  i < ItemCount;  ++i) \
        Items[i] = init_items[i]; \

// CREATE

#define Q_I_CREATE(Class) (new Class)->init()
#define Q_I_CREATE__AGGREGATOR(Class) Q_I_CREATE(Class)
#define Q_I_CREATE__AGGREGATE(Class) appendAggregate(Q_I_CREATE(Class(this)))

// AGGREGATE

#define Q_I_COMMON__AGGREGATE \
    protected: \
    \
        A *a() const \
        { \
            return cast<A>(_a); \
        } \

#define Q_I_BASE_COMMON__AGGREGATE \
    Q_I_COMMON__AGGREGATE \
    \
        IAggregator *_a; \
    \
        IAggregator *aggregator() const \
        { \
            return _a; \
        } \
    \
    public: \
        virtual IAggregate* init(); \
    \
    protected:

#define Q_I_BASE__AGGREGATE__NO_CONSTRUCTOR \
    Q_I_BASE_COMMON__AGGREGATE

#define Q_I_BASE__AGGREGATE(Class) \
    Q_I_BASE_COMMON__AGGREGATE \
    \
    public: \
        Class(A *aggregator) \
            :   _a(aggregator) \
        {} \
    \
    protected:

#define Q_I_DERIVED_COMMON__AGGREGATE(Class) \
    Q_I_COMMON__AGGREGATE \
    \
        typedef A::Base::Class Base; \
    \
    public: \
        IAggregate* init(); \
    \
    protected:

#define Q_I_DERIVED__AGGREGATE__NO_CONSTRUCTOR(Class) \
    Q_I_DERIVED_COMMON__AGGREGATE(Class)

#define Q_I_DERIVED__AGGREGATE(Class) \
    Q_I_DERIVED_COMMON__AGGREGATE(Class) \
    \
    public: \
        Class(A *aggregator) \
            :   Base(aggregator) \
        {} \
    \
    protected:

#define Q_IA(AggregatorClass) AggregatorClass *a = cast<AggregatorClass>(_a)

// MODEL_DATA

#define Q_I_COMMON__MODEL_DATA \

#define Q_I_BASE__MODEL_DATA \
        IModelItem *_item; \
    \
    Q_I_BASE__AGGREGATE__NO_CONSTRUCTOR \
    Q_I_COMMON__MODEL_DATA \
    \
        Qt::ItemFlags flags() const \
        { \
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable; \
        } \
    \
    public: \
        ModelData(A *aggregator) \
            :   _item(0) \
            ,   _a(aggregator) \
        {} \
    \
    protected: \
        IModelItem *item() const \
        { \
            return _item; \
        } \

#define Q_I_DERIVED__MODEL_DATA \
    Q_I_DERIVED__AGGREGATE(ModelData) \
    Q_I_COMMON__MODEL_DATA \

#define Q_I_BASE__MODEL_DATA__ROLE_FUNCTIONS \
    Q_I_BASE__MODEL_DATA__ROLE_COUNT \
    Q_I_BASE__MODEL_DATA__ROLE_AT

#define Q_I_DERIVED__MODEL_DATA__ROLE_FUNCTIONS \
    Q_I_DERIVED__MODEL_DATA__ROLE_COUNT \
    Q_I_DERIVED__MODEL_DATA__ROLE_AT

// MODEL_DATA__ROLE_COUNT

#define Q_I_BASE__MODEL_DATA__ROLE_COUNT \
        int roleCount() const \
        { \
            return TotalRoleCount; \
        } \

#define Q_I_DERIVED__MODEL_DATA__ROLE_COUNT \
    Q_I_BASE__MODEL_DATA__ROLE_COUNT

// MODEL_DATA__ROLE_AT

#define Q_I_BASE__MODEL_DATA__ROLE_AT \
        int roleAt(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            Q_ASSERT(i < RoleCount); \
            if (i < 0 || RoleCount <= i) \
                return -1; \
            return Roles[i]; \
        }

#define Q_I_DERIVED__MODEL_DATA__ROLE_AT \
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

// MODEL_ITEM

#define Q_I_BASE__MODEL_ITEM \
    Q_I_BASE__AGGREGATE(ModelItem) \
    Q_I_BASE__MODEL_ITEM__PARENT \

#define Q_I_DERIVED__MODEL_ITEM \
    Q_I_DERIVED__AGGREGATE(ModelItem)

#define Q_I_BASE__MODEL_ITEM__ALL_ITEM_FUNCTIONS \
    Q_I_BASE__MODEL_ITEM__COUNT \
    Q_I_BASE__MODEL_ITEM__INDEX_OF \
    Q_I_BASE__MODEL_ITEM__AT \

#define Q_I_DERIVED__MODEL_ITEM__ALL_ITEM_FUNCTIONS \
    Q_I_DERIVED__MODEL_ITEM__COUNT \
    Q_I_DERIVED__MODEL_ITEM__INDEX_OF \
    Q_I_DERIVED__MODEL_ITEM__AT \

#define Q_I_BASE__MODEL_ITEM__ALL_FIND_FUNCTIONS \
    Q_I_BASE__MODEL_ITEM__FIND_ITEM \
    Q_I_BASE__MODEL_ITEM__FIND_LIST \

#define Q_I_DERIVED__MODEL_ITEM__ALL_FIND_FUNCTIONS \
    Q_I_DERIVED__MODEL_ITEM__FIND_ITEM \
    Q_I_DERIVED__MODEL_ITEM__FIND_LIST \

#define Q_I_BASE__MODEL_ITEM__ALL_FUNCTIONS \
    Q_I_BASE__MODEL_ITEM__ALL_ITEM_FUNCTIONS \
    Q_I_BASE__MODEL_ITEM__ALL_FIND_FUNCTIONS \

#define Q_I_DERIVED__MODEL_ITEM__ALL_FUNCTIONS \
    Q_I_DERIVED__MODEL_ITEM__ALL_ITEM_FUNCTIONS \
    Q_I_DERIVED__MODEL_ITEM__ALL_FIND_FUNCTIONS \

// MODEL_ITEM__PARENT

#define Q_I_BASE__MODEL_ITEM__PARENT \
        IModelItem *parent() const \
        { \
            return query<IModelItem>(a()->parent()); \
        }

// MODEL_ITEM__ITEM_TYPE

#define Q_I_COMMON__MODEL_ITEM__ITEM_TYPE(ClassItemType) \
        enum { ItemType = ClassItemType }; \
    \
        int itemType() const \
        { \
            return ItemType; \
        }

#define Q_I_BASE__MODEL_ITEM__ITEM_TYPE(ClassItemType) \
    Q_I_COMMON__MODEL_ITEM__ITEM_TYPE(ClassItemType) \
    \
        bool isTypeOfItem(int itemType) const \
        { \
            return ItemType == itemType; \
        }

#define Q_I_DERIVED__MODEL_ITEM__ITEM_TYPE(ClassItemType) \
    Q_I_COMMON__MODEL_ITEM__ITEM_TYPE(ClassItemType) \
    \
        bool isTypeOfItem(int itemType) const \
        { \
            if (ItemType == itemType) \
                return true; \
            return Base::isTypeOfItem(itemType); \
        }

// MODEL_ITEM__COUNT

#define Q_I_BASE__MODEL_ITEM__COUNT \
        int count() const \
        { \
            return A::TotalItemCount; \
        }

#define Q_I_DERIVED__MODEL_ITEM__COUNT \
    Q_I_BASE__MODEL_ITEM__COUNT

// MODEL_ITEM__INDEX_OF

#define Q_I_COMMON__MODEL_ITEM__INDEX_OF(Return) \
        int indexOf(const IModelItem *item) const \
        { \
            Q_IA(const A); \
            const IAggregator *item_a = item->aggregator(); \
            for (int i = 0;  i < ItemCount;  ++i) \
                if (a->Items[i] == item_a) \
                    return ItemCountOffset + i; \
            Return; \
        }

#define Q_I_BASE__MODEL_ITEM__INDEX_OF \
    Q_I_COMMON__MODEL_ITEM__INDEX_OF(return -1)

#define Q_I_DERIVED__MODEL_ITEM__INDEX_OF \
    Q_I_COMMON__MODEL_ITEM__INDEX_OF(return Base::indexOf(item))

// MODEL_ITEM__AT

#define Q_I_COMMON__MODEL_ITEM__AT(Return) \
        IModelItem *at(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            if (i < TotalItemCount) \
                return query<IModelItem>(a()->Items[i - ItemCountOffset]); \
            Return; \
        }

#define Q_I_BASE__MODEL_ITEM__AT \
    Q_I_COMMON__MODEL_ITEM__AT(return 0)

#define Q_I_DERIVED__MODEL_ITEM__AT \
    Q_I_COMMON__MODEL_ITEM__AT(return Base::at(i))

// MODEL_ITEM__FIND_ITEM

#define Q_I_COMMON__MODEL_ITEM__FIND_ITEM(Return) \
        IModelItem *findItem(int itemType) const \
        { \
            Q_IA(const A); \
            for (int i = 0;  i < ItemCount;  ++i) \
                if (itemType == a->ItemTypes[i]) \
                    return query<IModelItem>(a->Items[i]); \
            Return; \
        }

#define Q_I_BASE__MODEL_ITEM__FIND_ITEM \
    Q_I_COMMON__MODEL_ITEM__FIND_ITEM(return 0)

#define Q_I_DERIVED__MODEL_ITEM__FIND_ITEM \
    Q_I_COMMON__MODEL_ITEM__FIND_ITEM(return Base::findItem(itemType))

// MODEL_ITEM__FIND_LIST

#define Q_I_COMMON__MODEL_ITEM__FIND_LIST(Return) \
        IModelList *findList(int listType) const \
        { \
            Q_IA(const A); \
            for (int i = 0;  i < ItemCount;  ++i) { \
                if (Mi::ListItem == a->ItemTypes[i]) { \
                    IModelList *list = query<IModelList>(a->Items[i]); \
                    if (listType == list->listType()) \
                        return list; \
                } \
            } \
            Return; \
        }

#define Q_I_BASE__MODEL_ITEM__FIND_LIST \
    Q_I_COMMON__MODEL_ITEM__FIND_LIST(return 0)

#define Q_I_DERIVED__MODEL_ITEM__FIND_LIST \
    Q_I_COMMON__MODEL_ITEM__FIND_LIST(return Base::findList(listType))

// MODEL_LIST

#define Q_I_BASE__MODEL_LIST \
    Q_I_BASE__AGGREGATE(ModelList) \
    Q_I_BASE__MODEL_ITEM__PARENT

#define Q_I_DERIVED__MODEL_LIST \
    Q_I_DERIVED__AGGREGATE(ModelList)

/*
// MODEL_ITEM__PARENT

#define Q_I_BASE__MODEL_LIST__PARENT \
        IModelItem *parent() const \
        { \
            DataObject *a_parent = a()->parent(); \
            return a_parent ? query<IModelItem>(a_parent) : 0; \
        }
*/

#endif // MI_GLOBALINTERFACE_H
