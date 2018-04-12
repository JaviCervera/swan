#include "../dir"
#include <iostream>

int main()
{
  swan::dir::create("_test_tmp");
  swan::dir::remove("_test_tmp");

  std::cout << "current dir: " << swan::dir::current() << std::endl;
  std::cout << "contents:" << std::endl;
  std::vector<std::string> contents = swan::dir::contents(".");
  for ( std::vector<std::string>::const_iterator it = contents.cbegin(); it != contents.cend(); ++it )
  {
    std::cout << " " << *it << std::endl;
  }

  swan::dir::change("..");
  std::cout << "current dir: " + swan::dir::current() << std::endl;
  std::cout << "contents:" << std::endl;
  contents = swan::dir::contents(".");
  for ( std::vector<std::string>::const_iterator it = contents.cbegin(); it != contents.cend(); ++it )
  {
    std::cout << " " << *it << std::endl;
  }
}

