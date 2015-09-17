#include "../dir"
#include "../console"

using namespace swan;

int main() {
  dir::create("_test_tmp");
  dir::del("_temp_tmp");

  console::writeln("Current dir: " + dir::current());
  console::writeln("Contents:");
  std::vector<std::string> contents = dir::contents(".");
  for ( size_t i = 0; i < contents.size(); ++i ) {
    console::writeln(contents[i]);
  }

  dir::change("..");
  console::writeln("Current dir: " + dir::current());
  console::writeln("Contents:");
  contents = dir::contents(".");
  for ( size_t i = 0; i < contents.size(); ++i ) {
    console::writeln(contents[i]);
  }
}
