// note: on windows, you need to link to winmm to use time module

#ifndef SWAN_TIME_INCLUDED
#define SWAN_TIME_INCLUDED

#if defined(_WIN32)
//#define WIN32_LEAN_AND_MEAN
//#include <Windows.h>
//#include <Mmsystem.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#elif defined(__linux__)
#include <sys/sysinfo.h>
#include <sys/time.h>
#endif
#include <time.h>

#ifdef _WIN32
extern "C" unsigned int __stdcall timeGetTime();
extern "C" void __stdcall Sleep(unsigned int);
#endif

namespace swan
{
  namespace time
  {
    struct timeinfo_t
    {
      int year;
      int mon;
      int day;
      int hour;
      int min;
      int sec;
    };

    inline unsigned int millisecs()
    {
#if defined(_WIN32)
      return timeGetTime();
#elif defined(__linux__)
      static long basetime = -1;
      long t;
      struct timeval tv;
      gettimeofday(&tv, 0);
      t = tv.tv_sec * 1000;
      t += tv.tv_usec / 1000;
      if ( basetime == -1 )
      {
        struct sysinfo info;
        sysinfo(&info);
        basetime = t - info.uptime * 1000;
      }
      return t - basetime;
#elif defined(__APPLE__)
      double t;
      UnsignedWide uw;
      Microseconds( &uw );
      t=(uw.hi<<(32-9))|(uw.lo>>9);
      return t/(1000.0/512.0);
#endif
    }

    inline void delay(unsigned int msecs)
    {
#if defined(_WIN32)
      Sleep(msecs);
#else
      struct timespec sleepval = { 0 };
      sleepval.tv_sec = msecs / 1000;
      sleepval.tv_nsec = (msecs - sleepval.tv_sec * 1000) * 1000000L;
      nanosleep(&sleepval, (struct timespec*)0);
#endif
    }

    inline timeinfo_t timeinfo()
    {
      // get local time
      time_t timer;
      ::time(&timer);
#ifdef _MSC_VER
      tm ti = { 0 };
      localtime_s(&ti, &timer);
      tm* pti = &ti;
#else
      tm* pti = localtime(&timer);
#endif

      timeinfo_t t;
      t.year = pti->tm_year+1900;
      t.mon = pti->tm_mon+1;
      t.day = pti->tm_mday;
      t.hour = pti->tm_hour;
      t.min = pti->tm_min;
      t.sec = pti->tm_sec;
      return t;
    }
  } // namespace time
} // namespace swan

#endif // SWAN_TIME_INCLUDED
