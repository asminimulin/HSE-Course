#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

namespace big_integer {

class BigInteger {
 public:
  BigInteger();

  BigInteger(std::string_view string);

  BigInteger(int value);

  BigInteger(const BigInteger& other) = default;

  BigInteger(BigInteger&& other) noexcept;

  BigInteger& operator=(const BigInteger& other) = default;

  BigInteger& operator=(BigInteger&& other) noexcept = default;

  BigInteger operator+(const BigInteger& other) const;

  BigInteger operator-(const BigInteger& other) const;

  BigInteger operator*(const BigInteger& other) const;

  BigInteger operator/(const BigInteger& other) const;

  BigInteger operator%(const BigInteger& other) const;

  BigInteger& operator++();

  BigInteger operator++(int);

  BigInteger& operator--();

  BigInteger operator--(int);

  BigInteger operator-() const;

  BigInteger operator+() const;

  BigInteger& operator+=(const BigInteger& other);

  BigInteger& operator-=(const BigInteger& other);

  BigInteger& operator*=(const BigInteger& other);

  BigInteger& operator/=(const BigInteger& other);

  BigInteger& operator%=(const BigInteger& other);

  bool operator<(const BigInteger& other) const noexcept;

  bool operator<=(const BigInteger& other) const noexcept;

  bool operator>(const BigInteger& other) const noexcept;

  bool operator>=(const BigInteger& other) const noexcept;

  bool operator==(const BigInteger& other) const noexcept;

  bool operator!=(const BigInteger& other) const noexcept;

  explicit operator bool() const noexcept;

  [[nodiscard]] std::string toString() const;

  ~BigInteger() = default;

 private:
  /**
   * I use uint32_t because I want to multiply numbers in uint64_t and
   * handle carried bits with bitwise operations
   */
  using LimbType = uint32_t;
  using ExtendedLimbType = uint64_t;

  static constexpr size_t limb_type_size_ = sizeof(LimbType) * 8U;

  static uint32_t GetHighPart(uint64_t value) noexcept;

  static uint32_t GetLowPart(uint64_t value) noexcept;

 private:
  enum CompareResult {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1,
  };

  static CompareResult CompareAbsoluteValues(
      const std::vector<LimbType>& left, const std::vector<LimbType>& right);

  static void SummarizeAbsoluteValuesInplace(
      std::vector<LimbType>& left, const std::vector<LimbType>& right);

  static std::vector<LimbType> SummarizeAbsoluteValues(
      const std::vector<LimbType>& left, const std::vector<LimbType>& right);

  static void SubtractAbsoluteValuesInplace(std::vector<LimbType>& left,
                                            const std::vector<LimbType>& right);

  static std::vector<uint32_t> SubtractAbsoluteValues(
      const std::vector<uint32_t>& left, const std::vector<uint32_t>& right);

  static void IncrementAbsoluteValue(std::vector<uint32_t>& limbs);

  static void DecrementAbsoluteValue(std::vector<uint32_t>& limbs);

  static std::vector<uint32_t> MultiplyAbsoluteValues(
      const std::vector<uint32_t>& left, const std::vector<uint32_t>& right);

  static std::vector<uint32_t> MultiplyAbsoluteValuesWithKaratsubaAlgo(
      const std::vector<uint32_t>& left, const std::vector<uint32_t>& right);

  static std::vector<uint32_t> MultiplyAbsoluteValuesNaive(
      const std::vector<uint32_t>& shorter,
      const std::vector<uint32_t>& longer);

  static std::pair<std::vector<uint32_t>, std::vector<uint32_t>>
  DivideAbsoluteValues(const std::vector<uint32_t>& left,
                       const std::vector<uint32_t>& right);

  static std::pair<std::vector<uint32_t>, uint32_t> DivideAbsoluteValueByLimb(
      const std::vector<uint32_t>& left, uint32_t limb);

  static void ShiftLimbsLeft(std::vector<uint32_t>& limbs, size_t count);

  static void ShiftLimbsRight(std::vector<uint32_t>& limbs, long count);

  static void ShiftBitsLeft(std::vector<uint32_t>& limbs, size_t count);

  static void ShiftBitsRight(std::vector<uint32_t>& limbs, long count);

  static constexpr uint32_t GetLeastBitsMask(size_t bits_count);

  static void Normalize(std::vector<uint32_t>& limbs) noexcept;

  static size_t GetMostSignificantBitPosition(uint32_t value) noexcept;

  static size_t GetMostSignificantBitPosition(
      const std::vector<uint32_t>& value) noexcept;

  /**
   * This constructor should be used from internal arithmetic functions
   * It provides necessary sign checks
   * @param is_negative is the number negative
   * @param limbs the limbs of the number
   */
  BigInteger(bool is_negative, std::vector<uint32_t> limbs);
  [[nodiscard]] bool IsZeroed() const;

 private:
  bool is_negative_{};

  std::vector<LimbType> limbs_;

  static constexpr size_t KARATSUBA_STOP_RECURSION_SIZE = 10;
};

std::istream& operator>>(std::istream& in, BigInteger& value);

std::ostream& operator<<(std::ostream& out, const BigInteger& value);

}  // namespace big_integer

#endif
