#include "../file.hh"
#include <iostream>

int main()
{
  std::cout << "size of 'file.cc': " << swan::filesize("file.cc") << " bytes" << std::endl;
  swan::filecopy("file.cc", "file_copy.cc");
  std::cout << "file 'file.cc' copied to 'file_copy.cc'" << std::endl;
  swan::file_t f("file_copy.cc", swan::file_t::read);
  if (f.isopen())
  {
    std::cout << "*** contents of 'file_copy.cc' ***" << std::endl;
    while ( !f.eof() )
    {
      std::cout << f.readcline().c_str() << std::endl;
    }
    f.close();
    std::cout << "*** end ***" << std::endl;
  }
  else
  {
    std::cout << "error: 'file_copy.cc' could not be opened" << std::endl;  
  }
  swan::fileremove("file_copy.cc");
  std::cout << "file 'file_copy.cc' removed" << std::endl;
  return 0;
}
