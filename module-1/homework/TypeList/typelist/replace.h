#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace {
    using NewTypeList = NullType;
};

template<typename Head, typename Tail, typename OldType, typename NewType>
struct Replace<TypeList<Head, Tail>, OldType, NewType> {
    using NewTypeList = TypeList<Head, typename Replace<Tail, OldType, NewType>::NewTypeList>;
};

template<typename Head, typename Tail, typename NewType>
struct Replace<TypeList<Head, Tail>, Head, NewType> {
    using NewTypeList = TypeList<NewType, Tail>;
};