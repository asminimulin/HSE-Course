#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf {
    static constexpr int pos = -1;
};

template<typename Head, typename Tail>
struct IndexOf<TypeList<Head, Tail>, Head> {
    static constexpr int pos = 0;
};

template<typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType> {
private:
    static constexpr int tail_pos = IndexOf<Tail, TargetType>::pos;

public:
    static constexpr int pos = (tail_pos >= 0) ? tail_pos + 1 : -1;
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    static constexpr int pos = -1;
};