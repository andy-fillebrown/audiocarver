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

#ifndef MI_COREDEFS_H
#define MI_COREDEFS_H

// IUNKNOWN  INTERFACETYPE

#define Q_IUNKNOWN_COMMON__INTERFACETYPE(Interface) \
        enum { InterfaceType = I::Interface }; \
    \
        int interfaceType() const \
        { \
            return InterfaceType; \
        } \

#define Q_IUNKNOWN_BASE__INTERFACETYPE(Interface) \
    Q_IUNKNOWN_COMMON__INTERFACETYPE(Interface) \
    \
        bool isTypeOfInterface(int interfaceType) const \
        { \
            return InterfaceType == interfaceType; \
        }

#define Q_IUNKNOWN_DERIVED__INTERFACETYPE(Interface, BaseInterface) \
    Q_IUNKNOWN_COMMON__INTERFACETYPE(Interface) \
    \
        bool isTypeOfInterface(int interfaceType) const \
        { \
            if (InterfaceType == interfaceType) \
                return true; \
            return BaseInterface::isTypeOfInterface(interfaceType); \
        }

// IAGGREGATOR

#define Q_IAGGREGATOR_COMMON(Class) \
    protected: \
        typedef Class A; \

#define Q_IAGGREGATOR_BASE(Class) \
    Q_IAGGREGATOR_COMMON(Class) \
    \
    public: \
        virtual IAggregator *init(); \
    \
    private:

#define Q_IAGGREGATOR_DERIVED(Class, BaseClass) \
    Q_IAGGREGATOR_COMMON(Class) \
    \
        typedef BaseClass Base; \
    \
    public: \
        IAggregator *init(); \
    \
    private:

// IAGGREGATOR  ROLECOUNT

#define Q_IAGGREGATOR_COMMON__ROLECOUNT(ClassRoleCount) \
    protected: \
        enum { RoleCount = ClassRoleCount }; \
    \
        static const int Roles[RoleCount];

#define Q_IAGGREGATOR_BASE__ROLECOUNT(ClassRoleCount) \
    Q_IAGGREGATOR_COMMON__ROLECOUNT(ClassRoleCount) \
    \
        enum { \
            RoleCountOffset = 0, \
            TotalRoleCount = RoleCount \
        }; \
    \
    private:

#define Q_IAGGREGATOR_DERIVED__ROLECOUNT(ClassRoleCount) \
    Q_IAGGREGATOR_COMMON__ROLECOUNT(ClassRoleCount) \
    \
        enum { \
            RoleCountOffset = Base::TotalRoleCount, \
            TotalRoleCount = RoleCountOffset + RoleCount \
        }; \
    \
    private: \

// IAGGREGATOR  ITEMCOUNT

#define Q_IAGGREGATOR_COMMON__ITEMCOUNT(ClassItemCount) \
    protected: \
        enum { ItemCount = ClassItemCount }; \
    \
        static const int ItemTypes[ItemCount]; \
        IAggregator *Items[ItemCount];

#define Q_IAGGREGATOR_BASE__ITEMCOUNT(ClassItemCount) \
    Q_IAGGREGATOR_COMMON__ITEMCOUNT(ClassItemCount) \
    \
        enum { \
            ItemCountOffset = 0, \
            TotalItemCount = ItemCount \
        }; \
    \
    private:

#define Q_IAGGREGATOR_DERIVED__ITEMCOUNT(ClassItemCount) \
    Q_IAGGREGATOR_COMMON__ITEMCOUNT(ClassItemCount) \
    \
        enum { \
            ItemCountOffset = Base::TotalItemCount, \
            TotalItemCount = ItemCountOffset + ItemCount \
        }; \
    \
    private:

// IAGGREGATE

#define Q_IAGGREGATE_COMMON \
    protected: \
    \
        A *a() const \
        { \
            return cast<A>(_a); \
        } \

#define Q_IAGGREGATE_COMMON_BASE \
    Q_IAGGREGATE_COMMON \
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

#define Q_IAGGREGATE_BASE_NOCONSTRUCTOR \
    Q_IAGGREGATE_COMMON_BASE

#define Q_IAGGREGATE_BASE(Class) \
    Q_IAGGREGATE_COMMON_BASE \
    \
    public: \
        Class(A *aggregator) \
            :   _a(aggregator) \
        {} \
    \
    protected:

#define Q_IAGGREGATE_COMMON_DERIVED(Class) \
    Q_IAGGREGATE_COMMON \
    \
        typedef A::Base::Class Base; \
    \
    public: \
        IAggregate* init(); \
    \
    protected:

#define Q_IAGGREGATE_DERIVED_NOCONSTRUCTOR(Class) \
    Q_IAGGREGATE_COMMON_DERIVED(Class)

#define Q_IAGGREGATE_DERIVED(Class) \
    Q_IAGGREGATE_COMMON_DERIVED(Class) \
    \
    public: \
        Class(A *aggregator) \
            :   Base(aggregator) \
        {} \
    \
    protected:

#define Q_IA(AggregatorClass) AggregatorClass *a = cast<AggregatorClass>(_a)

// IMODELDATA

#define Q_IMODELDATA_COMMON \

#define Q_IMODELDATA_BASE \
        IModelItem *_item; \
    \
    Q_IAGGREGATE_BASE_NOCONSTRUCTOR \
    Q_IMODELDATA_COMMON \
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

#define Q_IMODELDATA_DERIVED \
    Q_IAGGREGATE_DERIVED(ModelData) \
    Q_IMODELDATA_COMMON \

#define Q_IMODELDATA_BASE__ROLE_FUNCTIONS \
    Q_IMODELDATA_BASE__ROLECOUNT \
    Q_IMODELDATA_BASE__ROLEAT

#define Q_IMODELDATA_DERIVED__ROLE_FUNCTIONS \
    Q_IMODELDATA_DERIVED__ROLECOUNT \
    Q_IMODELDATA_DERIVED__ROLEAT

// IMODELDATA  ROLECOUNT

#define Q_IMODELDATA_BASE__ROLECOUNT \
        int roleCount() const \
        { \
            return TotalRoleCount; \
        } \

#define Q_IMODELDATA_DERIVED__ROLECOUNT \
    Q_IMODELDATA_BASE__ROLECOUNT

// IMODELDATA  ROLEAT

#define Q_IMODELDATA_BASE__ROLEAT \
        int roleAt(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            Q_ASSERT(i < RoleCount); \
            if (i < 0 || RoleCount <= i) \
                return -1; \
            return Roles[i]; \
        }

#define Q_IMODELDATA_DERIVED__ROLEAT \
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

// IMODELITEM

#define Q_IMODELITEM_BASE \
    Q_IAGGREGATE_BASE(ModelItem) \
    Q_IMODELITEM_BASE__PARENT \

#define Q_IMODELITEM_DERIVED \
    Q_IAGGREGATE_DERIVED(ModelItem)

#define Q_IMODELITEM_BASE__ITEM_FUNCTIONS \
    Q_IMODELITEM_BASE__COUNT \
    Q_IMODELITEM_BASE__INDEXOF \
    Q_IMODELITEM_BASE__AT \

#define Q_IMODELITEM_DERIVED__ITEM_FUNCTIONS \
    Q_IMODELITEM_DERIVED__COUNT \
    Q_IMODELITEM_DERIVED__INDEXOF \
    Q_IMODELITEM_DERIVED__AT \

#define Q_IMODELITEM_BASE__FIND_FUNCTIONS \
    Q_I_BASE__MODEL_ITEM__FIND_ITEM \
    Q_I_BASE__MODEL_ITEM__FIND_LIST \

#define Q_IMODELITEM_DERIVED__FIND_FUNCTIONS \
    Q_IMODELITEM_DERIVED__FINDITEM \
    Q_IMODELITEM_DERIVED__FINDLIST \

#define Q_IMODELITEM_BASE__FUNCTIONS \
    Q_IMODELITEM_BASE__ITEM_FUNCTIONS \
    Q_IMODELITEM_BASE__FIND_FUNCTIONS \

#define Q_IMODELITEM_DERIVED__FUNCTIONS \
    Q_IMODELITEM_DERIVED__ITEM_FUNCTIONS \
    Q_IMODELITEM_DERIVED__FIND_FUNCTIONS \

// IMODELITEM  PARENT

#define Q_IMODELITEM_BASE__PARENT \
        IModelItem *parent() const \
        { \
            return query<IModelItem>(a()->parent()); \
        }

// IMODELITEM  ITEMTYPE

#define Q_IMODELITEM_COMMON__ITEMTYPE(ClassItemType) \
        enum { ItemType = ClassItemType }; \
    \
        int itemType() const \
        { \
            return ItemType; \
        }

#define Q_IMODELITEM_BASE__ITEMTYPE(ClassItemType) \
    Q_IMODELITEM_COMMON__ITEMTYPE(ClassItemType) \
    \
        bool isTypeOfItem(int itemType) const \
        { \
            return ItemType == itemType; \
        }

#define Q_IMODELITEM_DERIVED__ITEMTYPE(ClassItemType) \
    Q_IMODELITEM_COMMON__ITEMTYPE(ClassItemType) \
    \
        bool isTypeOfItem(int itemType) const \
        { \
            if (ItemType == itemType) \
                return true; \
            return Base::isTypeOfItem(itemType); \
        }

// IMODELITEM  COUNT

#define Q_IMODELITEM_BASE__COUNT \
        int count() const \
        { \
            return A::TotalItemCount; \
        }

#define Q_IMODELITEM_DERIVED__COUNT \
    Q_IMODELITEM_BASE__COUNT

// IMODELITEM  INDEXOF

#define Q_IMODELITEM_COMMON__INDEXOF(Return) \
        int indexOf(const IModelItem *item) const \
        { \
            Q_IA(const A); \
            const IAggregator *item_a = item->aggregator(); \
            for (int i = 0;  i < ItemCount;  ++i) \
                if (a->Items[i] == item_a) \
                    return ItemCountOffset + i; \
            Return; \
        }

#define Q_IMODELITEM_BASE__INDEXOF \
    Q_IMODELITEM_COMMON__INDEXOF(return -1)

#define Q_IMODELITEM_DERIVED__INDEXOF \
    Q_IMODELITEM_COMMON__INDEXOF(return Base::indexOf(item))

// IMODELITEM  AT

#define Q_IMODELITEM_COMMON__AT(Return) \
        IModelItem *at(int i) const \
        { \
            Q_ASSERT(0 <= i); \
            if (i < TotalItemCount) \
                return query<IModelItem>(a()->Items[i - ItemCountOffset]); \
            Return; \
        }

#define Q_IMODELITEM_BASE__AT \
    Q_IMODELITEM_COMMON__AT(return 0)

#define Q_IMODELITEM_DERIVED__AT \
    Q_IMODELITEM_COMMON__AT(return Base::at(i))

// IMODELITEM  FINDITEM

#define Q_IMODELITEM_COMMON__FINDITEM(Return) \
        IModelItem *findItem(int itemType) const \
        { \
            Q_IA(const A); \
            for (int i = 0;  i < ItemCount;  ++i) \
                if (itemType == a->ItemTypes[i]) \
                    return query<IModelItem>(a->Items[i]); \
            Return; \
        }

#define Q_IMODELITEM_BASE__FINDITEM \
    Q_IMODELITEM_COMMON__FINDITEM(return 0)

#define Q_IMODELITEM_DERIVED__FINDITEM \
    Q_IMODELITEM_COMMON__FINDITEM(return Base::findItem(itemType))

// IMODELITEM  FINDLIST

#define Q_IMODELITEM_COMMON__FINDLIST(Return) \
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

#define Q_IMODELITEM_BASE__FINDLIST \
    Q_IMODELITEM_COMMON__FINDLIST(return 0)

#define Q_IMODELITEM_DERIVED__FINDLIST \
    Q_IMODELITEM_COMMON__FINDLIST(return Base::findList(listType))

// IMODELLIST

#define Q_IMODELLIST_BASE \
    Q_IAGGREGATE_BASE(ModelList) \
    Q_IMODELITEM_BASE__PARENT

#define Q_IMODELLIST_DERIVED \
    Q_IAGGREGATE_DERIVED(ModelList)

// NEW

#define Q_NEW_AGGREGATE(Class) appendAggregate((new Class(this))->init())
#define Q_NEW_OBJECT(Class) (new Class)->init()
#define Q_NEW_OBJECTLIST(Class, ItemType) (new Class(ItemType))->init()

// IAGGREGATOR  INIT

#define Q_IAGGREGATOR_INIT_ROLES(Class) \
    const int Class::Roles[]

#define Q_IAGGREGATOR_INIT_ITEMTYPES(Class) \
    const int Class::ItemTypes[]

#define Q_IAGGREGATOR_INIT_ITEMLIST__INITIALIZER \
    IAggregator *items[ItemCount]

#define Q_IAGGREGATOR_INIT_ITEMLIST \
    for (int i = 0;  i < ItemCount;  ++i) { \
        IAggregator *item = items[i]; \
        Items[i] = item; \
        Object *object = cast<Object>(item); \
        if (object) \
            object->setParent(this); \
    }

#endif // MI_COREDEFS_H
