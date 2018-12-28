// inspired by jasmine library: https://jasmine.github.io

#ifndef SWAN_TESTING_INCLUDED
#define SWAN_TESTING_INCLUDED

#include <math.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace swan
{
  namespace testing
  {
    // passing null as parameter decreases indent
    inline std::string _formatandindent(const char* s)
    {
      static size_t numTabs = 0;
      if ( s )
      {
        std::string str = std::string(numTabs, '\t') + s;
        ++numTabs;
        return str;
      }
      else
      {
        if ( numTabs > 0 ) --numTabs;
        return std::string(numTabs, '\t');
      }
    }

    // passing a function pointer as second parameter changes the function used to print a message
    inline void _printstring(const char* s, void (*f)(const char*) = 0)
    {
      static void (* callback)(const char*) = 0;
      if ( f )
      {
        callback = f;
      }
      else
      {
        if ( !callback )
        {
          std::cout << s;
          std::cout.flush();
        }
        else
        {
          callback(s);
        }
      }
    }

    void printcallback(void (*f)(const char* s))
    {
      _printstring(0, f);
    }

    void print(const char* s, bool format = true)
    {
      _printstring(format ? _formatandindent(s ? s : "").c_str() : s);
      if ( format ) _formatandindent(0);
    }

    void printindent(const char* s, bool format = true)
    {
      _printstring(format ? _formatandindent(s ? s : "").c_str() : s);
      if ( !format ) _formatandindent("");
    }

    void println(const char* s, bool format = true)
    {
      print((s + std::string("\n")).c_str(), format);
    }

    void printlnindent(const char* s, bool format = true)
    {
      printindent((s + std::string("\n")).c_str(), format);
    }

    void unindent()
    {
      _formatandindent(0);
    }

    template<typename T>
    class result_t
    {
    private:
      std::string error_expected(T v)
      {
        std::stringstream ss;
        ss << std::setprecision(16) << "expected '" << v << "', got '" << r << "'";
        return ss.str();
      }

      std::string error_unexpected()
      {
        std::stringstream ss;
        ss << std::setprecision(16) << "unexpected '" << r << "'";
        return ss.str();
      }
    public:
      result_t(T v) : r(v) {}
      
      void tobenan()
      {
        if ( r == r )
        {
          std::string str = error_expected(std::numeric_limits<T>::quiet_NaN());
          println("", false);
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }
      
      void tobenull()
      {
        if ( r )
        {
          std::string str = "expected null";
          println("", false);
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }
      
      void tobeptr()
      {
        if ( !r )
        {
          std::string str = "expected pointer";
          println("", false);
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }

      void tobe(T v)
      {
        if ( v != r )
        {
          std::string str = error_expected(v);
          println("", false);      
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }

      void tobenumber(T v)
      {
        if ( (std::numeric_limits<T>::is_integer && v != r) || (!std::numeric_limits<T>::is_integer && std::abs(v - r) > std::numeric_limits<T>::epsilon()*8) || r != r )
        {
          std::string str = error_expected(v);
          println("", false);      
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }
      
      void tobestring(const char* v)
      {
        std::stringstream ss;
        ss << r;
        if ( ss.str() != v )
        {
          std::string str = error_expected(v);
          println("", false);
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }

      void tobeobject(T v)
      {
        if ( v != r )
        {
          std::string str = "object does not match";
          println("", false);      
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }

      void tonotbe(T v)
      {
        if ( (std::numeric_limits<T>::is_integer && v == r) || (!std::numeric_limits<T>::is_integer && std::abs(v - r) <= std::numeric_limits<T>::epsilon()*8) )
        {
          std::string str = error_unexpected();
          println("", false);
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }

      void tonotbestring(const char* v)
      {
        std::stringstream ss;
        ss << r;
        if ( ss.str() == v )
        {
          std::string str = error_unexpected();
          println("", false);
          println(str.c_str());
          #ifdef SWAN_EXCEPTIONS
            throw str.c_str();
          #else
            exit(-1);
          #endif
        }
      }
    private:
      T r;
    };

    inline void describe(const char* s, void (*f)())
    {
      printlnindent(s);
      f();
      unindent();
    }

    inline void it(const char* s, void (*f)())
    {
      printlnindent(s);
      f();
      println("");
      unindent();
    }

    template<typename T>
    result_t<T> expect_noprint(T exp)
    {
      return result_t<T>(exp);
    }

    template<typename T>
    result_t<T> expect(T exp)
    {
      result_t<T> res(exp);
      std::stringstream ss;
      ss << std::setprecision(16) << exp;
      print((" -> " + ss.str()).c_str(), false);
      return res;
    }
  } // namespace testing
} // namespace swan

#endif // SWAN_TESTING_INCLUDED
