#include "../file.hh"
#include "../testing.hh"
#include <iostream>

class test_file : public swan::testcase_t
{
public:
  void test_size()
  {
    assert_notequal<size_t>(0, swan::filesize("test_file.hh"));
  }

  void test_copynotexists()
  {
    assert_equal(funknown, swan::filetype("test_file_copy.hh"));
  }

  void test_copy()
  {
    swan::filecopy("test_file.hh", "test_file_copy.hh");
    assert_equal(swan::filesize("test_file.hh"), swan::filesize("test_file_copy.hh"));
  }

  void test_remove()
  {
    swan::fileremove("test_file_copy.hh");
    assert_equal(funknown, swan::filetype("test_file_copy.hh"));
  }

  test_file() : testcase_t("file")
  {
    add_test(test_func(&test_file::test_size), "Checking that test_file.hh size is not zero");
    add_test(test_func(&test_file::test_copynotexists), "Checking that test_file_copy.hh does not exist");
    add_test(test_func(&test_file::test_copy), "Checking filecopy");
    add_test(test_func(&test_file::test_remove), "Checking fileremove");
  }
};
