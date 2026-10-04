#pragma once

#include <cstdint>
#include <string>

class UniqueWordCounterInterface
{
public:
  virtual void count_word(std::string word) = 0;
  virtual uint32_t get_unique() = 0;
protected:
private:
};
