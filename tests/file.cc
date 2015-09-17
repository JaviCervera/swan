#include "../file"
#include "../console"

using namespace swan;

int main() {
  console::writeln(str::fromnumber(file::filesize("file.cc")));
  file::copy("file.cc", "file_copy.cc");
  file f("file_copy.cc", file::read);
  if ( f.isopen() ) {
    while ( !f.eof() ) {
      console::writeln(f.readcline());
    }
    f.close();
  }
  file::del("file_copy.cc");
}
