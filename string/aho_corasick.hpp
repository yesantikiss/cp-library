#pragma once

#include <array>
#include <cassert>
#include <queue>
#include <string>
#include <vector>

namespace yesantikiss {
    template<int SIGMA = 26, char BASE = 'a'>
    struct AhoCorasick {
        struct Node {
            std::array<int, SIGMA> nxt;
            int link = 0;
            int parent = -1;
            int pch = -1;
    
            Node(int parent = -1, int pch = -1)
                : parent(parent), pch(pch) {
                nxt.fill(-1);
            }
        };
    
        std::vector<Node> nodes;
        std::vector<int> order;
    
        AhoCorasick() {
            nodes.emplace_back();
        }
    
        int enc(char ch) const {
            return ch - BASE;
        }
    
        int add(const std::string& s) {
            int v = 0;
            for (char ch : s) {
                int c = enc(ch);
                assert(0 <= c && c < SIGMA);
    
                if (nodes[v].nxt[c] == -1) {
                    nodes[v].nxt[c] = (int)nodes.size();
                    nodes.emplace_back(v, c);
                }
                v = nodes[v].nxt[c];
            }
            return v;
        }
    
        void build() {
            std::queue<int> q;
            order.clear();
            order.push_back(0);
    
            for (int c = 0; c < SIGMA; c++) {
                int u = nodes[0].nxt[c];
                if (u == -1) {
                    nodes[0].nxt[c] = 0;
                } else {
                    nodes[u].link = 0;
                    q.push(u);
                }
            }
    
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                order.push_back(v);
    
                for (int c = 0; c < SIGMA; c++) {
                    int u = nodes[v].nxt[c];
    
                    if (u == -1) {
                        nodes[v].nxt[c] = nodes[nodes[v].link].nxt[c];
                    } else {
                        nodes[u].link = nodes[nodes[v].link].nxt[c];
                        q.push(u);
                    }
                }
            }
        }
    
        int move(int v, int c) const {
            return nodes[v].nxt[c];
        }
    
        int move(int v, char ch) const {
            return move(v, enc(ch));
        }
    
        int link(int v) const {
            return nodes[v].link;
        }
    
        int parent(int v) const {
            return nodes[v].parent;
        }
    
        int size() const {
            return (int)nodes.size();
        }
    };
}
