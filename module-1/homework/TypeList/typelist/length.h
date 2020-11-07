#pragma once

#include "typelist.h"

template<typename TList> 
struct Length {};

template<>
struct Length<NullType> {
    static size_t const length = 0;
};

template<typename T, typename TListTail>
struct Length<TypeList<T, TListTail>> {
    static size_t const length = 1 + Length<TListTail>::length;
};