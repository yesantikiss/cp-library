#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include <iostream>
#include <vector>

#include "ds/cartesian_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;

    yesantikiss::CartesianTree<int> tree(values);
    tree.par[tree.root] = tree.root;
    for (int i = 0; i < n; ++i) {
        if (i != 0) std::cout << ' ';
        std::cout << tree.par[i];
    }
    std::cout << '\n';
}
