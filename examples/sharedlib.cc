#include "../sharedlib"
#include <iostream>

// note: this example can only be run on windows currently
// because it access a windows dll, but you can use sharedlib_t
// on macos and linux too

typedef int(__stdcall * MessageBoxPtr)(const void*, const char*, const char*, unsigned int);

MessageBoxPtr MessageBox;

int main()
{
  swan::sharedlib_t lib("user32");
  if ( lib.isopen() )
  {
    MessageBox = reinterpret_cast<MessageBoxPtr>(lib.funcptr("MessageBoxA"));
    if ( !MessageBox )
    {
      std::cout << "could not find 'MessageBoxA' function within 'user32.dll'" << std::endl;
    }
    else
    {
      MessageBox(NULL, "Hello, world!", "Title", 0);
    }
  }
  else
  {
    std::cout << "could not open lib" << std::endl;
  }
  return 0;
}
