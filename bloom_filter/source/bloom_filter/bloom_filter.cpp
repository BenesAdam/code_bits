#include "bloom_filter.hpp"
#include <functional>
#include <iostream>

template<uint16_t BITS>
BloomFilter<BITS>::BloomFilter(const uint16_t hashes) : hashes_(hashes)
{
}

template<uint16_t BITS>
void BloomFilter<BITS>::insert(const std::string& key)
{
  for (uint16_t hash_index = 0U; hash_index < hashes_; ++hash_index)
  {
    const auto index = get_index(key, hash_index);
    data_.set(index);
  }
}

template<uint16_t BITS>
size_t BloomFilter<BITS>::get_index(const std::string& key, const size_t hash_index) const
{
  std::hash<std::string> hasher;
  size_t hash = hasher(key);
  hash ^= std::hash<size_t>()(hash_index) + 0x9E3779B9 + (hash << 6) + (hash >> 2);
  return hash % BITS;
}

template<uint16_t BITS>
bool BloomFilter<BITS>::contains(const std::string& key) const
{
  for (uint16_t hash_index = 0U; hash_index < hashes_; ++hash_index)
  {
    const auto index = get_index(key, hash_index);
    if (!data_.test(index))
    {
      return false;
    }
  }

  return true;
}

template<uint16_t BITS>
void BloomFilter<BITS>::test(const std::string& key) const
{
  std::cout << "Item \"" << key << "\" " << (contains(key) ? "is" : "is not") << " contained." << std::endl;
}

template class BloomFilter<32U>;
