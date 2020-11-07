#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates {
    using NewTypeList = NullType;
};

template<typename First, typename TList>
struct NoDuplicates<TypeList<First, TypeList<First, TList>>> {
    using NewTypeList = TypeList<First, typename NoDuplicates<TList>::NewTypeList>;
};

template<>
struct NoDuplicates<NullType> {
    using NewTypeList = NullType;
};
