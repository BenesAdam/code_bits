#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "bloom_filter.hpp"

int main(int argc, char** argv)
{
  BloomFilter<32U> bloom_filter(10U);

  bloom_filter.insert("Alice");
  bloom_filter.insert("Bob");
  bloom_filter.insert("Charlie");

  bloom_filter.test("Alice");
  bloom_filter.test("Eve");

  return 0;
}
