extern int Main(int /* argc */, char const*const /* argv */[]);

#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <bitset>
#include <functional>
#include <utility>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <tuple>
#if __cplusplus >= 201703L && __has_include(<any>)
#include <any>
#endif
#if __cplusplus >= 201703L && __has_include(<optional>)
#include <optional>
#endif
#if __cplusplus >= 201703L && __has_include(<variant>)
#include <variant>
#endif

#include <new>
#include <memory>
#include <scoped_allocator>
#if __has_include(<memory_resource>)
# include <memory_resource>
#endif

#include <climits>
#include <cfloat>
#include <cstdint>
#include <cinttypes>
#include <limits>

#include <exception>
#include <stdexcept>
#include <cassert>
#include <system_error>
#include <cerrno>

#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#if __has_include(<cuchar>)
#include <cuchar>
#endif
#include <string>
#if __cplusplus >= 201703L
#include <string_view>
#endif

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

#include <algorithm>
#if __has_include(<execution>)
#include <execution>
#endif

#include <iterator>

#include <cmath>
#include <complex>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <cfenv>

#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
// #include <strstream>    // deprecated
#include <iomanip>
#include <streambuf>
#include <cstdio>

#include <locale>
#include <clocale>
#include <codecvt>      // deprecated C++17

#include <regex>

#include <atomic>

#include <thread>
#include <mutex>
#if __cplusplus >= 201402L
#include <shared_mutex>
#endif
#include <future>
#include <condition_variable>

#if __has_include(<filesystem>)
#include <filesystem>
#endif

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

struct Claim
{
    Claim(size_t c, size_t l, size_t t, size_t w, size_t h)
    : claimId(c), left(l), top(t), width(w), height(h) {}

    size_t claimId;
    size_t left;
    size_t top;
    size_t width;
    size_t height;
};

struct Claims : std::vector<Claim> {};

struct Square : boost::numeric::ublas::matrix<size_t>
{
    using matrix = boost::numeric::ublas::matrix<size_t>;

    friend std::ostream& operator<<(std::ostream& os, Square const& that)
    { return os << static_cast<matrix const&>(that); }
};

inline int NoMatterHowYouSliceIt(Claims const& claims)
{
    Square square;

    for (Claim const& claim : claims)
    {
        square.resize(std::max(square.size1(), claim.top + claim.height),
                      std::max(square.size2(), claim.left + claim.width));

        for (size_t r = claim.top; r != claim.top + claim.height; ++r)
            for (size_t c = claim.left; c != claim.left + claim.width; ++c)
                ++square(r, c);
    }

    std::cout << square << '\n';
    
    return 0;
}

int Main(int /* argc */, char const*const /* argv */[])
{
    Claims claims;

    //claims.emplace_back(123, 3, 2, 5, 4);
    claims.emplace_back(1, 1, 3, 4, 4);
    claims.emplace_back(2, 3, 1, 4, 4);
    claims.emplace_back(3, 5, 5, 2, 2);

    NoMatterHowYouSliceIt(claims);
    return 0;
}

