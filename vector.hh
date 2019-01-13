#ifndef SWAN_VECTOR_INCLUDED
#define SWAN_VECTOR_INCLUDED

#ifdef SWAN_NO_STL

#include <stdlib.h>
#include <string.h>

namespace swan
{
  template <typename T>
  class vector_t {
  public:
    typedef T* iterator;
    typedef const T* const_iterator;

    vector_t();
    vector_t(size_t n, const T& val = T());
    vector_t(const vector_t<T>& other);
    ~vector_t() { clear(); free(m_buffer); }

    vector_t<T>&  operator=(const vector_t<T>& other);
    T&            operator[](size_t index)                    { return m_buffer[index]; }
    const T&      operator[](size_t index)              const { return m_buffer[index]; }

    iterator       begin()                                    { return m_buffer; }
    const_iterator begin()                              const { return m_buffer; }
    iterator       end()                                      { return m_buffer + m_size; }
    const_iterator end()                                const { return m_buffer + m_size; }
    T*             data()                                     { return m_buffer; }
    const T*       data()                               const { return m_buffer; }
    size_t         size()                               const { return m_size; }
    void           push_back(const T& elem);
    void           pop_back()                                 { erase(end()-1); }
    T&             back()                                     { return m_buffer[m_size-1]; }
    const T&       back()                               const { return m_buffer[m_size-1]; }
    T&             front()                                    { return m_buffer[0]; }
    const T&       front()                              const { return m_buffer[0]; }
    iterator       erase(iterator it);
    void           clear();
    void           resize(size_t n, const T& val = T());
  private:
    T*      m_buffer;
    size_t  m_size;
    size_t  m_capacity;
  };

  #define SWAN_CAPACITY_INC 128

  template <typename T>
  vector_t<T>::vector_t()
  {
    m_buffer = (T*)calloc(0, sizeof(T));
    m_size = 0;
    m_capacity = 0;
  }

  template <typename T>
  vector_t<T>::vector_t(size_t n, const T& val)
  {
    m_capacity = (n > 0 && n < SWAN_CAPACITY_INC) ? SWAN_CAPACITY_INC : n;
    m_buffer = (T*)calloc(m_capacity, sizeof(T));
    m_size = n;
    for (size_t i = 0; i < n; ++i) m_buffer[i] = val;
  }

  template <typename T>
  vector_t<T>::vector_t(const vector_t<T>& other)
  {
    m_buffer = (T*)calloc(other.m_capacity, sizeof(T));
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    for (size_t i = 0; i < other.m_size; ++i) m_buffer[i] = other.m_buffer[i];
  }

  template <typename T>
  vector_t<T>& vector_t<T>::operator=(const vector_t<T>& other)
  {
    free(m_buffer);
    m_buffer = (T*)calloc(other.m_capacity, sizeof(T));
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    for (size_t i = 0; i < other.m_size; ++i) m_buffer[i] = other.m_buffer[i];
    return *this;
  }

  template <typename T>
  void vector_t<T>::push_back(const T& elem)
  {
    if (m_size == m_capacity)
    {
      m_capacity += SWAN_CAPACITY_INC;
      m_buffer = (T*)realloc(m_buffer, m_capacity * sizeof(T));
    }
    m_buffer[m_size++] = elem;
  }

  template <typename T>
  typename vector_t<T>::iterator vector_t<T>::erase(vector_t<T>::iterator it)
  {
    size_t index = it - m_buffer;
    m_buffer[index].~T(); // invoke destructor
    memmove(&m_buffer[index], &m_buffer[index+1], (m_size - index - 1) * sizeof(T));
    for (size_t i = index+1; i < m_size; ++i)
    --m_size;
    return &m_buffer[index];
  }

  template <typename T>
  void vector_t<T>::clear()
  {
    for (size_t i = 0; i < m_size; ++i)
    {
      m_buffer[i].~T(); // invoke destructor
    }
    m_buffer = (T*)realloc(m_buffer, SWAN_CAPACITY_INC * sizeof(T));
    m_size = 0;
    m_capacity = SWAN_CAPACITY_INC;
  }

  template <typename T>
  void vector_t<T>::resize(size_t n, const T& val)
  {
    if (n < m_size)
    {
      m_size = n;
    }
    else if (n > m_size)
    {
      if (n > m_capacity)
      {
        m_capacity += (n - m_capacity < SWAN_CAPACITY_INC) ? SWAN_CAPACITY_INC : (n - m_capacity);
        m_buffer = (T*)realloc(m_buffer, m_capacity * sizeof(T));
      }
      for (size_t i = m_size; i < n; ++i) m_buffer[i] = val;
      m_size = n;
    }
  }

  template <typename T>
  bool operator==(const vector_t<T>& lhs, const vector_t<T>& rhs)
  {
    if (lhs.size() != rhs.size()) return false;
    const size_t len = lhs.size();
    for (size_t i = 0; i < len; ++i)
    {
      if (!(lhs[i] == rhs[i])) return false;
    }
    return true;
  }
} // namespace swan

#undef SWAN_CAPACITY_INC

#else // SWAN_NO_STL

#include <vector>

#if (__cplusplus >= 201103L) // check c++11 support
namespace swan
{
  template <typename T>
  using vector_t = std::vector<T>;
}
#else
#define vector_t std::vector
#endif

#endif // SWAN_NO_STL

#endif // SWAN_VECTOR_INCLUDED
