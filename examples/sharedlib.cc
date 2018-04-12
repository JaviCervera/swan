#include "../sharedlib"
#include <iostream>

int main()
{
  swan::sharedlib_t lib("user32");
  if ( lib.isopen() )
  {
    std::cout << lib.funcptr("InitApp") << std::endl;
  }
  else
  {
    std::cout << "could not open lib" << std::endl;
  }
}

