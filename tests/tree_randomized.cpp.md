---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: Heavy-Light Decomposition
  - icon: ':heavy_check_mark:'
    path: tree/lca_binary_lifting.hpp
    title: LCA (Binary Lifting)
  - icon: ':heavy_check_mark:'
    path: tree/lca_euler_tour.hpp
    title: LCA (Euler Tour + Sparse Table)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tests/tree_randomized.cpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <random>\n#include <vector>\n\n#line 2 \"tree/heavy_light_decomposition.hpp\"\
    \n\n#line 4 \"tree/heavy_light_decomposition.hpp\"\n#include <tuple>\n#include\
    \ <utility>\n#line 7 \"tree/heavy_light_decomposition.hpp\"\n\nnamespace yesantikiss\
    \ {\n    struct HeavyLightDecomposition {\n        int n = 0;\n        int root\
    \ = -1;\n        std::vector<int> parent;\n        std::vector<int> depth;\n \
    \       std::vector<int> size;\n        std::vector<int> in;\n        std::vector<int>\
    \ out;\n        std::vector<int> head;\n        std::vector<int> heavy;\n    \
    \    std::vector<int> vertex;\n\n        HeavyLightDecomposition() = default;\n\
    \n        explicit HeavyLightDecomposition(\n            const std::vector<std::vector<int>>&\
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
    \ -1);\n            vertex.assign(n, -1);\n        }\n    };\n}\n#line 2 \"tree/lca_binary_lifting.hpp\"\
    \n\n#line 5 \"tree/lca_binary_lifting.hpp\"\n\nnamespace yesantikiss {\n    struct\
    \ BinaryLiftingLCA {\n        int n = 0;\n        int log = 1;\n        std::vector<int>\
    \ depth;\n        std::vector<int> parent;\n        std::vector<int> component;\n\
    \n        BinaryLiftingLCA() = default;\n\n        explicit BinaryLiftingLCA(\n\
    \            const std::vector<std::vector<int>>& graph, int root = 0) {\n   \
    \         build(graph, root);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph, int root = 0) {\n            init(static_cast<int>(graph.size()));\n\
    \            if (n == 0) return;\n\n            build_component(graph, root, 0);\n\
    \            build_table();\n        }\n\n        void build_forest(const std::vector<std::vector<int>>&\
    \ graph) {\n            init(static_cast<int>(graph.size()));\n\n            int\
    \ component_id = 0;\n            for (int root = 0; root < n; ++root) {\n    \
    \            if (parent[root] == -1) {\n                    build_component(graph,\
    \ root, component_id++);\n                }\n            }\n            build_table();\n\
    \        }\n\n        int kth_ancestor(int v, int k) const {\n            if (!contains(v)\
    \ || k < 0 || parent[v] == -1) return -1;\n            k = std::min(k, depth[v]);\n\
    \            for (int bit = 0; bit < log; ++bit) {\n                if ((k >>\
    \ bit) & 1) v = up_at(bit, v);\n            }\n            return v;\n       \
    \ }\n\n        int lca(int a, int b) const {\n            if (!same_component(a,\
    \ b)) return -1;\n            if (depth[a] < depth[b]) std::swap(a, b);\n\n  \
    \          a = kth_ancestor(a, depth[a] - depth[b]);\n            if (a == b)\
    \ return a;\n\n            for (int bit = log - 1; bit >= 0; --bit) {\n      \
    \          if (up_at(bit, a) != up_at(bit, b)) {\n                    a = up_at(bit,\
    \ a);\n                    b = up_at(bit, b);\n                }\n           \
    \ }\n            return parent[a];\n        }\n\n        int dist(int a, int b)\
    \ const {\n            int ancestor = lca(a, b);\n            if (ancestor ==\
    \ -1) return -1;\n            return depth[a] + depth[b] - 2 * depth[ancestor];\n\
    \        }\n\n        bool is_ancestor(int ancestor, int v) const {\n        \
    \    return same_component(ancestor, v) && lca(ancestor, v) == ancestor;\n   \
    \     }\n\n        // a -> b \u30D1\u30B9\u4E0A\u3067 a \u3092 0 \u756A\u76EE\u3068\
    \u3059\u308B k \u756A\u76EE\u306E\u9802\u70B9\u3092\u8FD4\u3059\u3002\n      \
    \  int jump(int a, int b, int k) const {\n            int ancestor = lca(a, b);\n\
    \            if (ancestor == -1 || k < 0) return -1;\n\n            int up_length\
    \ = depth[a] - depth[ancestor];\n            int down_length = depth[b] - depth[ancestor];\n\
    \            if (k > up_length + down_length) return -1;\n            if (k <=\
    \ up_length) return kth_ancestor(a, k);\n            return kth_ancestor(b, up_length\
    \ + down_length - k);\n        }\n\n    private:\n        std::vector<int> up;\n\
    \n        void init(int size) {\n            n = size;\n            log = 1;\n\
    \            while ((1LL << log) <= std::max(1, n)) ++log;\n            depth.assign(n,\
    \ 0);\n            parent.assign(n, -1);\n            component.assign(n, -1);\n\
    \            up.assign(log * n, 0);\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& up_at(int bit, int v) { return up[bit * n + v]; }\n        int up_at(int\
    \ bit, int v) const { return up[bit * n + v]; }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            parent[root] = root;\n            depth[root]\
    \ = 0;\n            component[root] = component_id;\n\n            std::vector<int>\
    \ order{root};\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         component[to] = component_id;\n                    order.push_back(to);\n\
    \                }\n            }\n        }\n\n        void build_table() {\n\
    \            for (int v = 0; v < n; ++v) {\n                if (parent[v] != -1)\
    \ up_at(0, v) = parent[v];\n            }\n            for (int bit = 1; bit <\
    \ log; ++bit) {\n                for (int v = 0; v < n; ++v) {\n             \
    \       if (parent[v] != -1) {\n                        up_at(bit, v) = up_at(bit\
    \ - 1, up_at(bit - 1, v));\n                    }\n                }\n       \
    \     }\n        }\n    };\n}\n#line 2 \"tree/lca_euler_tour.hpp\"\n\n#line 5\
    \ \"tree/lca_euler_tour.hpp\"\n\nnamespace yesantikiss {\n    struct EulerTourLCA\
    \ {\n        int n = 0;\n        std::vector<int> depth;\n        std::vector<int>\
    \ parent;\n        std::vector<int> component;\n        std::vector<int> tin;\n\
    \        std::vector<int> tout;\n\n        EulerTourLCA() = default;\n\n     \
    \   explicit EulerTourLCA(const std::vector<std::vector<int>>& graph,\n      \
    \                        int root = 0) {\n            build(graph, root);\n  \
    \      }\n\n        void build(const std::vector<std::vector<int>>& graph, int\
    \ root = 0) {\n            init(static_cast<int>(graph.size()));\n           \
    \ if (n == 0) return;\n\n            euler.reserve(2 * n - 1);\n            build_component(graph,\
    \ root, 0);\n            build_sparse_table();\n        }\n\n        void build_forest(const\
    \ std::vector<std::vector<int>>& graph) {\n            init(static_cast<int>(graph.size()));\n\
    \            euler.reserve(n == 0 ? 0 : 2 * n - 1);\n\n            int component_id\
    \ = 0;\n            for (int root = 0; root < n; ++root) {\n                if\
    \ (parent[root] == -1) {\n                    build_component(graph, root, component_id++);\n\
    \                }\n            }\n            build_sparse_table();\n       \
    \ }\n\n        int lca(int a, int b) const {\n            if (!same_component(a,\
    \ b)) return -1;\n            int left = first[a];\n            int right = first[b];\n\
    \            if (left > right) std::swap(left, right);\n\n            int length\
    \ = right - left + 1;\n            int level = lg[length];\n            return\
    \ better(st_at(level, left),\n                          st_at(level, right - (1\
    \ << level) + 1));\n        }\n\n        int dist(int a, int b) const {\n    \
    \        int ancestor = lca(a, b);\n            if (ancestor == -1) return -1;\n\
    \            return depth[a] + depth[b] - 2 * depth[ancestor];\n        }\n\n\
    \        bool is_ancestor(int ancestor, int v) const {\n            return same_component(ancestor,\
    \ v) && tin[ancestor] <= tin[v] &&\n                   tout[v] <= tout[ancestor];\n\
    \        }\n\n    private:\n        int timer = 0;\n        int euler_size = 0;\n\
    \        int levels = 0;\n        std::vector<int> first;\n        std::vector<int>\
    \ euler;\n        std::vector<int> lg;\n        std::vector<int> sparse_table;\n\
    \n        struct Frame {\n            int v;\n            int next_edge;\n   \
    \     };\n\n        void init(int size) {\n            n = size;\n           \
    \ timer = 0;\n            euler_size = 0;\n            levels = 0;\n         \
    \   depth.assign(n, 0);\n            parent.assign(n, -1);\n            component.assign(n,\
    \ -1);\n            tin.assign(n, -1);\n            tout.assign(n, -1);\n    \
    \        first.assign(n, -1);\n            euler.clear();\n            lg.clear();\n\
    \            sparse_table.clear();\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& st_at(int level, int index) {\n            return sparse_table[level\
    \ * euler_size + index];\n        }\n\n        int st_at(int level, int index)\
    \ const {\n            return sparse_table[level * euler_size + index];\n    \
    \    }\n\n        int better(int a, int b) const {\n            return depth[a]\
    \ <= depth[b] ? a : b;\n        }\n\n        void enter(int v, int p, int component_id)\
    \ {\n            parent[v] = p;\n            component[v] = component_id;\n  \
    \          tin[v] = timer++;\n            first[v] = static_cast<int>(euler.size());\n\
    \            euler.push_back(v);\n        }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            depth[root] = 0;\n            enter(root, root,\
    \ component_id);\n            std::vector<Frame> stack{{root, 0}};\n\n       \
    \     while (!stack.empty()) {\n                Frame& frame = stack.back();\n\
    \                int v = frame.v;\n                if (frame.next_edge == static_cast<int>(graph[v].size()))\
    \ {\n                    tout[v] = timer;\n                    stack.pop_back();\n\
    \                    if (!stack.empty()) euler.push_back(stack.back().v);\n  \
    \                  continue;\n                }\n\n                int to = graph[v][frame.next_edge++];\n\
    \                if (parent[to] != -1) continue;\n                depth[to] =\
    \ depth[v] + 1;\n                enter(to, v, component_id);\n               \
    \ stack.push_back({to, 0});\n            }\n        }\n\n        void build_sparse_table()\
    \ {\n            euler_size = static_cast<int>(euler.size());\n            if\
    \ (euler_size == 0) return;\n\n            lg.assign(euler_size + 1, 0);\n   \
    \         for (int i = 2; i <= euler_size; ++i) lg[i] = lg[i / 2] + 1;\n\n   \
    \         levels = lg[euler_size] + 1;\n            sparse_table.assign(levels\
    \ * euler_size, 0);\n            for (int i = 0; i < euler_size; ++i) st_at(0,\
    \ i) = euler[i];\n\n            for (int level = 1; level < levels; ++level) {\n\
    \                int length = 1 << level;\n                int half = length /\
    \ 2;\n                for (int i = 0; i + length <= euler_size; ++i) {\n     \
    \               st_at(level, i) =\n                        better(st_at(level\
    \ - 1, i),\n                               st_at(level - 1, i + half));\n    \
    \            }\n            }\n        }\n    };\n}\n#line 9 \"tests/tree_randomized.cpp\"\
    \n\nint main() {\n    std::mt19937 random(123456789);\n\n    for (int trial =\
    \ 0; trial < 100; ++trial) {\n        int n = 1 + static_cast<int>(random() %\
    \ 100);\n        std::vector<std::vector<int>> graph(n);\n        std::vector<int>\
    \ parent(n), depth(n);\n        for (int v = 1; v < n; ++v) {\n            parent[v]\
    \ = static_cast<int>(random() % v);\n            depth[v] = depth[parent[v]] +\
    \ 1;\n            graph[parent[v]].push_back(v);\n            graph[v].push_back(parent[v]);\n\
    \        }\n\n        yesantikiss::BinaryLiftingLCA doubling(graph);\n       \
    \ yesantikiss::EulerTourLCA sparse(graph);\n        yesantikiss::HeavyLightDecomposition\
    \ hld(graph);\n\n        auto naive_lca = [&](int u, int v) {\n            while\
    \ (depth[u] > depth[v]) u = parent[u];\n            while (depth[v] > depth[u])\
    \ v = parent[v];\n            while (u != v) {\n                u = parent[u];\n\
    \                v = parent[v];\n            }\n            return u;\n      \
    \  };\n\n        for (int query = 0; query < 200; ++query) {\n            int\
    \ u = static_cast<int>(random() % n);\n            int v = static_cast<int>(random()\
    \ % n);\n            int ancestor = naive_lca(u, v);\n\n            assert(doubling.lca(u,\
    \ v) == ancestor);\n            assert(sparse.lca(u, v) == ancestor);\n      \
    \      assert(hld.lca(u, v) == ancestor);\n\n            std::vector<int> expected;\n\
    \            for (int x = u; x != ancestor; x = parent[x]) expected.push_back(x);\n\
    \            expected.push_back(ancestor);\n            std::vector<int> suffix;\n\
    \            for (int x = v; x != ancestor; x = parent[x]) suffix.push_back(x);\n\
    \            std::reverse(suffix.begin(), suffix.end());\n            expected.insert(expected.end(),\
    \ suffix.begin(), suffix.end());\n\n            assert(doubling.dist(u, v) ==\
    \ static_cast<int>(expected.size()) - 1);\n            assert(sparse.dist(u, v)\
    \ == static_cast<int>(expected.size()) - 1);\n            assert(hld.dist(u, v)\
    \ == static_cast<int>(expected.size()) - 1);\n            for (int k = 0; k <\
    \ static_cast<int>(expected.size()); ++k) {\n                assert(doubling.jump(u,\
    \ v, k) == expected[k]);\n            }\n            assert(doubling.jump(u, v,\
    \ static_cast<int>(expected.size())) == -1);\n\n            std::vector<int> actual;\n\
    \            hld.path_query(u, v, false,\n                           [&](int left,\
    \ int right, bool reverse) {\n                               if (reverse) {\n\
    \                                   for (int i = right - 1; i >= left; --i) {\n\
    \                                       actual.push_back(hld.vertex[i]);\n   \
    \                                }\n                               } else {\n\
    \                                   for (int i = left; i < right; ++i) {\n   \
    \                                    actual.push_back(hld.vertex[i]);\n      \
    \                             }\n                               }\n          \
    \                 });\n            assert(actual == expected);\n\n           \
    \ actual.clear();\n            hld.path_query(u, v, true,\n                  \
    \         [&](int left, int right, bool reverse) {\n                         \
    \      if (reverse) {\n                                   for (int i = right -\
    \ 1; i >= left; --i) {\n                                       actual.push_back(hld.vertex[i]);\n\
    \                                   }\n                               } else {\n\
    \                                   for (int i = left; i < right; ++i) {\n   \
    \                                    actual.push_back(hld.vertex[i]);\n      \
    \                             }\n                               }\n          \
    \                 });\n            expected.erase(std::find(expected.begin(),\
    \ expected.end(), ancestor));\n            assert(actual == expected);\n     \
    \   }\n\n        for (int ancestor = 0; ancestor < n; ++ancestor) {\n        \
    \    for (int v = 0; v < n; ++v) {\n                bool expected = naive_lca(ancestor,\
    \ v) == ancestor;\n                assert(doubling.is_ancestor(ancestor, v) ==\
    \ expected);\n                assert(sparse.is_ancestor(ancestor, v) == expected);\n\
    \                assert(hld.is_ancestor(ancestor, v) == expected);\n         \
    \   }\n        }\n    }\n}\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <random>\n#include <vector>\n\
    \n#include \"tree/heavy_light_decomposition.hpp\"\n#include \"tree/lca_binary_lifting.hpp\"\
    \n#include \"tree/lca_euler_tour.hpp\"\n\nint main() {\n    std::mt19937 random(123456789);\n\
    \n    for (int trial = 0; trial < 100; ++trial) {\n        int n = 1 + static_cast<int>(random()\
    \ % 100);\n        std::vector<std::vector<int>> graph(n);\n        std::vector<int>\
    \ parent(n), depth(n);\n        for (int v = 1; v < n; ++v) {\n            parent[v]\
    \ = static_cast<int>(random() % v);\n            depth[v] = depth[parent[v]] +\
    \ 1;\n            graph[parent[v]].push_back(v);\n            graph[v].push_back(parent[v]);\n\
    \        }\n\n        yesantikiss::BinaryLiftingLCA doubling(graph);\n       \
    \ yesantikiss::EulerTourLCA sparse(graph);\n        yesantikiss::HeavyLightDecomposition\
    \ hld(graph);\n\n        auto naive_lca = [&](int u, int v) {\n            while\
    \ (depth[u] > depth[v]) u = parent[u];\n            while (depth[v] > depth[u])\
    \ v = parent[v];\n            while (u != v) {\n                u = parent[u];\n\
    \                v = parent[v];\n            }\n            return u;\n      \
    \  };\n\n        for (int query = 0; query < 200; ++query) {\n            int\
    \ u = static_cast<int>(random() % n);\n            int v = static_cast<int>(random()\
    \ % n);\n            int ancestor = naive_lca(u, v);\n\n            assert(doubling.lca(u,\
    \ v) == ancestor);\n            assert(sparse.lca(u, v) == ancestor);\n      \
    \      assert(hld.lca(u, v) == ancestor);\n\n            std::vector<int> expected;\n\
    \            for (int x = u; x != ancestor; x = parent[x]) expected.push_back(x);\n\
    \            expected.push_back(ancestor);\n            std::vector<int> suffix;\n\
    \            for (int x = v; x != ancestor; x = parent[x]) suffix.push_back(x);\n\
    \            std::reverse(suffix.begin(), suffix.end());\n            expected.insert(expected.end(),\
    \ suffix.begin(), suffix.end());\n\n            assert(doubling.dist(u, v) ==\
    \ static_cast<int>(expected.size()) - 1);\n            assert(sparse.dist(u, v)\
    \ == static_cast<int>(expected.size()) - 1);\n            assert(hld.dist(u, v)\
    \ == static_cast<int>(expected.size()) - 1);\n            for (int k = 0; k <\
    \ static_cast<int>(expected.size()); ++k) {\n                assert(doubling.jump(u,\
    \ v, k) == expected[k]);\n            }\n            assert(doubling.jump(u, v,\
    \ static_cast<int>(expected.size())) == -1);\n\n            std::vector<int> actual;\n\
    \            hld.path_query(u, v, false,\n                           [&](int left,\
    \ int right, bool reverse) {\n                               if (reverse) {\n\
    \                                   for (int i = right - 1; i >= left; --i) {\n\
    \                                       actual.push_back(hld.vertex[i]);\n   \
    \                                }\n                               } else {\n\
    \                                   for (int i = left; i < right; ++i) {\n   \
    \                                    actual.push_back(hld.vertex[i]);\n      \
    \                             }\n                               }\n          \
    \                 });\n            assert(actual == expected);\n\n           \
    \ actual.clear();\n            hld.path_query(u, v, true,\n                  \
    \         [&](int left, int right, bool reverse) {\n                         \
    \      if (reverse) {\n                                   for (int i = right -\
    \ 1; i >= left; --i) {\n                                       actual.push_back(hld.vertex[i]);\n\
    \                                   }\n                               } else {\n\
    \                                   for (int i = left; i < right; ++i) {\n   \
    \                                    actual.push_back(hld.vertex[i]);\n      \
    \                             }\n                               }\n          \
    \                 });\n            expected.erase(std::find(expected.begin(),\
    \ expected.end(), ancestor));\n            assert(actual == expected);\n     \
    \   }\n\n        for (int ancestor = 0; ancestor < n; ++ancestor) {\n        \
    \    for (int v = 0; v < n; ++v) {\n                bool expected = naive_lca(ancestor,\
    \ v) == ancestor;\n                assert(doubling.is_ancestor(ancestor, v) ==\
    \ expected);\n                assert(sparse.is_ancestor(ancestor, v) == expected);\n\
    \                assert(hld.is_ancestor(ancestor, v) == expected);\n         \
    \   }\n        }\n    }\n}\n"
  dependsOn:
  - tree/heavy_light_decomposition.hpp
  - tree/lca_binary_lifting.hpp
  - tree/lca_euler_tour.hpp
  isVerificationFile: false
  path: tests/tree_randomized.cpp
  requiredBy: []
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tests/tree_randomized.cpp
layout: document
redirect_from:
- /library/tests/tree_randomized.cpp
- /library/tests/tree_randomized.cpp.html
title: tests/tree_randomized.cpp
---
