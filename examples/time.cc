// note: on windows, you need to link to winmm to use time module

#include "../time.hh"
#include "../strmanip.hh" // must be included after time.hh to get parsetimeinfo function
#include <iostream>

int main()
{
  std::cout << "current date: " << swan::strmanip::parsetimeinfo(swan::time::timeinfo()).c_str() << std::endl;
  std::cout << "current millisecs: " << swan::time::millisecs() << std::endl;
  std::cout << "waiting 1 second..." << std::endl;
  swan::time::delay(1000);
  std::cout << "current date: " << swan::strmanip::parsetimeinfo(swan::time::timeinfo()).c_str() << std::endl;
  std::cout << "current millisecs: " << swan::time::millisecs() << std::endl;
  return 0;
}
