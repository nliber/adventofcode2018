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
#if 0
#if __has_include(<execution>)
#include <execution>
#endif
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

#include <cool/Out.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

struct Claim
{
    Claim() = default;

    explicit Claim(size_t i, size_t l, size_t t, size_t w, size_t h)
        : id(i), left(l), top(t), width(w), height(h) {}

    friend std::ostream& operator<<(std::ostream& os, Claim const& that)
    { return os << '#' << that.id << " @ " << that.left << ',' << that.top << ": " << that.width << 'x' << that.height; }

    size_t id;
    size_t left;
    size_t top;
    size_t width;
    size_t height;
};

struct Claims : std::vector<Claim>
{
    friend std::ostream& operator<<(std::ostream& os, Claims const& that)
    { return os << cool::Out<Claims, true>(that); }
};

struct Square : boost::numeric::ublas::matrix<short, boost::numeric::ublas::row_major, std::vector<short>>
{
    using matrix = boost::numeric::ublas::matrix<short, boost::numeric::ublas::row_major, std::vector<short>>;

    Square() = default;

    explicit Square(Claims const& claims)
    {
        for (Claim const& claim : claims)
        {
            resize(std::max(size1(), claim.top + claim.height),
                   std::max(size2(), claim.left + claim.width));

            for (size_t r = claim.top; r != claim.top + claim.height; ++r)
                for (size_t c = claim.left; c != claim.left + claim.width; ++c)
                    ++(*this)(r, c);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Square const& that)
    { return os << static_cast<matrix const&>(that); }
};

inline
ptrdiff_t NoMatterHowYouSliceIt(Square const& square)
{
    ptrdiff_t count = 0;
    for (auto row = square.begin1(); row != square.end1(); ++row)
        count += std::count_if(row.begin(), row.end(), [](Square::value_type v){ return 1 < v; });

    return count;
}

inline
bool Overlaps(Claim const& claim, Square const& square)
{
    for (size_t r = claim.top; r != claim.top + claim.height; ++r)
        for (size_t c = claim.left; c != claim.left + claim.width; ++c)
            if (1 < square(r, c))
                return true;

    return false;
}

inline
size_t DoesNotOverlap(Claims const& claims, Square const& square)
{
    auto found = std::find_if(claims.begin(), claims.end(), [&](Claim const& claim){ return !Overlaps(claim, square); });
    return found != claims.end() ? found->id : 0;
}


int Main(int /* argc */, char const*const /* argv */[])
{
    Claims claims;

#if 0
    claims.emplace_back(1, 1, 3, 4, 4);
    claims.emplace_back(2, 3, 1, 4, 4);
    claims.emplace_back(3, 5, 5, 2, 2);
#else

    std::regex rClaim("#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)");
    std::smatch match;
    std::string line;
    while (std::getline(std::cin, line) && std::regex_match(line, match, rClaim))
    {
        claims.emplace_back(stoul(match[1]),
                            stoul(match[2]),
                            stoul(match[3]),
                            stoul(match[4]),
                            stoul(match[5]));
    }
#endif

    std::cout << claims << '\n';
    Square square(claims);
    std::cout << NoMatterHowYouSliceIt(square) << '\n';
    std::cout << DoesNotOverlap(claims, square) << '\n';

    return 0;
}

