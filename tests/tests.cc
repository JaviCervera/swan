#include "test_dir.hh"
#include "test_file.hh"

int main(int argc, const char* argv[])
{
  test_dir d(swan::strmanip::stripdir(argv[0]));
  test_file f;

  d.run();
  f.run();
}
