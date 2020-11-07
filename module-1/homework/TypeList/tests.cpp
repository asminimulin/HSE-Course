#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "typelist/append.h"
#include "typelist/eraseall.h"
#include "typelist/indexof.h"
#include "typelist/length.h"
#include "typelist/noduplicates.h"
#include "typelist/replace.h"
#include "typelist/typeat.h"

#include "gtest/gtest.h"

TEST(Append, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<int, TypeList<double, TypeList<std::string, NullType>>> expected;
    
    testing::StaticAssertTypeEq<Append<actual, std::string>::NewTypeList, expected>();
}

TEST(Append, Test2) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<int, TypeList<double, TypeList<std::string, NullType>>> expected;
    
    static_assert((!std::is_same<Append<actual, int>::NewTypeList, expected>::value));
}

TEST(Append, Test3) {
    typedef TypeList<int, NullType> expected;

    testing::StaticAssertTypeEq<Append<NullType, int>::NewTypeList, expected>();
}

TEST(Append, Test4) {
    testing::StaticAssertTypeEq<Append<NullType, NullType>::NewTypeList, NullType>();
}

TEST(Erase, Test1) {
    typedef TypeList<int, TypeList<int, NullType>> actual;
    typedef TypeList<int, NullType> expected;

    testing::StaticAssertTypeEq<Erase<actual, int>::NewTypeList, expected>();
}

TEST(Erase, Test2) {
    testing::StaticAssertTypeEq<Erase<NullType, int>::NewTypeList, NullType>();
}

TEST(EraseAll, Test1) {
    typedef TypeList<int, TypeList<int, NullType>> actual;
    
    testing::StaticAssertTypeEq<EraseAll<actual, int>::NewTypeList, NullType>();
}

TEST(EraseAll, Test2) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<double, NullType> expected;

    testing::StaticAssertTypeEq<EraseAll<actual, int>::NewTypeList, expected>();
}

TEST(EraseAll, Test3) {
    testing::StaticAssertTypeEq<EraseAll<NullType, int>::NewTypeList, NullType>();
}

TEST(IndexOf, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;

    static_assert(IndexOf<actual, double>::pos == 1, "expected pos=1");
}

TEST(IndexOf, Test2) {
    typedef TypeList<int, TypeList<double, NullType>> actual;

    static_assert(IndexOf<actual, char>::pos == -1, "expected pos=-1");
}

TEST(IndexOf, Test3) {
    static_assert(IndexOf<NullType, char>::pos== -1, "expected pos=-1");
}

TEST(Length, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    
    static_assert(Length<actual>::length == 2, "expected length=2");
}

TEST(Length, Test2) { 
    static_assert(Length<NullType>::length == 0, "expected length=0");
}

TEST(NoDuplicates, Test1) {
    typedef TypeList<int, TypeList<int, TypeList<std::string, TypeList<std::string, NullType>>>> actual;
    typedef TypeList<int, TypeList<std::string, NullType>> expected;
    
    testing::StaticAssertTypeEq<NoDuplicates<actual>::NewTypeList, expected>();
}

TEST(Replace, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef TypeList<int, TypeList<std::string, NullType>> expected;
    
    testing::StaticAssertTypeEq<Replace<actual, double, std::string>::NewTypeList, expected>();
}

TEST(Replace, Test2) {
    testing::StaticAssertTypeEq<Replace<NullType, double, std::string>::NewTypeList, NullType>();
}

TEST(TypeAt, Test1) {
    typedef TypeList<int, TypeList<double, NullType>> actual;
    typedef double expected;

    using target_type = TypeAt<actual, 1>::TargetType;
    bool x = std::is_same<target_type, expected>::value;
    ASSERT_TRUE(x);
}

TEST(Custom, Test) {
    using list1 = TypeList<int, TypeList<short, TypeList<short, TypeList<char, NullType>>>>;

    testing::StaticAssertTypeEq<typename Append<list1, NullType>::NewTypeList, list1>();

    testing::StaticAssertTypeEq<Erase<list1, NullType>::NewTypeList, list1>();

    using list2 = TypeList<int, TypeList<float, TypeList<char, NullType>>>;
    testing::StaticAssertTypeEq<Erase<list2, void>::NewTypeList, list2>();

    testing::StaticAssertTypeEq<EraseAll<NullType, short>::NewTypeList, NullType>();

    using list3 = Replace<list1, short, long>::NewTypeList;
    using list3_expected = TypeList<int, TypeList<long, TypeList<short, TypeList<char, NullType>>>>;
    testing::StaticAssertTypeEq<list3, list3_expected>();

    testing::StaticAssertTypeEq<TypeAt<list1, 100000>::TargetType, NullType>();

    testing::StaticAssertTypeEq<Erase<TypeList<int, NullType>, int>::NewTypeList, NullType>();
}