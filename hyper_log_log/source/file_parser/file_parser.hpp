#pragma once

#include "string"
#include "optional"
#include "functional"
#include "unique_word_counter_interface.hpp"

class FileParser
{
public:
  FileParser(const std::string& file_path);

  void set_counter(UniqueWordCounterInterface& counter);
  void parse();

private:
  std::string clean_word(std::string word);

  const std::string& file_path_;
  std::optional<std::reference_wrapper<UniqueWordCounterInterface>> counter_;
};
