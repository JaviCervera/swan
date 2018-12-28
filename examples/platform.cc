#include "../platform.hh"
#include <iostream>

int main()
{
  swan::string_t platform_name[] = {"windows", "macos", "linux"};
  std::cout << "platform name: " << platform_name[swan::platform::platformid()].c_str() << std::endl;
  std::cout << "PATH: " << swan::platform::getenv("PATH").c_str() << std::endl;
  return 0;
}
