#include "iostream"
#include "sstream"
#include "fstream"
#include <algorithm>

#include "file_parser.hpp"

FileParser::FileParser(const std::string& file_path) : file_path_(file_path), counter_{}
{
}

void FileParser::set_counter(UniqueWordCounterInterface& counter)
{
  counter_ = std::ref(counter);
}

void FileParser::parse()
{
  if (!counter_.has_value())
  {
    std::cerr << "Counter does not have a value.";
    return;
  }

  std::ifstream file(file_path_);

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);

    std::string word;
    while (iss >> word)
    {
      std::string cleaned = clean_word(word);
      counter_->get().count_word(cleaned);
    }
  }
}

std::string FileParser::clean_word(std::string word)
{
  // Remove every interpunktion
  word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c)
                            { return std::ispunct(c); }),
             word.end());

  // Transform to lower case
  std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                 { return std::tolower(c); });

  return word;
}
