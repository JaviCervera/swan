#ifndef SWAN_STRMANIP_INCLUDED
#define SWAN_STRMANIP_INCLUDED

#ifdef _WIN32
#define realpath(N,R) _fullpath((R),(N),_MAX_PATH)
#endif

#include "string.hh"
#include "vector.hh"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace swan
{
  namespace strmanip
  {
    template <typename T>
    string_t fromnumber(const T& val, const char* format)
    {
      char buf[32];
      sprintf(buf, format, val);
      return string_t(buf);
    }

    inline string_t fromint(int val)
    {
      return fromnumber(val, "%i");
    }

    inline string_t fromdouble(double val)
    {
      return fromnumber(val, "%f");
    }

    template <typename T>
    T tonumber(const string_t& str, const char* format)
    {
      T ret = 0;
      sscanf(str.c_str(), format, &ret);
      return ret;
    }

    inline int toint(const string_t& str)
    {
      return tonumber<int>(str, "%i");
    }

    inline float tofloat(const string_t& str)
    {
      return tonumber<float>(str, "%f");
    }

    inline double todouble(const string_t& str)
    {
      return tonumber<double>(str, "%lf");
    }

    inline string_t replace_all(const string_t& str, const string_t& find, const string_t& rep)
    {
      string_t strcopy = str;
      size_t find_pos = strcopy.find(find);
      while (find_pos != string_t::npos)
      {
        strcopy.replace(find_pos, find.length(), rep);
        find_pos = strcopy.find(find, find_pos + rep.length());
      }
      return strcopy;
    }

    inline string_t stripext(const string_t& filename)
    {
      return filename.substr(0, filename.find('.'));
    }

    inline string_t stripdir(const string_t& filename)
    {
      string_t filenameCopy = replace_all(filename, "\\", "/");
      return filenameCopy.substr(filenameCopy.rfind('/')+1, filenameCopy.length() - filenameCopy.rfind('/')-1);
    }

    inline string_t extractext(const string_t& filename)
    {
      return filename.substr(filename.rfind('.')+1, filename.length() - filename.rfind('.')-1);
    }

    inline string_t extractdir(const string_t& filename)
    {
      string_t filenameCopy = replace_all(filename, "\\", "/");
      return filenameCopy.substr(0, filenameCopy.rfind('/'));
    }

    inline string_t read(const string_t& filename)
    {
      FILE* f = fopen(filename.c_str(), "rb");
      if (!f) return "";
      fseek(f, 0, SEEK_END);
      long size = ftell(f);
      fseek(f, 0, SEEK_SET);
      char* buf = new char[size+1];
      fread(buf, sizeof(char), size, f);
      buf[size] = '\0';
      string_t str(buf);
      delete[] buf;
      return str;
    }

    inline void write(const string_t& str, const string_t& filename, bool append = true)
    {
      FILE* f = fopen(filename.c_str(), append ? "ab" : "wb");
      if (!f) return;
      fwrite(str.c_str(), sizeof(char), str.length(), f);
      fclose(f);
    }

    inline vector_t<string_t> split(const string_t& str, char delim)
    {
      vector_t<string_t> arr;
      if (str.length() == 0 || delim == 0) return arr;
      string_t out;
      for (size_t i = 0; i < str.length(); ++i)
      {
        const char c = str[i];
        if (c == delim)
        {
          arr.push_back(out);
          out = "";
        }
        else
        {
          out += c;
        }
      }
      arr.push_back(out);
      return arr;
    }

    // todo: optimize this
    inline string_t upper(const string_t& str)
    {
      string_t out;
      for (size_t i = 0; i < str.length(); ++i) out += toupper(str[i]);
      return out;
    }

    // todo optimize this
    inline string_t lower(const string_t& str)
    {
      string_t out;
      for (size_t i = 0; i < str.length(); ++i)
        out += tolower(str[i]);
      return out;
    }

    inline string_t ltrim(const string_t& str)
    {
      // count spaces at the beginning
      size_t i = 0;
      while (i < str.length() && isspace(str[i])) ++i;

      // return trimmed string
      return str.substr(i);
    }

    inline string_t rtrim(const string_t& str)
    {
      // look for first non space on the right
      int i = str.length() - 1;
      size_t pos = string_t::npos;
      while (i > 0 && pos == string_t::npos)
      {
        if ( !isspace(str[i]) ) pos = i + 1;
        --i;
      }

      if (pos == string_t::npos) pos = str.length();

      // return trimmed string
      return str.substr(0, pos);
    }

    inline string_t trim(const string_t& str)
    {
      return rtrim(ltrim(str));
    }

    inline string_t lset(const string_t& str, size_t length, char c)
    {
      string_t out = str;
      if (out.length() > length)
      {
        out.resize(length);
      }
      else if (out.length() < length)
      {
        out = string_t(length - out.length(), c) + out;
      }
      return out;
    }

    inline string_t rset(const string_t& str, size_t length, char c)
    {
      string_t out = str;
      out.resize(length, c);
      return out;
    }

#ifdef SWAN_TIME_INCLUDED
    inline string_t parsetimeinfo(const time::timeinfo_t& ti, bool parsedate = true, bool parsetime = true)
    {
      string_t str;
      
      if (parsedate)
      {
        str += lset(fromint(ti.year), 4, '0');
        str += "/";
        str += lset(fromint(ti.mon), 2, '0');
        str += "/";
        str +=  lset(fromint(ti.day), 2, '0');
      }

      if (parsetime)
      {
        if ( str != "" ) str += " ";
        str += lset(fromint(ti.hour), 2, '0');
        str += ":";
        str += lset(fromint(ti.min), 2, '0');
        str += ":";
        str +=  lset(fromint(ti.sec), 2, '0');
      }

      return str;
    }
#endif
  } // namespace strmanip
} // namespace swan

#endif // SWAN_STRMANIP_INCLUDED
