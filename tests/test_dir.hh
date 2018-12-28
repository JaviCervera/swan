#include "../dir.hh"
#include "../file.hh"
#include "../strmanip.hh"
#include "../testing.hh"
#include <iostream>

using namespace swan;

class test_dir : public testcase_t
{
public:
  void init()
  {
    std::cout << "* Current dir is '" << dir::current().c_str() << "'" << std::endl;
  }

  void test_notempfolder()
  {
    assert_equal(funknown, filetype("_test_tmp"));
  }

  void test_create()
  {
    dir::create("_test_tmp");
    assert_equal(fdir, filetype("_test_tmp"));
  }

  void test_remove()
  {
    dir::remove("_test_tmp");
    assert_equal(funknown, filetype("_test_tmp"));
  }

  void test_contents()
  {
    vector_t<string_t> expected_dir;
    expected_dir.push_back(".");
    expected_dir.push_back("..");
    expected_dir.push_back(app_name);
    expected_dir.push_back("tests.cc");
    expected_dir.push_back("test_dir.hh");
    expected_dir.push_back("test_file.hh");

    vector_t<string_t> actual_dir = dir::contents(dir::current());
    std::cout << "* Printing ' " << dir::current().c_str() << "' dir contents: " << std::endl;
    for (
      vector_t<string_t>::const_iterator it = actual_dir.begin();
      it != actual_dir.end();
      ++it)
    {
      std::cout << "  * " << (*it).c_str() << std::endl;
    }

    assert_equal(expected_dir, actual_dir);
  }

  void test_change()
  {
    string_t expected_current = strmanip::extractdir(dir::current());
    dir::change("..");
    string_t actual_current = dir::current();
    dir::change("tests");
    assert_equal(expected_current, actual_current);
  }

  test_dir(const string_t& app_name) : testcase_t("dir"), app_name(app_name)
  {
    add_test(test_func(&test_notempfolder), "Checking that temp folder does not exist");
    add_test(test_func(&test_create), "Checking dir::create");
    add_test(test_func(&test_remove), "Checking dir::remove");
    add_test(test_func(&test_contents), "Checking dir::contents");
    add_test(test_func(&test_change), "Checking dir::change");
  }
private:
  string_t app_name;
};
