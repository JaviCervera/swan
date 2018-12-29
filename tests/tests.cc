#include "test_dir.hh"
#include "test_file.hh"
#include "test_platform.hh"
#include "test_sharedlib.hh"
#include "test_strmanip.hh"
#include "test_time.hh"

using namespace swan;

int main(int argc, const char* argv[])
{
  test_dir d;
  test_file f;
  test_platform p;
  test_sharedlib sl;
  test_strmanip st;
  test_time t;

  d.run();
  f.run();
  p.run();
  sl.run();
  st.run();
  t.run();
}
