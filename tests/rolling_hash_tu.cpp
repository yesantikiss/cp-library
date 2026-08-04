#include <string>

#include "string/rolling_hash.hpp"

yesantikiss::RollingHash::ull rolling_hash_from_other_tu(const std::string& s) {
    return yesantikiss::RollingHash(s).get(0, (int)s.size());
}
