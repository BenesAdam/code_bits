#pragma once

#include "unordered_set"
#include "unique_word_counter_interface.hpp"

class SetCounter : public UniqueWordCounterInterface
{
public:
  SetCounter();
  void count_word(std::string word) override;
  uint32_t get_unique() override;
private:
  std::unordered_set<std::string> set_;
};
