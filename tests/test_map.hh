#ifndef SWAN_TEST_MAP_INCLUDED
#define SWAN_TEST_MAP_INCLUDED

#include "../map.hh"
#include "../string.hh"
#include "../testing.hh"

struct test_map_t : public swan::testcase_t
{
  void test_empty_constructor()
  {
    std::map<std::string, int> map;
    assert_equal<int>(0, map.size());
    assert_equal<bool>(true, map.empty());
  }

  void test_insertion()
  {
    std::map<std::string, int> map;
    map["number"] = 100;
    assert_equal<int>(100, map["number"]);
  }

  void test_replacement()
  {
    std::map<std::string, int> map;
    map["number"] = 100;
    assert_equal<int>(100, map["number"]);
    map["number"] = 200;
    assert_equal<int>(200, map["number"]);
  }

  void test_value_deletion()
  {
    std::map<std::string, int> map;
    map["number"] = 100;
    assert_equal<int>(100, map["number"]);
    map.erase("number");
    assert_equal<int>(0, map["number"]);
  }

  void test_it_deletion()
  {
    std::map<std::string, int> map;
    map["number"] = 100;
    assert_equal<int>(100, map["number"]);
    map.erase(map.begin());
    assert_equal<int>(0, map["number"]);
  }

  void test_clear()
  {
    std::map<std::string, int> map;
    map["number1"] = 100;
    map["number2"] = 200;
    map["number3"] = 300;
    assert_equal<int>(100, map["number1"]);
    assert_equal<int>(200, map["number2"]);
    assert_equal<int>(300, map["number3"]);
    map.clear();
    assert_equal<int>(0, map.size());
    assert_equal<bool>(true, map.empty());
  }

  void test_count()
  {
    std::map<std::string, int> map;
    map["number"] = 100;
    assert_equal<int>(1, map.count("number"));
    assert_equal<int>(0, map.count("other"));
  }

  void test_find()
  {
    std::map<std::string, int> map;
    map["one"] = 1;
    map["two"] = 2;
    map["three"] = 3;
    assert_equal<std::string>("two", map.find("two")->first);
    assert_equal<int>(2, map.find("two")->second);
  }

  test_map_t() : testcase_t("map")
  {
    add_test(test_func(&test_map_t::test_empty_constructor), "Checking that empty constructor has no elements.");
    add_test(test_func(&test_map_t::test_insertion), "Checking insertion.");
    add_test(test_func(&test_map_t::test_replacement), "Checking replacement.");
    add_test(test_func(&test_map_t::test_value_deletion), "Checking deletion by value.");
    add_test(test_func(&test_map_t::test_it_deletion), "Checking deletion by iterator.");
    add_test(test_func(&test_map_t::test_clear), "Checking that clear works.");
    add_test(test_func(&test_map_t::test_count), "Checking that count works.");
    add_test(test_func(&test_map_t::test_find), "Checking that find works.");
  }
};

#endif // SWAN_TEST_MAP_INCLUDED
