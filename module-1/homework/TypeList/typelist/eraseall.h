#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll {
    using NewTypeList = NullType;
};

template<typename TList>
struct EraseAll<TList, NullType> {
    using NewTypeList = TList;
};

template<typename TargetType>
struct EraseAll<NullType, TargetType> {
    using NewTypeList = NullType;
};

template<typename Head, typename Tail>
struct EraseAll<TypeList<Head, Tail>, Head> {
    using NewTypeList = typename EraseAll<Tail, Head>::NewTypeList;
};

template<typename Head, typename Tail, typename TargetType>
struct EraseAll<TypeList<Head, Tail>, TargetType> {
    using NewTypeList = TypeList<Head, typename EraseAll<Tail, TargetType>::NewTypeList>;
};