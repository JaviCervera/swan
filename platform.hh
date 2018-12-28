#ifndef SWAN_PLATFORM_INCLUDED
#define SWAN_PLATFORM_INCLUDED

#include "string.hh"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace swan
{
  namespace platform
  {
    enum platformid
    {
      pwindows,
      pmacos,
      plinux
    };

    inline platformid platformid()
    {
#if defined(_WIN32)
      return pwindows;
#elif defined(__APPLE__)
      return pmacos;
#elif defined(__linux__)
      return plinux;
#else
      return 0;
#endif
    }

    inline string_t getenv(const char* var)
    {
      string_t env;
#ifdef _MSC_VER
      char* buffer = NULL;
      size_t size;
      _dupenv_s(&buffer, &size, var);
      if ( buffer )
      {
        env = buffer;
        free(buffer);
      }
#else
      char* p = ::getenv(var);
      if ( p ) env = p;
#endif
      return env;
    }

    inline int call(const char* command)
    {
      return system(command);
    }

    inline string_t run(const char* program)
    {
      string_t output;

      // open pipe
      FILE* pipe = popen(program, "rt");
      if ( !pipe ) return output;

      // read pipe
      while ( !feof(pipe) )
      {
        char tmp[128];
        if ( fgets(tmp, 128, pipe) != 0 ) output += tmp;
      }

      // close pipe
      pclose(pipe);

      return output;
    }

    inline void exit(int exitCode)
    {
      exit(exitCode);
    }
  } // namespace platform
} // namespace swan

#ifdef _WIN32
#undef popen
#undef pclose
#endif

#endif // SWAN_PLATFORM_INCLUDED
