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
    typedef pair<Key, T>* iterator;
    typedef const pair<Key, T>* const_iterator;

    map() {}
    map(const map& other) : m(other.m) {}

    map& operator=(const map& other) { m = other.m; return *this; }
    T& operator[](const Key& key);
    iterator begin() { return m.begin(); }
    const_iterator begin() const { return m.begin(); }
    iterator end() { return m.end(); }
    const_iterator end() const { return m.end(); }
    size_t count(const Key& key) const { return (find(key) != end()) ? 1 : 0; }
    iterator find(const Key& key) { return const_cast<iterator>(static_cast<const map<Key, T>*>(this)->find(key)); }
    const_iterator find(const Key& key) const;
    void erase(const_iterator pos) { m.erase(pos); }
    size_t erase(const Key& key);
    void clear() { m.clear(); }
    bool empty() const { return size() == 0; }
    size_t size() const { return m.size(); }
  private:
    std::vector<std::pair<Key, T> > m;
  };

  template <typename Key, typename T>
  T& map<Key, T>::operator[](const Key& key) {
    iterator it = find(key);
    if (it == end()) {
      m.push_back(std::pair(key, T()));
      it = end() - 1;
    }
    return it->second;
  }

  template <typename Key, typename T>
  const_iterator map<Key, T>::find(const Key& key) const {
    for (const_iterator<Key, T> it = begin(); it != end(); ++it) {
      if (*it.first == key) {
        return it;
      }
    }
    return end();
  }

  template <typename Key, typename T>
  size_t map<Key, T>::erase(const Key& key) {
    const_iterator it = find(key);
    if (it != end()) {
      erase(it);
      return 1;
    } else {
      return 0;
    }
  }
}

#else // SWAN_NO_STL

#include <map>

#endif // SWAN_NO_STL

#endif // SWAN_MAP_INCLUDED
