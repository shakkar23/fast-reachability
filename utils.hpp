#pragma once
#include <type_traits>
#include <utility>
#include <span>
#include <algorithm>
namespace reachability {
  template<typename F, std::size_t... S>
  [[gnu::always_inline]]
  constexpr void static_for(F&& function, std::index_sequence<S...>) {
      int unpack[] = {0,
          (void(function(std::integral_constant<std::size_t, S>{})), 0)...
      };

      (void) unpack;
  }

  template<std::size_t iterations, typename F>
  [[gnu::always_inline]]
  constexpr void static_for(F&& function) {
      static_for(std::forward<F>(function), std::make_index_sequence<iterations>());
  }

  template <typename T, std::size_t N>
  struct static_vector {
    static constexpr std::size_t capacity = N;
    T data[N];
    std::size_t used;
    template <std::size_t M>
    constexpr static_vector(std::span<T, M> arr): used(M) {
      static_assert(M <= N);
      std::copy(arr.begin(), arr.end(), data);
    }
    static_vector() = delete;
    constexpr std::size_t size() const {
      return used;
    }
    constexpr const T &operator[](std::size_t i) const {
      return data[i];
    }
    constexpr T &operator[](std::size_t i) {
      return data[i];
    }
  };
}