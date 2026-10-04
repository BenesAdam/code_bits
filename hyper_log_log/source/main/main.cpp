#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

#include "file_parser.hpp"
#include "set_counter.hpp"
#include "hyper_log_log_counter.hpp"

int main(int argc, char** argv)
{
  SetCounter set_counter;
  HyperLogLogCounter<16> hyper_log_log_counter;

  // std::string text_path = "/home/adamb/Projects/hyper_log_log/input/dracula_really_short.txt";
  // std::string text_path = "/home/adamb/Projects/hyper_log_log/input/dracula.txt";
  // std::string text_path = "/home/adamb/Projects/hyper_log_log/input/pride_and_prejudice.txt";
  std::string text_path = "/home/adamb/Projects/hyper_log_log/input/moby_dick.txt";
  FileParser file_parser(text_path);

  file_parser.set_counter(set_counter);
  file_parser.parse();

  file_parser.set_counter(hyper_log_log_counter);
  file_parser.parse();

  std::cout << "Unique words: " << std::endl;
  std::cout << "a) Set: " << set_counter.get_unique() << std::endl;
  std::cout << "b) HLL: " << hyper_log_log_counter.get_unique() << std::endl;

  return 0;
}
