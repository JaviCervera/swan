#ifndef SWAN_PAIR_INCLUDED
#define SWAN_PAIR_INCLUDED

#ifdef SWAN_NO_STL

namespace std
{
  template <typename T1, typename T2>
  class pair
  {
  public:
    T1 first;
    T2 second;

    pair() {}
    pair(const pair& other) : first(other.first), second(other.second) {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}

    pair& operator=(const pair& other) { first = other.first; second = other.second; return *this; }
    void swap(pair& other) { pair temp(*this); *this = other; other = temp; }
  };

  template <typename T1, typename T2>
  std::pair<T1,T2> make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }
}

#else // SWAN_NO_STL

#include <utility>

#endif // SWAN_NO_STL

#endif // SWAN_PAIR_INCLUDED
