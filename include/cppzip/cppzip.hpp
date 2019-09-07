#ifndef CPPZIP_HEADER_INCLUDED
#define CPPZIP_HEADER_INCLUDED

#include "tcb/span.hpp"

#include <type_traits>
#include <utility>

namespace cppzip {

template <typename AElementType, typename AType, typename BElementType,
          typename BType>
class ZipIterator {
public:
  using reference_type = std::pair<AElementType &, BElementType &>;

  ZipIterator(AType a, BType b) : a(a), b(b) {
  }

  bool operator!=(
      const ZipIterator<AElementType, AType, BElementType, BType> &other) {
    return a != other.a || b != other.b;
  }

  ZipIterator<AElementType, AType, BElementType, BType> operator++() {
    ++a;
    ++b;
    return *this;
  }

  reference_type operator*() {
    return reference_type(*a, *b);
  }

private:
  AType a;
  BType b;
};

template <typename AElementType, typename ABeginType, typename AEndType,
          typename BElementType, typename BBeginType, typename BEndType>
class ZipIterable {
public:
  ZipIterable(ABeginType abegin, AEndType aend, BBeginType bbegin,
              BEndType bend)
      : abegin(abegin), aend(aend), bbegin(bbegin), bend(bend) {
  }

private:
  ABeginType abegin;
  AEndType aend;
  BBeginType bbegin;
  BEndType bend;

  template <typename AElementType_, typename ABeginType_, typename AEndType_,
            typename BElementType_, typename BBeginType_, typename BEndType_>
  friend ZipIterator<AElementType_, ABeginType_, BElementType_, BBeginType_>
  begin(ZipIterable<AElementType_, ABeginType_, AEndType_, BElementType_,
                    BBeginType_, BEndType_> &zIt);

  template <typename AElementType_, typename ABeginType_, typename AEndType_,
            typename BElementType_, typename BBeginType_, typename BEndType_>
  friend ZipIterator<AElementType_, AEndType_, BElementType_, BEndType_>
  end(ZipIterable<AElementType_, ABeginType_, AEndType_, BElementType_,
                  BBeginType_, BEndType_> &zIt);
};

template <typename AElementType, typename ABeginType, typename AEndType,
          typename BElementType, typename BBeginType, typename BEndType>
ZipIterator<AElementType, ABeginType, BElementType, BBeginType>
begin(ZipIterable<AElementType, ABeginType, AEndType, BElementType, BBeginType,
                  BEndType> &zIt) {
  return ZipIterator<AElementType, ABeginType, BElementType, BBeginType>(
      zIt.abegin, zIt.bbegin);
}

template <typename AElementType, typename ABeginType, typename AEndType,
          typename BElementType, typename BBeginType, typename BEndType>
ZipIterator<AElementType, AEndType, BElementType, BEndType>
end(ZipIterable<AElementType, ABeginType, AEndType, BElementType, BBeginType,
                BEndType> &zIt) {
  return ZipIterator<AElementType, AEndType, BElementType, BEndType>(zIt.aend,
                                                                     zIt.bend);
}

template <typename T, size_t TExtent, typename U, size_t UExtent>
auto zip(tcb::span<T, TExtent> a, tcb::span<U, UExtent> b)
    -> ZipIterable<T, decltype(begin(a)), decltype(end(a)), U,
                   decltype(begin(b)), decltype(end(b))> {
  return ZipIterable<T, decltype(begin(a)), decltype(end(a)), U,
                     decltype(begin(b)), decltype(end(b))>(begin(a), end(a),
                                                           begin(b), end(b));
}

template <typename T, size_t TExtent, typename U, size_t UExtent>
auto czip(tcb::span<T, TExtent> a, tcb::span<U, UExtent> b)
    -> ZipIterable<const T, decltype(begin(a)), decltype(end(a)), const U,
                   decltype(begin(b)), decltype(end(b))> {
  return ZipIterable<const T, decltype(begin(a)), decltype(end(a)), const U,
                     decltype(begin(b)), decltype(end(b))>(begin(a), end(a),
                                                           begin(b), end(b));
}

template <typename T, typename U>
auto zip(T &a, U &b) -> ZipIterable<
    typename decltype(tcb::make_span(a))::element_type,
    decltype(begin(tcb::make_span(a))), decltype(end(tcb::make_span(a))),
    typename decltype(tcb::make_span(b))::element_type,
    decltype(begin(tcb::make_span(b))), decltype(end(tcb::make_span(b)))> {
  return zip(tcb::make_span(a), tcb::make_span(b));
}

template <typename T, typename U>
auto czip(T &a, U &b) -> ZipIterable<
    const typename decltype(tcb::make_span(a))::element_type,
    decltype(begin(tcb::make_span(a))), decltype(end(tcb::make_span(a))),
    const typename decltype(tcb::make_span(b))::element_type,
    decltype(begin(tcb::make_span(b))), decltype(end(tcb::make_span(b)))> {
  return czip(tcb::make_span(a), tcb::make_span(b));
}

} // namespace cppzip

#endif
