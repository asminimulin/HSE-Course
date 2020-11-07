#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase {
    using NewTypeList = NullType;
};

template<typename TargetType>
struct Erase<NullType, TargetType> {
    using NewTypeList = NullType;
};

template<typename Head, typename Tail, typename TargetType>
struct Erase<TypeList<Head, Tail>, TargetType> {
    using NewTypeList = TypeList<Head, typename Erase<Tail, TargetType>::NewTypeList>;
};

template<typename Head, typename Tail>
struct Erase<TypeList<Head, Tail>, Head> {
    using NewTypeList = Tail;
};