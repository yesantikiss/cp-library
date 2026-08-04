#pragma once

#include <functional>
#include <vector>

namespace yesantikiss {
    template <class T, class Compare = std::less<T>>
    struct CartesianTree {
        int n = 0;
        std::vector<T> a;
        std::vector<int> par, left, right;
        int root = -1;
        Compare comp;
    
        CartesianTree() {}
    
        CartesianTree(const std::vector<T>& _a, Compare _comp = Compare())
            : n((int)_a.size()),
              a(_a),
              par(n, -1),
              left(n, -1),
              right(n, -1),
              root(-1),
              comp(_comp) {
            build();
        }
    
        // comp(a[i], a[j]) == true なら i の方が j より上に来る
        // less<T>    : min Cartesian Tree
        // greater<T> : max Cartesian Tree
        void build() {
            std::vector<int> st;
            st.reserve(n);
    
            for (int i = 0; i < n; i++) {
                int last = -1;
    
                while (!st.empty() && comp(a[i], a[st.back()])) {
                    last = st.back();
                    st.pop_back();
                }
    
                if (!st.empty()) {
                    par[i] = st.back();
                    right[st.back()] = i;
                }
    
                if (last != -1) {
                    par[last] = i;
                    left[i] = last;
                }
    
                st.push_back(i);
            }
    
            for (int i = 0; i < n; i++) {
                if (par[i] == -1) {
                    root = i;
                    break;
                }
            }
        }
    };
}
