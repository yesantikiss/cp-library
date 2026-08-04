#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace yesantikiss {
    namespace hash_detail {
        inline std::uint64_t splitmix64(std::uint64_t x) {
            x += 0x9e3779b97f4a7c15ULL;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
            return x ^ (x >> 31);
        }

        inline std::uint64_t random_seed() {
            static const std::uint64_t seed =
                static_cast<std::uint64_t>(
                    std::chrono::steady_clock::now()
                        .time_since_epoch()
                        .count());
            return seed;
        }
    }

    struct custom_hash {
        template<class T>
        std::size_t operator()(const T& value) const {
            return static_cast<std::size_t>(hash_detail::splitmix64(
                static_cast<std::uint64_t>(std::hash<T>{}(value)) +
                hash_detail::random_seed()));
        }

        template<class T, class U>
        std::size_t operator()(const std::pair<T, U>& value) const {
            std::uint64_t first =
                static_cast<std::uint64_t>((*this)(value.first));
            std::uint64_t second =
                static_cast<std::uint64_t>((*this)(value.second));
            return static_cast<std::size_t>(hash_detail::splitmix64(
                first ^ (second + 0x9e3779b97f4a7c15ULL +
                         (first << 6) + (first >> 2))));
        }
    };

    template<
        class Key,
        class T,
        class Hash = custom_hash,
        class KeyEqual = std::equal_to<Key>,
        class Allocator = std::allocator<std::pair<const Key, T>>>
    using umap =
        std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

    template<
        class Key,
        class Hash = custom_hash,
        class KeyEqual = std::equal_to<Key>,
        class Allocator = std::allocator<Key>>
    using uset =
        std::unordered_set<Key, Hash, KeyEqual, Allocator>;
}
