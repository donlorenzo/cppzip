#ifndef CPPZIP_HEADER_INCLUDED
#define CPPZIP_HEADER_INCLUDED


#include <iterator>
#include <type_traits>

namespace cppzip {

template <typename AIteratorType, typename BIteratorType> class ZipIterator {

private:
  AIteratorType aIt;
  BIteratorType bIt;

public:
  ZipIterator(AIteratorType aIt, BIteratorType bIt) : aIt(aIt), bIt(bIt) {
  }

  bool operator!=(const ZipIterator<AIteratorType, BIteratorType> &other) {
    return aIt != other.aIt || bIt != other.bIt;
  }

  auto operator++() -> ZipIterator<AIteratorType, BIteratorType> {
    ++aIt;
    ++bIt;
    return *this;
  }

  auto operator*() -> std::pair<decltype(*aIt), decltype(*bIt)> {
    return std::pair<decltype(*aIt), decltype(*bIt)>(*aIt, *bIt);
  }
};

template <typename AType, typename BType> class ZipIterable {
private:
  AType &a;
  BType &b;

public:
  ZipIterable(AType &a, BType &b) : a(a), b(b) {
  }

  auto begin()
      -> ZipIterator<decltype(std::begin(a)), decltype(std::begin(b))> {
    using std::begin;
    return ZipIterator<decltype(begin(a)), decltype(begin(b))>(begin(a),
                                                               begin(b));
  }

  auto end() -> ZipIterator<decltype(std::end(a)), decltype(std::end(b))> {
    using std::end;
    return ZipIterator<decltype(end(a)), decltype(end(b))>(end(a), end(b));
  }
};

template <typename T, typename U> auto zip(T &a, U &b) -> ZipIterable<T, U> {
  return ZipIterable<T, U>(a, b);
}

template <class T>
constexpr typename std::add_const<T>::type &as_const(T &t) noexcept {
  return t;
}

template <typename T, typename U>
auto czip(T &a, U &b) -> ZipIterable<typename std::add_const<T>::type,
                                     typename std::add_const<U>::type> {
  return zip(cppzip::as_const(a), cppzip::as_const(b));
}

} // namespace cppzip

#endif
