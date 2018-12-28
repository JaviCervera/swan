#include "../dir.hh"
#include <iostream>

using namespace swan;

int main()
{
  dir::create("_test_tmp");
  dir::remove("_test_tmp");

  std::cout << "current dir: " << dir::current().c_str() << std::endl;
  std::cout << "contents:" << std::endl;
  vector_t<string_t> contents = dir::contents(".");
  for (vector_t<string_t>::const_iterator it = contents.begin(); it != contents.end(); ++it)
  {
    std::cout << " " << (*it).c_str() << std::endl;
  }

  dir::change("..");
  std::cout << "current dir: " << dir::current().c_str() << std::endl;
  std::cout << "contents:" << std::endl;
  contents = dir::contents(".");
  for (vector_t<string_t>::const_iterator it = contents.begin(); it != contents.end(); ++it)
  {
    std::cout << " " << (*it).c_str() << std::endl;
  }
  
  return 0;
}
