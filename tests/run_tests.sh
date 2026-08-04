#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"
cxx="${CXX:-g++}"
flags=(-std=c++17 -Wall -Wextra -Werror -O2 -I"$root")
build_dir="${TMPDIR:-/tmp}/cp-library-tests"

mkdir -p "$build_dir"

for header in \
    "$root"/algo/*.hpp \
    "$root"/ds/*.hpp \
    "$root"/math/*.hpp \
    "$root"/string/*.hpp \
    "$root"/utils/*.hpp; do
    source="$build_dir/header-$(basename "${header%.hpp}").cpp"
    printf '#include "%s"\n#include "%s"\nint main() {}\n' "$header" "$header" > "$source"
    "$cxx" "${flags[@]}" -fsyntax-only "$source"
done

"$cxx" "${flags[@]}" \
    "$root/tests/test.cpp" "$root/tests/rolling_hash_tu.cpp" \
    -o "$build_dir/tests"
"$build_dir/tests"

echo "All tests passed with $cxx"
