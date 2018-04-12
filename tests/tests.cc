// note: this example must be compiled with c++11 upwards

#include "../dir"
#include "../testing"
#include <string>
#include <vector>

int main()
{
  // dir
  swan::testing::describe("running dir tests", []()
  {
    swan::testing::println(("current dir is '" + swan::dir::current() + "'").c_str());

    swan::testing::it("checking dir contents", []()
    {
      std::vector<std::string> expected_dir = { "tests.cc" };
      swan::testing::expect_noprint(swan::dir::contents(swan::dir::current().c_str())).tobeobject(expected_dir);
    });
  });
}
