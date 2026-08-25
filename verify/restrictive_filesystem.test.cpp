#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2152"

#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "ds/interval_map.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr long long LIMIT = 1000000001LL;

    int command_count;
    while (std::cin >> command_count && command_count != 0) {
        yesantikiss::IntervalMap<long long, int> filesystem(0, LIMIT, -1);
        std::unordered_set<int> active;

        while (command_count--) {
            char command;
            std::cin >> command;
            if (command == 'W') {
                int id;
                long long remaining;
                std::cin >> id >> remaining;
                active.insert(id);

                long long position = 0;
                while (remaining > 0 && position < LIMIT) {
                    auto segment = filesystem.locate(position);
                    long long right = segment->r;
                    if (segment->v == -1 || !active.count(segment->v)) {
                        long long length = std::min(remaining, right - position);
                        filesystem.assign(position, position + length, id);
                        position += length;
                        remaining -= length;
                    } else {
                        position = right;
                    }
                }
            } else if (command == 'D') {
                int id;
                std::cin >> id;
                active.erase(id);
            } else {
                long long position;
                std::cin >> position;
                int id = filesystem.get_val(position);
                std::cout << (active.count(id) ? id : -1) << '\n';
            }
        }
        std::cout << '\n';
    }
}
