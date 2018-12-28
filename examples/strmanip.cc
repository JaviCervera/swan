#include "../strmanip.hh"
#include <iostream>

int main()
{
  swan::string_t str = "this is a test string."; // this is a test string.
  std::cout << str.c_str() << std::endl;
  std::cout << str.length() << std::endl;

  str.replace(9, 5, "n example");                // this is an example string.
  std::cout << str.c_str() << std::endl;
  std::cout << str.length() << std::endl;

  str.replace(19, 6, "phrase");                  // this is an example phrase.
  std::cout << str.c_str() << std::endl;
  std::cout << str.length() << std::endl;

  str.replace(8, 10, "just a");                  // this is just a phrase.
  std::cout << str.c_str() << std::endl;
  std::cout << str.length() << std::endl;

  str.resize(4);                                 // this
  std::cout << str.c_str() << std::endl;
  std::cout << str.length() << std::endl;

  str.resize(8, '=');                                 // this====
  std::cout << str.c_str() << std::endl;
  std::cout << str.length() << std::endl;

  return 0;
}
