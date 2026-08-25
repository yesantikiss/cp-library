#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"

#include <iostream>
#include <vector>

#include "tree/heavy_light_decomposition.hpp"

namespace {
    constexpr long long MOD = 998244353;

    struct Affine {
        long long a = 1;
        long long b = 0;
    };

    // firstを適用した後にsecondを適用する。
    Affine compose(const Affine& first, const Affine& second) {
        return {second.a * first.a % MOD,
                (second.a * first.b + second.b) % MOD};
    }

    struct BidirectionalProduct {
        Affine forward;
        Affine backward;
    };

    BidirectionalProduct merge(const BidirectionalProduct& left,
                               const BidirectionalProduct& right) {
        return {compose(left.forward, right.forward),
                compose(right.backward, left.backward)};
    }

    struct SegmentTree {
        int size = 1;
        std::vector<BidirectionalProduct> data;

        explicit SegmentTree(int n) {
            while (size < n) size *= 2;
            data.assign(2 * size, {});
        }

        void set(int position, Affine value) {
            int index = position + size;
            data[index] = {value, value};
            while (index > 1) {
                index /= 2;
                data[index] = merge(data[2 * index], data[2 * index + 1]);
            }
        }

        BidirectionalProduct prod(int left, int right) const {
            BidirectionalProduct left_product, right_product;
            left += size;
            right += size;
            while (left < right) {
                if (left & 1) left_product = merge(left_product, data[left++]);
                if (right & 1) right_product = merge(data[--right], right_product);
                left /= 2;
                right /= 2;
            }
            return merge(left_product, right_product);
        }
    };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<Affine> function(n);
    for (auto& [a, b] : function) std::cin >> a >> b;

    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i + 1 < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    yesantikiss::HeavyLightDecomposition hld(graph);
    SegmentTree segment_tree(n);
    for (int v = 0; v < n; ++v) {
        segment_tree.set(hld.in[v], function[v]);
    }

    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int v;
            Affine value;
            std::cin >> v >> value.a >> value.b;
            segment_tree.set(hld.in[v], value);
        } else {
            int u, v;
            long long x;
            std::cin >> u >> v >> x;

            Affine path_product;
            hld.path_query(u, v, false,
                           [&](int left, int right, bool reverse) {
                               auto product = segment_tree.prod(left, right);
                               const Affine& part = reverse ? product.backward
                                                            : product.forward;
                               path_product = compose(path_product, part);
                           });
            std::cout << (path_product.a * x + path_product.b) % MOD << '\n';
        }
    }
}
