#include "test_dir.hh"
#include "test_file.hh"
#include "test_map.hh"
#include "test_pair.hh"
#include "test_platform.hh"
#include "test_sharedlib.hh"
#include "test_strmanip.hh"
#include "test_time.hh"
#include "test_vector.hh"

using namespace swan;

int main(int argc, const char* argv[])
{
  test_dir_t d;
  test_file_t f;
  test_map_t m;
  test_pair_t p;
  test_platform_t pl;
  test_sharedlib_t sl;
  test_strmanip_t st;
  test_time_t t;
  test_vector_t v;

  d.run();
  f.run();
  m.run();
  p.run();
  pl.run();
  sl.run();
  st.run();
  t.run();
  v.run();
}
