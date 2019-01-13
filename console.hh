#ifndef SWAN_CONSOLE_INCLUDED
#define SWAN_CONSOLE_INCLUDED

#include "string.hh"

namespace swan
{
  namespace console
  {
    inline void print(const string_t& msg)
    {
      printf("%s", msg.c_str());
    }

    inline void println(const string_t& msg)
    {
      printf("%s\n", msg.c_str());
      fflush(stdout);
    }

    inline string_t input(const string_t& prompt)
    {
      char buffer[1024];
      printf("%s", prompt.c_str());
      fgets(buffer, 1024, stdin);
      return buffer;
    }
  }
}

#endif // SWAN_CONSOLE_INCLUDED
