#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "biginteger.h"
#include "gtest/gtest.h"

using big_integer::BigInteger;

TEST(AssignmentFromInt, Test1) {
    int value = 42;
    BigInteger bigint_val;
    bigint_val = value;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(value));
}

TEST(UnaryMinus, Test1) {
    int value = 42;
    BigInteger bigint_val = value;
    bigint_val = -bigint_val;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(-value));
}

TEST(ToString, Test1) {
    int value = 42;
    BigInteger bigint_val = value;

    std::string testString = bigint_val.toString();
    ASSERT_EQ(testString, std::to_string(value));
}

TEST(ToAssignment, Test1) {
    int val = 42;
    BigInteger bigint_val = val;
    bigint_val += bigint_val += bigint_val += bigint_val;
    val += val += val += val;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(val));
}

TEST(Arithmetic, Test1) {
    int a = 42;
    int b = 11;
    BigInteger bigint_a = a;
    BigInteger bigint_b = b;

    ++bigint_a -= bigint_b++;
    ++a -= b++;


    bigint_b -= bigint_a *= bigint_a *= bigint_b;
    b -= a *= a *= b;

    bigint_a /= 42;
    a /= 42;

    bigint_a %= 100;
    a %= 100;

    std::ostringstream oss;
    oss << bigint_a << bigint_b;
    ASSERT_EQ(oss.str(), std::to_string(a) + std::to_string(b));
}

TEST(TypeCast, Test1) {
    BigInteger bigint_val = 42;
    ASSERT_TRUE(bool(bigint_val));

    bigint_val = 0;
    ASSERT_FALSE(bool(bigint_val));
}

TEST(InStream, Test1) {
    int value = 42;
    BigInteger bigint_val = value;

    std::istringstream iss(std::to_string(value));
    std::ostringstream oss;
    iss >> bigint_val;
    oss << bigint_val;

    ASSERT_EQ(oss.str(), std::to_string(value));
}

TEST(Comparison, Test1) {

   std::istringstream iss("9325492345983274589758023847509283745827349587212938129"
                              "348762838512387487213648172639471269348172397461297");
    BigInteger a;
    BigInteger b;
    iss >> a >> b;

    std::ostringstream oss;
    oss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
    ASSERT_EQ(oss.str(), "010101");
}

TEST(Comparison, NegativeValues) {
  BigInteger a = 10;
  BigInteger b = -10;

  std::stringstream ss;
  ss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
  ASSERT_EQ(ss.str(), "010101");
  ss.str("");

  std::swap(b, a);
  ss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
  ASSERT_EQ(ss.str(), "100110");
  ss.str("");

  a = -20;
  b = -20;
  ss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
  ASSERT_EQ(ss.str(), "111000");
}

TEST(Huge, Test1) {

  std::istringstream iss("9325492345983274589758023847509283745827349587212938129"
      "9325492345983274589758023847509283745827349587212938129"
      "9325492345983274589758023847509283745827349587212938129"
      "9325492345983274589758023847509283745827349587212938129"
      "9325492345983274589758023847509283745827349587212938129"
      "9325492345983274589758023847509283745827349587212938129"
      "9325492345983274589758023847509283745827349587212938129 "
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297"
      "348762838512387487213648172639471269348172397461297");
  BigInteger a;
  BigInteger b;
  iss >> a >> b;

  std::string_view correct_answer = "325238518111067033664577314008878939431"
      "181260739769327233603389712655993221168"
      "842740419705256298059152635433802898240"
      "520555454033228223805853283705562884573"
      "764622918191373341910256514662354191898"
      "508303634946958456000193368427188902136"
      "990998046732369783909021995775383501568"
      "626697430001553230911117853170057049403"
      "279115439899446717380854339687134404291"
      "718395664206019865813093279799382816901"
      "113968919916995792766666612245945012473"
      "108714116901113968919916995792766666612"
      "245945012473108714116901113968919916995"
      "792441428094134877978808531400108022174"
      "537738656256023439433008856232356479887"
      "545274160694263663618936640131232809347"
      "704491917654680888677308115636211432908"
      "192901989327753639131198457602238759777"
      "021408692157819708156245751644045919811"
      "979910115922187547211883744670836862443"
      "443846411284115347883057802063825735717"
      "263333130505113026391333262561426834515"
      "6252773971024605923801319191933093313";

  std::ostringstream oss;
  oss << a * b;
  ASSERT_EQ(oss.str(), correct_answer);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}