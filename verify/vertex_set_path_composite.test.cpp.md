---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: Heavy-Light Decomposition
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "#line 1 \"verify/vertex_set_path_composite.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\n\n#include <iostream>\n\
    #include <vector>\n\n#line 2 \"tree/heavy_light_decomposition.hpp\"\n\n#include\
    \ <algorithm>\n#include <tuple>\n#include <utility>\n#line 7 \"tree/heavy_light_decomposition.hpp\"\
    \n\nnamespace yesantikiss {\n    struct HeavyLightDecomposition {\n        int\
    \ n = 0;\n        int root = -1;\n        std::vector<int> parent;\n        std::vector<int>\
    \ depth;\n        std::vector<int> size;\n        std::vector<int> in;\n     \
    \   std::vector<int> out;\n        std::vector<int> head;\n        std::vector<int>\
    \ heavy;\n        std::vector<int> vertex;\n\n        HeavyLightDecomposition()\
    \ = default;\n\n        explicit HeavyLightDecomposition(\n            const std::vector<std::vector<int>>&\
    \ graph, int root_ = 0) {\n            build(graph, root_);\n        }\n\n   \
    \     void build(const std::vector<std::vector<int>>& graph, int root_ = 0) {\n\
    \            init(static_cast<int>(graph.size()));\n            if (n == 0) return;\n\
    \            root = root_;\n\n            std::vector<int> order{root};\n    \
    \        parent[root] = root;\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         order.push_back(to);\n                }\n            }\n\n         \
    \   for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {\n        \
    \        int v = order[i];\n                int largest_size = 0;\n          \
    \      for (int to : graph[v]) {\n                    if (parent[to] != v) continue;\n\
    \                    size[v] += size[to];\n                    if (size[to] >\
    \ largest_size) {\n                        largest_size = size[to];\n        \
    \                heavy[v] = to;\n                    }\n                }\n  \
    \          }\n\n            int timer = 0;\n            std::vector<std::pair<int,\
    \ int>> pending{{root, root}};\n            while (!pending.empty()) {\n     \
    \           auto [v, chain_head] = pending.back();\n                pending.pop_back();\n\
    \n                for (; v != -1; v = heavy[v]) {\n                    head[v]\
    \ = chain_head;\n                    in[v] = timer;\n                    vertex[timer++]\
    \ = v;\n\n                    for (int to : graph[v]) {\n                    \
    \    if (parent[to] == v && to != heavy[v]) {\n                            pending.emplace_back(to,\
    \ to);\n                        }\n                    }\n                }\n\
    \            }\n\n            for (int v = 0; v < n; ++v) {\n                if\
    \ (in[v] != -1) out[v] = in[v] + size[v];\n            }\n        }\n\n      \
    \  int edge_vertex(int u, int v) const {\n            return depth[u] > depth[v]\
    \ ? u : v;\n        }\n\n        int lca(int u, int v) const {\n            while\
    \ (head[u] != head[v]) {\n                if (depth[head[u]] > depth[head[v]])\
    \ {\n                    u = parent[head[u]];\n                } else {\n    \
    \                v = parent[head[v]];\n                }\n            }\n    \
    \        return depth[u] < depth[v] ? u : v;\n        }\n\n        int dist(int\
    \ u, int v) const {\n            int ancestor = lca(u, v);\n            return\
    \ depth[u] + depth[v] - 2 * depth[ancestor];\n        }\n\n        bool is_ancestor(int\
    \ ancestor, int v) const {\n            return in[ancestor] <= in[v] && out[v]\
    \ <= out[ancestor];\n        }\n\n        std::pair<int, int> subtree_vertex(int\
    \ v) const {\n            return {in[v], out[v]};\n        }\n\n        // \u5404\
    \u8FBA\u3092\u6DF1\u3044\u65B9\u306E\u9802\u70B9\u306B\u5BFE\u5FDC\u3055\u305B\
    \u305F\u3068\u304D\u306E\u90E8\u5206\u6728\u5185\u306E\u8FBA\u3002\n        std::pair<int,\
    \ int> subtree_edge(int v) const {\n            return {in[v] + 1, out[v]};\n\
    \        }\n\n        // u -> v \u306E\u9806\u306B\u3001\u30D1\u30B9\u3092\u534A\
    \u958B\u533A\u9593\u3078\u5206\u89E3\u3059\u308B\u3002\n        // reverse=true\
    \ \u306E\u533A\u9593\u306F r-1, ..., l \u306E\u9806\u306B\u8AAD\u3080\u3002\n\
    \        template <class F>\n        void path_query(int u, int v, bool edge,\
    \ F&& callback) const {\n            std::vector<std::tuple<int, int, bool>> right;\n\
    \n            while (head[u] != head[v]) {\n                if (depth[head[u]]\
    \ > depth[head[v]]) {\n                    callback(in[head[u]], in[u] + 1, true);\n\
    \                    u = parent[head[u]];\n                } else {\n        \
    \            right.emplace_back(in[head[v]], in[v] + 1, false);\n            \
    \        v = parent[head[v]];\n                }\n            }\n\n          \
    \  if (depth[u] > depth[v]) {\n                int left = in[v] + (edge ? 1 :\
    \ 0);\n                int right_end = in[u] + 1;\n                if (left <\
    \ right_end) callback(left, right_end, true);\n            } else {\n        \
    \        int left = in[u] + (edge ? 1 : 0);\n                int right_end = in[v]\
    \ + 1;\n                if (left < right_end) callback(left, right_end, false);\n\
    \            }\n\n            std::reverse(right.begin(), right.end());\n    \
    \        for (auto [left, right_end, reverse] : right) {\n                callback(left,\
    \ right_end, reverse);\n            }\n        }\n\n        template <class S,\
    \ class Op, class Get>\n        S path_fold(int u, int v, bool edge, Op op, S\
    \ identity,\n                    Get get) const {\n            S result = identity;\n\
    \            path_query(u, v, edge,\n                       [&](int left, int\
    \ right, bool reverse) {\n                           result = op(result, get(left,\
    \ right, reverse));\n                       });\n            return result;\n\
    \        }\n\n    private:\n        void init(int size_) {\n            n = size_;\n\
    \            root = -1;\n            parent.assign(n, -1);\n            depth.assign(n,\
    \ 0);\n            size.assign(n, 1);\n            in.assign(n, -1);\n       \
    \     out.assign(n, -1);\n            head.assign(n, -1);\n            heavy.assign(n,\
    \ -1);\n            vertex.assign(n, -1);\n        }\n    };\n}\n#line 7 \"verify/vertex_set_path_composite.test.cpp\"\
    \n\nnamespace {\n    constexpr long long MOD = 998244353;\n\n    struct Affine\
    \ {\n        long long a = 1;\n        long long b = 0;\n    };\n\n    // first\u3092\
    \u9069\u7528\u3057\u305F\u5F8C\u306Bsecond\u3092\u9069\u7528\u3059\u308B\u3002\
    \n    Affine compose(const Affine& first, const Affine& second) {\n        return\
    \ {second.a * first.a % MOD,\n                (second.a * first.b + second.b)\
    \ % MOD};\n    }\n\n    struct BidirectionalProduct {\n        Affine forward;\n\
    \        Affine backward;\n    };\n\n    BidirectionalProduct merge(const BidirectionalProduct&\
    \ left,\n                               const BidirectionalProduct& right) {\n\
    \        return {compose(left.forward, right.forward),\n                compose(right.backward,\
    \ left.backward)};\n    }\n\n    struct SegmentTree {\n        int size = 1;\n\
    \        std::vector<BidirectionalProduct> data;\n\n        explicit SegmentTree(int\
    \ n) {\n            while (size < n) size *= 2;\n            data.assign(2 * size,\
    \ {});\n        }\n\n        void set(int position, Affine value) {\n        \
    \    int index = position + size;\n            data[index] = {value, value};\n\
    \            while (index > 1) {\n                index /= 2;\n              \
    \  data[index] = merge(data[2 * index], data[2 * index + 1]);\n            }\n\
    \        }\n\n        BidirectionalProduct prod(int left, int right) const {\n\
    \            BidirectionalProduct left_product, right_product;\n            left\
    \ += size;\n            right += size;\n            while (left < right) {\n \
    \               if (left & 1) left_product = merge(left_product, data[left++]);\n\
    \                if (right & 1) right_product = merge(data[--right], right_product);\n\
    \                left /= 2;\n                right /= 2;\n            }\n    \
    \        return merge(left_product, right_product);\n        }\n    };\n}\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<Affine> function(n);\n\
    \    for (auto& [a, b] : function) std::cin >> a >> b;\n\n    std::vector<std::vector<int>>\
    \ graph(n);\n    for (int i = 0; i + 1 < n; ++i) {\n        int u, v;\n      \
    \  std::cin >> u >> v;\n        graph[u].push_back(v);\n        graph[v].push_back(u);\n\
    \    }\n\n    yesantikiss::HeavyLightDecomposition hld(graph);\n    SegmentTree\
    \ segment_tree(n);\n    for (int v = 0; v < n; ++v) {\n        segment_tree.set(hld.in[v],\
    \ function[v]);\n    }\n\n    while (q--) {\n        int type;\n        std::cin\
    \ >> type;\n        if (type == 0) {\n            int v;\n            Affine value;\n\
    \            std::cin >> v >> value.a >> value.b;\n            segment_tree.set(hld.in[v],\
    \ value);\n        } else {\n            int u, v;\n            long long x;\n\
    \            std::cin >> u >> v >> x;\n\n            Affine path_product;\n  \
    \          hld.path_query(u, v, false,\n                           [&](int left,\
    \ int right, bool reverse) {\n                               auto product = segment_tree.prod(left,\
    \ right);\n                               const Affine& part = reverse ? product.backward\n\
    \                                                            : product.forward;\n\
    \                               path_product = compose(path_product, part);\n\
    \                           });\n            std::cout << (path_product.a * x\
    \ + path_product.b) % MOD << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"tree/heavy_light_decomposition.hpp\"\
    \n\nnamespace {\n    constexpr long long MOD = 998244353;\n\n    struct Affine\
    \ {\n        long long a = 1;\n        long long b = 0;\n    };\n\n    // first\u3092\
    \u9069\u7528\u3057\u305F\u5F8C\u306Bsecond\u3092\u9069\u7528\u3059\u308B\u3002\
    \n    Affine compose(const Affine& first, const Affine& second) {\n        return\
    \ {second.a * first.a % MOD,\n                (second.a * first.b + second.b)\
    \ % MOD};\n    }\n\n    struct BidirectionalProduct {\n        Affine forward;\n\
    \        Affine backward;\n    };\n\n    BidirectionalProduct merge(const BidirectionalProduct&\
    \ left,\n                               const BidirectionalProduct& right) {\n\
    \        return {compose(left.forward, right.forward),\n                compose(right.backward,\
    \ left.backward)};\n    }\n\n    struct SegmentTree {\n        int size = 1;\n\
    \        std::vector<BidirectionalProduct> data;\n\n        explicit SegmentTree(int\
    \ n) {\n            while (size < n) size *= 2;\n            data.assign(2 * size,\
    \ {});\n        }\n\n        void set(int position, Affine value) {\n        \
    \    int index = position + size;\n            data[index] = {value, value};\n\
    \            while (index > 1) {\n                index /= 2;\n              \
    \  data[index] = merge(data[2 * index], data[2 * index + 1]);\n            }\n\
    \        }\n\n        BidirectionalProduct prod(int left, int right) const {\n\
    \            BidirectionalProduct left_product, right_product;\n            left\
    \ += size;\n            right += size;\n            while (left < right) {\n \
    \               if (left & 1) left_product = merge(left_product, data[left++]);\n\
    \                if (right & 1) right_product = merge(data[--right], right_product);\n\
    \                left /= 2;\n                right /= 2;\n            }\n    \
    \        return merge(left_product, right_product);\n        }\n    };\n}\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<Affine> function(n);\n\
    \    for (auto& [a, b] : function) std::cin >> a >> b;\n\n    std::vector<std::vector<int>>\
    \ graph(n);\n    for (int i = 0; i + 1 < n; ++i) {\n        int u, v;\n      \
    \  std::cin >> u >> v;\n        graph[u].push_back(v);\n        graph[v].push_back(u);\n\
    \    }\n\n    yesantikiss::HeavyLightDecomposition hld(graph);\n    SegmentTree\
    \ segment_tree(n);\n    for (int v = 0; v < n; ++v) {\n        segment_tree.set(hld.in[v],\
    \ function[v]);\n    }\n\n    while (q--) {\n        int type;\n        std::cin\
    \ >> type;\n        if (type == 0) {\n            int v;\n            Affine value;\n\
    \            std::cin >> v >> value.a >> value.b;\n            segment_tree.set(hld.in[v],\
    \ value);\n        } else {\n            int u, v;\n            long long x;\n\
    \            std::cin >> u >> v >> x;\n\n            Affine path_product;\n  \
    \          hld.path_query(u, v, false,\n                           [&](int left,\
    \ int right, bool reverse) {\n                               auto product = segment_tree.prod(left,\
    \ right);\n                               const Affine& part = reverse ? product.backward\n\
    \                                                            : product.forward;\n\
    \                               path_product = compose(path_product, part);\n\
    \                           });\n            std::cout << (path_product.a * x\
    \ + path_product.b) % MOD << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - tree/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: verify/vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/verify/vertex_set_path_composite.test.cpp
- /verify/verify/vertex_set_path_composite.test.cpp.html
title: verify/vertex_set_path_composite.test.cpp
---
