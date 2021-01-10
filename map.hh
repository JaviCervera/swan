#ifndef SWAN_MAP_INCLUDED
#define SWAN_MAP_INCLUDED

#ifdef SWAN_NO_STL

#include "pair.hh"
#include "vector.hh"

namespace std
{
  template <typename Key, typename T>
  class map
  {
  public:
    map() {}
    map(const map& other) {}

    map& operator=(const map& other) {}
  private:
    std::vector<std::pair<Key, T>> m;
  };
}

#else // SWAN_NO_STL

#include <map>

#endif // SWAN_NO_STL

#endif // SWAN_MAP_INCLUDED
