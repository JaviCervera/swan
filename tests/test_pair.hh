#ifndef SWAN_TEST_PAIR_INCLUDED
#define SWAN_TEST_PAIR_INCLUDED

#include "../pair.hh"
#include "../string.hh"
#include "../testing.hh"

struct test_pair_t : public swan::testcase_t
{
  void test_empty_constructor()
  {
    std::pair<std::string, int> pair;
    assert_equal<std::string>("", pair.first);
    assert_equal<int>(0, pair.second);
  }

  void test_constructor()
  {
    std::pair<std::string, int> pair("hello", 25);
    assert_equal<std::string>("hello", pair.first);
    assert_equal<int>(25, pair.second);
  }

  void test_copy_constructor()
  {
    std::pair<std::string, int> pair("hello", 25);
    std::pair<std::string, int> pair2(pair);
    assert_equal<std::string>(pair.first, pair2.first);
    assert_equal<int>(pair.second, pair2.second);
  }

  void test_assignment()
  {
    std::pair<std::string, int> pair("hello", 25);
    std::pair<std::string, int> pair2;
    pair2 = pair;
    assert_equal<std::string>(pair.first, pair2.first);
    assert_equal<int>(pair.second, pair2.second);
  }

  void test_swap()
  {
    std::pair<std::string, int> pair("hello", 25);
    std::pair<std::string, int> pair2("world", 30);
    pair.swap(pair2);
    assert_equal<std::string>("world", pair.first);
    assert_equal<int>(30, pair.second);
    assert_equal<std::string>("hello", pair2.first);
    assert_equal<int>(25, pair2.second);
  }

  void test_make_pair()
  {
    std::pair<std::string, int> pair = std::make_pair(std::string("hello"), 25);
    assert_equal<std::string>("hello", pair.first);
    assert_equal<int>(25, pair.second);
  }

  test_pair_t() : testcase_t("pair")
  {
    add_test(test_func(&test_pair_t::test_empty_constructor), "Checking that empty constructor initializes members");
    add_test(test_func(&test_pair_t::test_constructor), "Checking that constructor initializes members");
    add_test(test_func(&test_pair_t::test_copy_constructor), "Checking that copy constructor initializes members");
    add_test(test_func(&test_pair_t::test_assignment), "Checking that assignment works");
    add_test(test_func(&test_pair_t::test_swap), "Checking that swap works");
    add_test(test_func(&test_pair_t::test_make_pair), "Checking that make_pair works");
  }
};

#endif // SWAN_TEST_PAIR_INCLUDED
