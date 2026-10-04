#include "algorithm"
#include "hyper_log_log_counter.hpp"
#include <cmath>

template<size_t BUCKET_BITS>
HyperLogLogCounter<BUCKET_BITS>::HyperLogLogCounter() : buckets_{}
{
}

template<size_t BUCKET_BITS>
void HyperLogLogCounter<BUCKET_BITS>::count_word(std::string word)
{
  std::hash<std::string> hash_function;
  const size_t hash = hash_function(word);
  const size_t index = hash >> (std::numeric_limits<size_t>::digits - BUCKET_BITS);
  const auto rank = get_rank(hash);

  buckets_[index] = std::max(buckets_[index], rank);
}

template<size_t BUCKET_BITS>
uint32_t HyperLogLogCounter<BUCKET_BITS>::get_rank(const size_t hash) const
{
  const size_t remainder_bits = std::numeric_limits<size_t>::digits - BUCKET_BITS;
  const size_t mask = (size_t{1} << remainder_bits) - 1;
  const size_t remainder = hash & mask;

  uint32_t rank = 1;
  for (size_t bit = remainder_bits; bit > 0; --bit)
  {
    if (remainder & (size_t{1} << (bit - 1)))
      break;
    ++rank;
  }

  return rank;
}

template<size_t BUCKET_BITS>
uint32_t HyperLogLogCounter<BUCKET_BITS>::get_unique()
{
  const auto harmonic_mean = get_harmonic_mean();
  const double estimate =
    ALPHA * static_cast<double>(BUCKET_COUNT * BUCKET_COUNT) * harmonic_mean;

  if (estimate <= 2.5 * BUCKET_COUNT)
  {
    const auto empty_buckets =
      std::count(buckets_.begin(), buckets_.end(), 0);

    if (empty_buckets > 0)
    {
      const double linear_counting =
        BUCKET_COUNT * std::log(
                         static_cast<double>(BUCKET_COUNT) / empty_buckets);
      return static_cast<uint32_t>(std::round(linear_counting));
    }
  }

  return static_cast<uint32_t>(std::round(estimate));
}

template<size_t BUCKET_BITS>
double HyperLogLogCounter<BUCKET_BITS>::get_harmonic_mean() const
{
  double sum = 0.0F;

  for (auto bucket : buckets_)
  {
    const double term = std::pow(2.0F, -static_cast<double>(bucket));
    sum += term;
  }

  return 1.0F / sum;
}
