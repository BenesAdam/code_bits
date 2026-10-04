#include "set_counter.hpp"

SetCounter::SetCounter() : set_{}
{
}

void SetCounter::count_word(std::string word)
{
  set_.insert(word);
}

uint32_t SetCounter::get_unique()
{
  return set_.size();
}
