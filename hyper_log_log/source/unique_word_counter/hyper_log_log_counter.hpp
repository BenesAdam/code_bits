#pragma once

#include <array>
#include <limits>
#include "unique_word_counter_interface.hpp"

template<size_t BUCKET_BITS>
class HyperLogLogCounter : public UniqueWordCounterInterface
{
  static_assert(BUCKET_BITS < std::numeric_limits<size_t>::digits, "BUCKET_BITS is too large");

public:
  HyperLogLogCounter();
  void count_word(std::string word) override;
  uint32_t get_unique() override;

private:
  double get_harmonic_mean() const;
  uint32_t get_rank(const size_t hash) const;

  static constexpr std::size_t BUCKET_COUNT = std::size_t{1} << BUCKET_BITS;
  static constexpr double ALPHA = 0.7213F / (1.0F + (1.079F / static_cast<double>(BUCKET_COUNT)));

  std::array<uint32_t, BUCKET_COUNT> buckets_;
};

#include "hyper_log_log_counter.inl"
