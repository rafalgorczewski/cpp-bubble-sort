#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace hqrp {

  template <typename, typename = void>
  struct is_comparable : std::false_type {};

  template <typename T>
  struct is_comparable<
    T,
    std::void_t<decltype(std::declval<T>() < std::declval<T>())>>
      : std::true_type {};

  template <typename ForwardIter>
  inline constexpr void bubble_sort(ForwardIter begin, ForwardIter end) {
    static_assert(
      std::is_base_of<
        std::forward_iterator_tag,
        typename std::iterator_traits<ForwardIter>::iterator_category>::value,
      "Iterator category tag mismatch: expected forward iterator.");
    static_assert(is_comparable<decltype(*begin)>::value,
                  "Iterator value type is not comparable, therefore you should "
                  "provide your own comparator.");

    const auto count = std::distance(begin, end);
    auto already_sorted = false;
    for (auto i = 0; i + 1 < count; ++i) {
      if (already_sorted) {
        break;
      }
      already_sorted = true;
      auto it = begin;
      for (auto nested_i = 0; nested_i + 1 + i < count; ++nested_i) {
        const auto next_it = std::next(it);
        if (!(*it < *next_it)) {
          std::iter_swap(it, next_it);
          already_sorted = false;
        }
        ++it;
      }
    }
  }

  template <typename ForwardIter, typename Comp>
  inline constexpr void bubble_sort(ForwardIter begin,
                                    ForwardIter end,
                                    Comp comparator) {
    static_assert(
      std::is_base_of<
        std::forward_iterator_tag,
        typename std::iterator_traits<ForwardIter>::iterator_category>::value,
      "Iterator category tag mismatch: expected forward iterator.");
    static_assert(std::is_convertible<
                    std::result_of_t<Comp(
                      typename std::iterator_traits<ForwardIter>::value_type&,
                      typename std::iterator_traits<ForwardIter>::value_type&)>,
                    bool>::value,
                  "Comparator's return value must be convertible to bool.");

    const auto count = std::distance(begin, end);
    auto already_sorted = false;
    for (auto i = 0; i + 1 < count; ++i) {
      if (already_sorted) {
        break;
      }
      already_sorted = true;
      auto it = begin;
      for (auto nested_i = 0; nested_i + 1 + i < count; ++nested_i) {
        const auto next_it = std::next(it);
        if (!comparator(*it, *next_it)) {
          std::iter_swap(it, next_it);
          already_sorted = false;
        }
        ++it;
      }
    }
  }

}  // namespace hqrp
