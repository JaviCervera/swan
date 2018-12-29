// inspired by jasmine library: https://jasmine.github.io

#ifndef SWAN_TESTING_INCLUDED
#define SWAN_TESTING_INCLUDED

#include "string.h"
#include "vector.hh"

namespace swan
{
  class testcase_t
  {
  public:
    typedef void(testcase_t::*test_func)();

    testcase_t(const char* name) : name(name), assert_ok(true) {}

    template<typename T>
    void assert_equal(const T& a, const T& b) { assert_ok = (a == b); }

    template<typename T>
    void assert_notequal(const T& a, const T& b) { assert_ok = (a != b); }

    virtual void init() {}
    virtual void setup() {}
    void run();

    static void print_callback(void(*func)(const char*), const char* msg = NULL);
  protected:
    void add_test(test_func f, const char* msg);
  private:
    string_t name;
    vector_t<test_func> test_funcs;
    vector_t<string_t> test_msgs;
    bool assert_ok;

    static void std_print(const char* s);
  };

  inline void testcase_t::run()
  {
    print_callback(NULL, ("# Testing " + name + "\n").c_str());
    init();
    for (size_t i = 0; i < test_funcs.size(); ++i)
    {
      assert_ok = true;
      (this->*test_funcs[i])();
      print_callback(NULL, ("* " + test_msgs[i] + " -> " + (assert_ok ? "OK" : "FAIL") + "\n").c_str());
    }
    print_callback(NULL, "\n");
  }

  inline void testcase_t::add_test(test_func f, const char* msg)
  {
    test_funcs.push_back(f);
    test_msgs.push_back(msg);
  }

  inline void testcase_t::print_callback(void(*func)(const char*), const char* msg)
  {
    static void(*callback)(const char*) = std_print;
    if (func)
    {
      callback = func;
    }
    else
    {
      callback(msg);
    }
  }

  inline void testcase_t::std_print(const char* s)
  {
    printf("%s", s);
  }
} // namespace swan

#endif // SWAN_TESTING_INCLUDED
