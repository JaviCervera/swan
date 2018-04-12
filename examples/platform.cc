#include "../platform"
#include <iostream>
#include <string>

int main()
{
  std::string platform_name[] = { "windows", "macos", "linux" };
  std::cout << "platform name: " << platform_name[swan::platform::platformid()] << std::endl;
  return 0;
}

