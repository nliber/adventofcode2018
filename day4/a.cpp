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

#include <boost/operators.hpp>

#include <cool/pretty_name.h>
#include <cool/iomanip.h>

struct Timestamp : private boost::totally_ordered<Timestamp>
{
    static constexpr const char* reTimestamp = "(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d) (\\d\\d):(\\d\\d)";
    explicit Timestamp(std::string_view sv)
    {
        std::regex regexTimestamp(reTimestamp);
        std::match_results<std::string_view::const_iterator> match;
        if (!std::regex_search(sv.begin(), sv.end(), match, regexTimestamp))
            throw std::runtime_error(std::string(sv) + ": not a " + std::string(cool::pretty_name(*this)));

        year   = static_cast<uint16_t>(stoul(match[1]));
        month  = static_cast< uint8_t>(stoul(match[2]));
        day    = static_cast< uint8_t>(stoul(match[3]));
        hour   = static_cast< uint8_t>(stoul(match[4]));
        minute = static_cast< uint8_t>(stoul(match[5]));
    }

    auto my_tie() const noexcept
    { return std::tie(year, month, day, hour, minute); }

    friend bool operator==(Timestamp const& l, Timestamp const& r) noexcept
    { return l.my_tie() == r.my_tie(); }

    friend bool operator<(Timestamp const& l, Timestamp const& r) noexcept
    { return l.my_tie() < r.my_tie(); }

    friend std::ostream& operator<<(std::ostream& os, Timestamp const& that)
    {
        return os << cool::setiomanip(true) << std::setfill('0')
            << std::setw(4) << +that.year
            << '-'
            << std::setw(2) << +that.month
            << '-'
            << std::setw(2) << +that.day
            << ' '
            << std::setw(2) << +that.hour
            << ':'
            << std::setw(2) << +that.minute
            ;
    }

    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
};

struct Guard
{
    explicit Guard(std::string_view sv)
        : timestamp(sv)
    {
        std::regex guardBeginsShift("Guard #(\\d+) begins shift");
        std::regex fallsAsleep("falls asleep");
        std::regex wakesUp("wakes up");
        std::match_results<std::string_view::const_iterator> match;

        if (std::regex_search(sv.begin(), sv.end(), match, guardBeginsShift))
            id = static_cast<uint16_t>(stoul(match[1]));
        else if (std::regex_search(sv.begin(), sv.end(), fallsAsleep))
            asleep = true;
        else if (!std::regex_search(sv.begin(), sv.end(), wakesUp))
            throw std::runtime_error(std::string(sv) + ": not a valid entry");
    }

    friend std::ostream& operator<<(std::ostream& os, Guard const& that)
    {
        return os
            << '['
            << that.timestamp
            << "] Guard #"
            << that.id
            << ' '
            << (that.asleep ? "sleep" : "awake")
            ;
    }

    Timestamp timestamp;
    uint16_t  id = 0;
    bool      asleep = false;
};

int Main(int /* argc */, char const*const /* argv */[])
{
    Timestamp t("0123-04-05 06:07");
    std::cout << t << '\n';

    Guard g("[1518-11-01 00:00] Guard #10 begins shift");
    std::cout << g << '\n';

    return 0;
}

