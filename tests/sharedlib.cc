#include "../sharedlib"
#include "../console"

using namespace swan;

int main() {
  sharedlib lib("cheetahui");
  if ( lib.isopen() ) {
    console::writeln(str::fromnumber(lib.funcptr("InitApp")));
  } else {
    console::writeln("Could not open lib");
  }
}
