//
// Created by aminimulin on 08.09.2020.
//

#include "biginteger.h"

#include <exception>
#include <istream>
#include <stdexcept>

namespace big_integer {

BigInteger::BigInteger() : is_negative_(false), limbs_{0} {}

BigInteger::BigInteger(std::string_view string) {
  limbs_ = {0};
  is_negative_ = false;

  if (string.empty()) {
    throw std::runtime_error(
        "Cannot construct BigInteger from provided string");
  }

  size_t pos = 0;
  if (string[0] == '-') {
    is_negative_ = true;
    pos += 1;
  }

  for (; pos < string.size(); ++pos) {
    if (!isdigit(string[pos])) {
      throw std::runtime_error(
          "Cannot construct BigInteger from provided string");
    }
    // fixme: do it inplace
    *this = *this * 10 + (string[pos] - '0');
  }
}

BigInteger::BigInteger(int value)
    : is_negative_(value < 0), limbs_({LimbType(std::abs(value))}) {}

BigInteger::BigInteger(BigInteger&& other) noexcept
    : is_negative_(other.is_negative_), limbs_(std::move(other.limbs_)) {}

BigInteger BigInteger::operator+(const BigInteger& other) const {
  BigInteger result(*this);
  result += other;
  return result;
}

inline BigInteger::LimbType BigInteger::GetHighPart(
    ExtendedLimbType value) noexcept {
  return static_cast<LimbType>(value >> limb_type_size_);
}

inline BigInteger::LimbType BigInteger::GetLowPart(
    ExtendedLimbType value) noexcept {
  return static_cast<LimbType>(value & (~LimbType(0)));
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
  auto result = *this;
  result -= other;
  return result;
}

BigInteger BigInteger::operator-() const {
  if (IsZeroed()) {
    return *this;
  }
  return BigInteger(!is_negative_, limbs_);
}

BigInteger BigInteger::operator+() const {
  return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
  if (is_negative_ == other.is_negative_) {
    limbs_ = SummarizeAbsoluteValues(limbs_, other.limbs_);

  } else {
    auto compare_result = CompareAbsoluteValues(limbs_, other.limbs_);

    if (compare_result == CompareResult::LESS) {
      is_negative_ = !is_negative_;
      limbs_ = SubtractAbsoluteValues(other.limbs_, limbs_);
    } else if (compare_result == CompareResult::GREATER) {
      limbs_ = SubtractAbsoluteValues(limbs_, other.limbs_);
    } else if (compare_result == CompareResult::EQUAL) {
      is_negative_ = false;
      limbs_ = {0};
    } else {
      throw std::runtime_error("Comparing result has unexpected value.");
    }
  }
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
  if (is_negative_ != other.is_negative_) {
    limbs_ = SummarizeAbsoluteValues(limbs_, other.limbs_);

  } else {
    auto compare_result = CompareAbsoluteValues(limbs_, other.limbs_);

    if (compare_result == CompareResult::LESS) {
      is_negative_ = !is_negative_;
      limbs_ = SubtractAbsoluteValues(other.limbs_, limbs_);

    } else if (compare_result == CompareResult::GREATER) {
      limbs_ = SubtractAbsoluteValues(limbs_, other.limbs_);

    } else if (compare_result == CompareResult::EQUAL) {
      is_negative_ = false;
      limbs_ = {0};

    } else {
      throw std::runtime_error("Comparing result has unexpected value");
    }
  }
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  if (this->IsZeroed() || other.IsZeroed()) {
    is_negative_ = false;
    limbs_ = {0};

  } else {
    is_negative_ = this->is_negative_ != other.is_negative_;
    limbs_ =
        MultiplyAbsoluteValuesWithKaratsubaAlgo(this->limbs_, other.limbs_);
  }
  return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
  if (other.IsZeroed()) {
    throw std::logic_error("Division by zero");
  }

  is_negative_ = this->is_negative_ != other.is_negative_;
  limbs_ = DivideAbsoluteValues(this->limbs_, other.limbs_).first;

  if (IsZeroed()) {
    is_negative_ = false;
  }

  return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
  if (other.IsZeroed()) {
    throw std::logic_error("Division by zero");
  }

  limbs_ = DivideAbsoluteValues(this->limbs_, other.limbs_).second;

  if (IsZeroed()) {
    is_negative_ = false;
  }

  return *this;
}

bool BigInteger::operator<(const BigInteger& other) const noexcept {
  auto compare_result = CompareAbsoluteValues(this->limbs_, other.limbs_);

  if (this->is_negative_ && other.is_negative_) {
    return compare_result == CompareResult::GREATER;
  } else if (this->is_negative_ && !other.is_negative_) {
    return true;
  } else if (!this->is_negative_ && other.is_negative_) {
    return false;
  } else {
    return compare_result == CompareResult::LESS;
  }
}

bool BigInteger::operator<=(const BigInteger& other) const noexcept {
  auto compare_result = CompareAbsoluteValues(this->limbs_, other.limbs_);

  if (this->is_negative_ && other.is_negative_) {
    return (compare_result == CompareResult::GREATER) ||
           (compare_result == CompareResult::EQUAL);

  } else if (this->is_negative_ && !other.is_negative_) {
    return true;

  } else if (!this->is_negative_ && other.is_negative_) {
    return false;

  } else {
    return (compare_result == CompareResult::LESS) ||
           (compare_result == CompareResult::EQUAL);
  }
}

bool BigInteger::operator>(const BigInteger& other) const noexcept {
  // Careful here
  // l > r is the same as r < l
  return other < *this;
}

bool BigInteger::operator>=(const BigInteger& other) const noexcept {
  // Careful here
  // l >= r is the same as !(l < r)
  return !(*this < other);
}

bool BigInteger::operator==(const BigInteger& other) const noexcept {
  if (is_negative_ != other.is_negative_) {
    return false;
  }
  return limbs_ == other.limbs_;
}

bool BigInteger::operator!=(const BigInteger& other) const noexcept {
  // Careful here
  // l != r is the same as !(l == r)
  return !(*this == other);
}

BigInteger::operator bool() const noexcept {
  return !IsZeroed();
}

BigInteger BigInteger::operator--(int) {
  auto result = *this;
  --*this;
  return result;
}

BigInteger BigInteger::operator++(int) {
  auto result = *this;
  ++*this;
  return result;
}

BigInteger& BigInteger::operator++() {
  if (is_negative_) {
    DecrementAbsoluteValue(limbs_);
    if (IsZeroed()) {
      is_negative_ = false;
    }
  } else {
    IncrementAbsoluteValue(limbs_);
  }
  return *this;
}

BigInteger& BigInteger::operator--() {
  if (IsZeroed()) {
    is_negative_ = true;
    IncrementAbsoluteValue(limbs_);
  } else if (is_negative_) {
    IncrementAbsoluteValue(limbs_);
  } else {
    DecrementAbsoluteValue(limbs_);
  }
  return *this;
}

BigInteger::BigInteger(bool is_negative, std::vector<LimbType> limbs)
    : is_negative_(is_negative), limbs_(std::move(limbs)) {
  if (IsZeroed()) is_negative_ = false;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
  auto result = *this;
  result *= other;
  return result;
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
  auto result = *this;
  result /= other;
  return result;
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
  auto result = *this;
  result %= other;
  return result;
}

std::string BigInteger::toString() const {
  if (IsZeroed()) {
    return "0";
  }
  std::string result;

  if (is_negative_) {
    result += '-';
  }

  std::vector<LimbType> limbs = limbs_;
  for (;;) {
    // fixme: use IsZeroed() method
    if ((limbs.size() == 1U) && (limbs[0] == 0)) {
      break;
    }

    auto division_result = DivideAbsoluteValueByLimb(limbs, 10U);
    result += char(division_result.second + '0');
    std::swap(limbs, division_result.first);
  }

  if (is_negative_) {
    std::reverse(result.begin() + 1, result.end());
  } else {
    std::reverse(result.begin(), result.end());
  }

  return result;
}

size_t BigInteger::GetMostSignificantBitPosition(
    const std::vector<LimbType>& value) noexcept {
  return GetMostSignificantBitPosition(value.back()) +
         (value.size() - 1) * limb_type_size_;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& value) {
  out << value.toString();
  return out;
}

std::istream& operator>>(std::istream& in, BigInteger& value) {
  char c;
  bool first = true;
  bool is_negative = false;
  value = 0;

  in >> c;
  while (!in.eof()) {
    if (first && (c == '-')) {
      is_negative = true;
    } else if (isdigit(c)) {
      value = value * 10 + c - '0';
    } else {
      in.putback(c);
      break;
    }
    first = false;

    // c can become -1 when we read EOF symbol from the input stream
    c = char(in.get());
  }

  if (is_negative && (value != 0)) {
    value = -value;
  }

  return in;
}

bool BigInteger::IsZeroed() const {
  return (limbs_.size() == 1) && (limbs_[0] == 0);
}

/*************************************************************************
 * From here low-level math starts
 *
 * This file implements unsigned math with numbers
 * represented as sequence of limbs
 */

BigInteger::CompareResult BigInteger::CompareAbsoluteValues(
    const std::vector<LimbType>& left, const std::vector<LimbType>& right) {
  if (left.size() < right.size()) {
    return CompareResult::LESS;
  }

  if (left.size() > right.size()) {
    return CompareResult::GREATER;
  }

  // pos could be equal to -1 => counter with sign bit required
  auto pos = long(left.size() - 1U);
  while (pos >= 0) {
    auto index = size_t(pos);

    if (left[index] < right[index]) {
      return CompareResult::LESS;
    }

    if (left[index] > right[index]) {
      return CompareResult::GREATER;
    }

    --pos;
  }

  return CompareResult::EQUAL;
}

std::vector<BigInteger::LimbType> BigInteger::SummarizeAbsoluteValues(
    const std::vector<LimbType>& left, const std::vector<LimbType>& right) {
  std::vector<LimbType> result(std::max(left.size(), right.size()));

  std::size_t pos = 0;
  LimbType carry = 0;
  while (pos < result.size()) {
    ExtendedLimbType limbs_sum;

    if (pos < right.size()) {
      limbs_sum = ExtendedLimbType(carry) + ExtendedLimbType(left[pos]) +
                  ExtendedLimbType(right[pos]);
    } else {
      limbs_sum = ExtendedLimbType(left[pos]) + carry;
    }

    result[pos] = GetLowPart(limbs_sum);
    carry = GetHighPart(limbs_sum);
    pos++;
  }

  if (carry != 0) {
    result.push_back(carry);
  }

  return result;
}

std::vector<BigInteger::LimbType> BigInteger::SubtractAbsoluteValues(
    const std::vector<LimbType>& left, const std::vector<LimbType>& right) {
  // It is private function. We assume that left > right.
  std::vector<LimbType> result(left.size(), 0);

  size_t pos = 0;
  ExtendedLimbType borrow = 0;
  while (pos < right.size()) {
    // Use ExtendedLimbType to calculate because LimbType overflow occurs when
    // (right[pos] == std::numeric_limits<LimbType>::max() && borrow == 1)
    if (ExtendedLimbType(left[pos]) >= ExtendedLimbType(right[pos]) + borrow) {
      result[pos] = LimbType(ExtendedLimbType(left[pos] - right[pos]) - borrow);
      borrow = 0;
    } else {
      ExtendedLimbType tmp = left[pos];
      tmp += (ExtendedLimbType(1) << limb_type_size_);
      tmp -= ExtendedLimbType(right[pos]);
      tmp += borrow;

      result[pos] = LimbType(tmp);
      borrow = 1;
    }
    pos++;
  }

  while (pos < left.size() && borrow == 1) {
    if (left[pos] >= borrow) {
      result[pos] = LimbType(left[pos] - borrow);
      borrow = 0;
    } else {
      result[pos] = LimbType(std::numeric_limits<LimbType>::max() - borrow);
      // here borrow still must be equal to 1
    }
    pos++;
  }

  while (pos < left.size()) {
    result[pos] = left[pos];
    ++pos;
  }

  Normalize(result);

  if (result.empty()) {
    throw std::runtime_error("Unexpected empty result of subtraction");
  }

  return result;
}

void BigInteger::IncrementAbsoluteValue(std::vector<LimbType>& limbs) {
  ExtendedLimbType carry = 1;
  size_t pos = 0;
  while ((carry != 0) && (pos < limbs.size())) {
    auto limbs_sum = carry + ExtendedLimbType(limbs[pos]);
    limbs[pos] = GetLowPart(limbs_sum);
    carry = GetHighPart(limbs_sum);
    pos++;
  }

  if (carry) {
    limbs.push_back(LimbType(carry));
  }
}

void BigInteger::DecrementAbsoluteValue(std::vector<LimbType>& limbs) {
  // It is private function and it is assumed that limbs.size() > 1
  for (LimbType& limb : limbs) {
    if (limb == 0) {
      limb = std::numeric_limits<LimbType>::max();
    } else {
      limb--;
      break;
    }
  }

  Normalize(limbs);
}

std::vector<BigInteger::LimbType> BigInteger::MultiplyAbsoluteValues(
    const std::vector<LimbType>& left, const std::vector<LimbType>& right) {
  return MultiplyAbsoluteValuesWithKaratsubaAlgo(left, right);
}

std::vector<BigInteger::LimbType>
BigInteger::MultiplyAbsoluteValuesWithKaratsubaAlgo(
    const std::vector<LimbType>& left, const std::vector<LimbType>& right) {
  if (left.size() < KARATSUBA_STOP_RECURSION_SIZE) {
    return MultiplyAbsoluteValuesNaive(right, left);

  } else if (right.size() < KARATSUBA_STOP_RECURSION_SIZE) {
    return MultiplyAbsoluteValuesNaive(left, right);
  } else {
    auto max_half_size = std::max(left.size() / 2, right.size() / 2);
    auto half_size = std::min(left.size(), right.size());
    half_size = std::min(half_size, max_half_size);

    std::vector a(left.begin() + long(half_size), left.end());
    std::vector b(left.begin(), left.begin() + long(half_size));
    std::vector c(right.begin() + long(half_size), right.end());
    std::vector d(right.begin(), right.begin() + long(half_size));

    auto mul_ac = MultiplyAbsoluteValuesWithKaratsubaAlgo(a, c);
    auto mul_bd = MultiplyAbsoluteValuesWithKaratsubaAlgo(b, d);
    auto sum_ab = SummarizeAbsoluteValues(a, b);
    auto sum_cd = SummarizeAbsoluteValues(c, d);

    auto mul_sum_ab_sum_cd =
        MultiplyAbsoluteValuesWithKaratsubaAlgo(sum_ab, sum_cd);
    auto center = SubtractAbsoluteValues(
        mul_sum_ab_sum_cd, SummarizeAbsoluteValues(mul_ac, mul_bd));

    // I am trying to avoid unnecessary copying and memory allocations,
    // so I can use mul_bd instance to store result
    // mul_bd is part of the final answer, so I need to add remaining values
    auto& result = mul_bd;

    ShiftLimbsLeft(center, half_size);
    ShiftLimbsLeft(mul_ac, half_size * 2);

    result = SummarizeAbsoluteValues(result,
                                     SummarizeAbsoluteValues(mul_ac, center));
    return result;
  }
}

std::vector<BigInteger::LimbType> BigInteger::MultiplyAbsoluteValuesNaive(
    const std::vector<LimbType>& shorter, const std::vector<LimbType>& longer) {
  std::vector<LimbType> result(shorter.size() + longer.size(), 0);

  // todo: check if there is a bug.
  // It is strange that there are no LimbType overflow checks
  // in the whole function

  for (size_t short_pos = 0; short_pos < shorter.size(); ++short_pos) {
    ExtendedLimbType carry = 0;

    for (size_t long_pos = 0; long_pos < longer.size(); ++long_pos) {
      ExtendedLimbType tmp = carry;
      tmp += ExtendedLimbType(shorter[short_pos]) *
             ExtendedLimbType(longer[long_pos]);
      tmp += ExtendedLimbType(result[long_pos + short_pos]);

      result[long_pos + short_pos] = GetLowPart(tmp);
      carry = GetHighPart(tmp);
    }

    if (carry) {
      result[short_pos + longer.size()] = LimbType(carry);
    }
  }

  Normalize(result);
  return result;
}

std::pair<std::vector<BigInteger::LimbType>, BigInteger::LimbType>
BigInteger::DivideAbsoluteValueByLimb(const std::vector<LimbType>& left,
                                      LimbType right) {
  std::vector<LimbType> result;
  result.resize(left.size());

  ExtendedLimbType carry = 0;
  auto pos = left.size() - 1;

  // when pos = -1 it's actual value is ~size_t(0)
  while (pos < left.size()) {
    ExtendedLimbType cur =
        left[pos] + (ExtendedLimbType(carry) << limb_type_size_);
    result[pos] = GetLowPart(cur / ExtendedLimbType(right));

    carry = cur % right;
    pos--;
  }

  Normalize(result);
  return {result, carry};
}

std::pair<std::vector<BigInteger::LimbType>, std::vector<BigInteger::LimbType>>
BigInteger::DivideAbsoluteValues(const std::vector<LimbType>& left,
                                 const std::vector<LimbType>& right) {
  if (CompareAbsoluteValues(left, right) == CompareResult::LESS) {
    return {{0}, left};
  }

  std::vector<LimbType> dividend = left;
  std::vector<LimbType> result = {0U};
  std::vector<LimbType> current_value = right;

  {
    auto left_msb_position = GetMostSignificantBitPosition(left);
    auto right_msb_position = GetMostSignificantBitPosition(right);
    ShiftBitsLeft(current_value, left_msb_position - right_msb_position);
  }

  while (CompareAbsoluteValues(current_value, right) != LESS) {
    ShiftBitsLeft(result, 1);

    if (CompareAbsoluteValues(dividend, current_value) != CompareResult::LESS) {
      // set least bit
      result[0] |= 1U;
      dividend = SubtractAbsoluteValues(dividend, current_value);
    }

    ShiftBitsRight(current_value, 1);
  }
  return {result, dividend};
}

void BigInteger::ShiftLimbsLeft(std::vector<LimbType>& limbs, size_t count) {
  limbs.insert(limbs.begin(), count, 0);
}

void BigInteger::ShiftLimbsRight(std::vector<LimbType>& limbs, long count) {
  count = std::min(count, long(limbs.size()));
  limbs.erase(limbs.begin(), limbs.begin() + count);
}

void BigInteger::ShiftBitsLeft(std::vector<LimbType>& limbs, size_t count) {
  if (count == 0) {
    return;
  }
  auto limbs_count = count / limb_type_size_;
  ShiftLimbsLeft(limbs, limbs_count);

  count %= limb_type_size_;
  LimbType carry = 0;
  for (LimbType& limb_value : limbs) {
    ExtendedLimbType new_limb_value =
        (ExtendedLimbType(limb_value) << count) + carry;
    limb_value = GetLowPart(new_limb_value);
    carry = GetHighPart(new_limb_value);
  }

  if (carry != 0) {
    limbs.push_back(carry);
  }
}

void BigInteger::ShiftBitsRight(std::vector<LimbType>& limbs, long count) {
  if (count == 0) {
    return;
  }
  auto limbs_count = count / long(limb_type_size_);
  ShiftLimbsRight(limbs, limbs_count);

  count %= limb_type_size_;
  LimbType borrow = 0;
  for (auto i = long(limbs.size()) - 1; i >= 0; --i) {
    LimbType new_limb_value = (limbs[size_t(i)] >> size_t(count)) | borrow;
    borrow = (GetLeastBitsMask(size_t(count)) & limbs[size_t(i)])
             << (limb_type_size_ - size_t(count));
    limbs[size_t(i)] = new_limb_value;
  }

  Normalize(limbs);
}

constexpr BigInteger::LimbType BigInteger::GetLeastBitsMask(size_t bits_count) {
  LimbType result = 0;
  for (size_t i = 0; i < bits_count; ++i) {
    result |= (LimbType(1) << i);
  }

  return result;
}

void BigInteger::Normalize(std::vector<LimbType>& limbs) noexcept {
  if (limbs.empty()) {
    limbs = {0};
    return;
  }

  auto is_not_zero = [](LimbType value) {
    return value != 0;
  };

  auto count_lead_zeros = size_t(
      std::find_if(limbs.rbegin(), limbs.rend(), is_not_zero) - limbs.rbegin());

  limbs.erase(limbs.end() - (long)std::min(limbs.size() - 1U, count_lead_zeros),
              limbs.end());
}

size_t BigInteger::GetMostSignificantBitPosition(LimbType value) noexcept {
  if (!value) {
    return ~size_t(0);
  }

  size_t pos = 0;
  while (value) {
    value >>= 1U;
    pos++;
  }

  return pos - 1;
}

}  // namespace big_integer