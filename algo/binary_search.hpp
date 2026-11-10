#pragma once

namespace yesantikiss {
    // (left, right] の範囲で f(x) が true になる最小の x を返す
    // 単調性: false...false,true...true
    // left と right は番兵で、f(left) == false, f(right) == true とみなす
    // (f(left), f(right) は評価しない。true がなければ right を返す)
    template<class F, class T>
    T binary_search_min_left(T left, T right, F f){
        while (right - left > 1){
            T mid = left + (right - left) / 2;
            if(f(mid)) right = mid;
            else left = mid;
        }
        return right;
    }

    // [left, right) の範囲で f(x) が true になる最大の x を返す
    // 単調性: true...true,false...false
    // left と right は番兵で、f(left) == true, f(right) == false とみなす
    // (f(left), f(right) は評価しない。true がなければ left を返す)
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
