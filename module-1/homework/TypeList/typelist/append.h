#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append {
    using NewTypeList = NullType;
};

template<typename Head, typename Tail, typename NewType>
struct Append<TypeList<Head, Tail>, NewType> {
    using NewTypeList = TypeList<Head, typename Append<Tail, NewType>::NewTypeList>;
};

template<typename T>
struct Append<NullType, T> {
    using NewTypeList = TypeList<T, NullType>;
};

template<typename Head, typename Tail>
struct Append<TypeList<Head, Tail>, NullType> {
    using NewTypeList = TypeList<Head, Tail>;
};

template<>
struct Append<NullType, NullType> {
    using NewTypeList = NullType;
};
