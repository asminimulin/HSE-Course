#pragma once

template<typename H, typename T>
struct TypeList {
    using Head = H;
    using Tail = T;
};

struct NullType {};

template<>
struct TypeList<NullType, NullType> {
    using Head = NullType;
    using Tail = NullType;
};

template<typename H>
struct TypeList<H, NullType> {
    using Head = H;
    using Tail = NullType;
};
