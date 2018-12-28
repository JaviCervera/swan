// TODO: use realloc

#ifndef SWAN_VECTOR_INCLUDED
#define SWAN_VECTOR_INCLUDED

#ifdef SWAN_NO_STL

#include <stdlib.h>

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
    ~vector_t() { free(mBuffer); }

    vector_t<T>&  operator=(const vector_t<T>& other);
    T&            operator[](size_t index)                    { return mBuffer[index]; }
    const T&      operator[](size_t index)              const { return mBuffer[index]; }

    iterator       begin()                                    { return mBuffer; }
    const_iterator begin()                              const { return mBuffer; }
    iterator       end()                                      { return mBuffer + mSize; }
    const_iterator end()                                const { return mBuffer + mSize; }
    T&             data()                                     { return mBuffer; }
    const T&       data()                               const { return mBuffer; }
    size_t         size()                               const { return mSize; }
    void           push_back(const T& elem);
    void           pop_back()                                 { erase(size()-1); }
    T&             back()                                     { return mBuffer[mSize-1]; }
    const T&       back()                               const { return mBuffer[mSize-1]; }
    T&             front()                                    { return mBuffer[0]; }
    const T&       front()                              const { return mBuffer[0]; }
    void           erase(size_t index);
    void           erase_elem(const T& elem);
    void           erase_elems(const T& elem);
    void           clear();
    void           resize(size_t n, const T& val = T());
  private:
    T*      mBuffer;
    size_t  mSize;
    size_t  mCapacity;
  };

  #define SWAN_CAPACITY_INC 128

  template <typename T>
  vector_t<T>::vector_t()
  {
    mBuffer = (T*)calloc(0, sizeof(T));
    mSize = 0;
    mCapacity = 0;
  }

  template <typename T>
  vector_t<T>::vector_t(size_t n, const T& val)
  {
    mCapacity = (n > 0 && n < SWAN_CAPACITY_INC) ? SWAN_CAPACITY_INC : n;
    mBuffer = (T*)calloc(mCapacity, sizeof(T));
    mSize = n;
    for (size_t i = 0; i < n; ++i) mBuffer[i] = val;
  }

  template <typename T>
  vector_t<T>::vector_t(const vector_t<T>& other)
  {
    mBuffer = (T*)calloc(other.mCapacity, sizeof(T));
    mSize = other.mSize;
    mCapacity = other.mCapacity;
    for (size_t i = 0; i < other.mSize; ++i) mBuffer[i] = other.mBuffer[i];
  }

  template <typename T>
  vector_t<T>& vector_t<T>::operator=(const vector_t<T>& other)
  {
    free(mBuffer);
    mBuffer = (T*)calloc(other.mCapacity, sizeof(T));
    mSize = other.mSize;
    mCapacity = other.mCapacity;
    for (size_t i = 0; i < other.mSize; ++i) mBuffer[i] = other.mBuffer[i];
    return *this;
  }

  template <typename T>
  void vector_t<T>::push_back(const T& elem)
  {
    if ( mCapacity == mSize ) {
      mCapacity += SWAN_CAPACITY_INC;
      T* oldBuffer = mBuffer;
      mBuffer = (T*)calloc(mCapacity, sizeof(T));
      for (size_t i = 0; i < mSize; ++i) mBuffer[i] = oldBuffer[i];
      free(oldBuffer);
    }
    mBuffer[mSize++] = elem;
  }

  template <typename T>
  void vector_t<T>::erase(size_t index)
  {
    for (size_t i = index+1; i < mSize; ++i)
    {
      mBuffer[i-1] = mBuffer[i];
    }
    --mSize;
  }

  template <typename T>
  void vector_t<T>::erase_elem(const T& elem)
  {
    for (size_t i = 0; i < mSize; ++i)
    {
      if (mBuffer[i] == elem)
      {
        erase(i);
        break;
      }
    }
  }

  template <typename T>
  void vector_t<T>::erase_elems(const T& elem)
  {
    size_t i = 0;
    while (i < mSize)
    {
      if (mBuffer[i] == elem)
      {
        erase(i);
      }
      else
      {
        ++i;
      }
    }
  }

  template <typename T>
  void vector_t<T>::clear()
  {
    free(mBuffer);
    mBuffer = (T*)calloc(SWAN_CAPACITY_INC, sizeof(T));
    mSize = 0;
    mCapacity = SWAN_CAPACITY_INC;
  }

  template <typename T>
  void vector_t<T>::resize(size_t n, const T& val)
  {
    if (n < mSize)
    {
      mSize = n;
    }
    else if (n > mSize)
    {
      if (n > mCapacity)
      {
        mCapacity += (n - mCapacity < SWAN_CAPACITY_INC) ? SWAN_CAPACITY_INC : (n - mCapacity);
        T* oldBuffer = mBuffer;
        mBuffer = (T*)calloc(mCapacity, sizeof(T));
        for (size_t i = 0; i < mSize; ++i) mBuffer[i] = oldBuffer[i];
        free(oldBuffer);
      }
      for (size_t i = mSize; i < n; ++i) mBuffer[i] = val;
      mSize = n;
    }
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
