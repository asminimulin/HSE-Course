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

  static std::vector<LimbType> SubtractAbsoluteValues(
      const std::vector<LimbType>& left, const std::vector<LimbType>& right);

  static void IncrementAbsoluteValue(std::vector<LimbType>& limbs);

  static void DecrementAbsoluteValue(std::vector<LimbType>& limbs);

  static std::vector<LimbType> MultiplyAbsoluteValues(
      const std::vector<LimbType>& left, const std::vector<LimbType>& right);

  static std::vector<LimbType> MultiplyAbsoluteValuesWithKaratsubaAlgo(
      const std::vector<LimbType>& left, const std::vector<LimbType>& right);

  static std::vector<LimbType> MultiplyAbsoluteValuesNaive(
      const std::vector<LimbType>& shorter,
      const std::vector<LimbType>& longer);

  static void MultiplyAbsoluteValueByLimbInplace(std::vector<LimbType>& limbs,
                                                 LimbType value);

  static std::pair<std::vector<LimbType>, std::vector<LimbType>>
  DivideAbsoluteValues(const std::vector<LimbType>& left,
                       const std::vector<LimbType>& right);

  static std::pair<std::vector<LimbType>, LimbType> DivideAbsoluteValueByLimb(
      const std::vector<LimbType>& left, LimbType limb);

  static void ShiftLimbsLeft(std::vector<LimbType>& limbs, size_t count);

  static void ShiftLimbsRight(std::vector<LimbType>& limbs, long count);

  static void ShiftBitsLeft(std::vector<LimbType>& limbs, size_t count);

  static void ShiftBitsRight(std::vector<LimbType>& limbs, long count);

  static constexpr uint32_t GetLeastBitsMask(size_t bits_count);

  static void Normalize(std::vector<uint32_t>& limbs) noexcept;

  static size_t GetMostSignificantBitPosition(LimbType value) noexcept;

  static size_t GetMostSignificantBitPosition(
      const std::vector<LimbType>& value) noexcept;

  /**
   * This constructor should be used from internal arithmetic functions
   * It provides necessary sign checks
   * @param is_negative is the number negative
   * @param limbs the limbs of the number
   */
  BigInteger(bool is_negative, std::vector<LimbType> limbs);

  [[nodiscard]] bool IsZeroed() const;

  [[nodiscard]] static bool IsZeroed(const std::vector<LimbType>& limbs);

 private:
  bool is_negative_{};

  std::vector<LimbType> limbs_;

  static constexpr size_t KARATSUBA_STOP_RECURSION_SIZE = 10;
};

std::istream& operator>>(std::istream& in, BigInteger& value);

std::ostream& operator<<(std::ostream& out, const BigInteger& value);

}  // namespace big_integer

#endif
