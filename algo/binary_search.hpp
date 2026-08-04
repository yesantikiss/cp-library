#pragma once

namespace yesantikiss {
    // [left, right) の範囲で f(mid) が true になる最小の left を返す
    // 単調性: false...false,true...true
    template<class F, class T>
    T binary_search_min_left(T left, T right, F f){
        while (right - left > 1){
            T mid = left + (right - left) / 2;
            if(f(mid)) right = mid;
            else left = mid;
        }
        return right;
    }

    // [left, right) の範囲で f(mid) が true になる最大の right-1 を返す
    // 単調性: true...true,false...false
    template<class F, class T>
    T binary_search_max_right(T left, T right, F f){
        while (right - left > 1){
            T mid = left + (right - left) / 2;
            if(f(mid)) left = mid;
            else right = mid;
        }
        return left;
    }
}
