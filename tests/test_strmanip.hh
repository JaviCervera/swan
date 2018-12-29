#ifndef SWAN_TEST_STRMANIP_INCLUDED
#define SWAN_TEST_STRMANIP_INCLUDED

#include "../strmanip.hh"
#include "../testing.hh"

class test_strmanip : public swan::testcase_t
{
public:
  void test_string()
  {
    assert_equal<string_t>("this is a test string.", str);
  }

  void test_string2()
  {
    str.replace(9, 5, "n example");
    assert_equal<string_t>("this is an example string.", str);
  }

  void test_string3()
  {
    str.replace(19, 6, "phrase");
    assert_equal<string_t>("this is an example phrase.", str);
  }

  void test_string4()
  {
    str.replace(8, 10, "just a");
    assert_equal<string_t>("this is just a phrase.", str);
  }

  void test_string5()
  {
    str.resize(4);
    assert_equal<string_t>("this", str);
  }

  void test_string6()
  {
    str.resize(8, '=');
    assert_equal<string_t>("this====", str);
  }

  test_strmanip() : testcase_t("strmanip"), str("this is a test string.")
  {
    add_test(test_func(&test_strmanip::test_string), "Checking that initial string is \"this is a test string.\"");
    add_test(test_func(&test_strmanip::test_string2), "Checking that modified string is \"this is an example string.\"");
    add_test(test_func(&test_strmanip::test_string3), "Checking that modified string is \"this is an example phrase.\"");
    add_test(test_func(&test_strmanip::test_string4), "Checking that modified string is \"this is just a phrase.\"");
    add_test(test_func(&test_strmanip::test_string5), "Checking that modified string is \"this\"");
    add_test(test_func(&test_strmanip::test_string6), "Checking that modified string is \"this====\"");
  }
private:
  string_t str;
};

#endif // SWAN_TEST_STRMANIP_INCLUDED
