#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstdint>
#include <bitset>

template<uint16_t BITS>
class BloomFilter
{
public:
  BloomFilter(const uint16_t hashes);

  void insert(const std::string& key);
  bool contains(const std::string& key) const;

  void test(const std::string& key) const;

private:
  size_t get_index(const std::string& key, const size_t hash_index) const;

  const uint16_t hashes_;
  std::bitset<BITS> data_;
};
