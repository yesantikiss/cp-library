#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include <iostream>
#include <string>
#include <vector>

#include "string/aho_corasick.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    yesantikiss::AhoCorasick<> aho;
    std::vector<int> terminal(n);
    for (int& vertex : terminal) {
        std::string s;
        std::cin >> s;
        vertex = aho.add(s);
    }
    aho.build();

    std::cout << aho.size() << '\n';
    for (int vertex = 1; vertex < aho.size(); ++vertex) {
        std::cout << aho.parent(vertex) << ' ' << aho.link(vertex) << '\n';
    }
    for (int i = 0; i < n; ++i) {
        if (i != 0) std::cout << ' ';
        std::cout << terminal[i];
    }
    std::cout << '\n';
}
