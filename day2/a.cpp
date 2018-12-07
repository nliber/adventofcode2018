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

struct BoxIds : std::vector<std::string> {};
struct Counts : std::map<char, int> {};

inline int Checksum(BoxIds const& boxIds)
{
    int twos = 0;
    int threes = 0;
    for (std::string const& boxId : boxIds)
    {
        Counts counts;
        for (char letter : boxId)
            ++counts[letter];

        bool containsTwo = false;
        bool containsThree = false;
        for (auto& count : counts)
        {
            if (2 == count.second)
                containsTwo = true;
            if (3 == count.second)
                containsThree = true;
        }
        twos += containsTwo;
        threes += containsThree;
    }

    return twos * threes;
}

inline int NumberDifferences(std::string const& a, std::string const& b)
{
    assert(a.size() == b.size());

    int numberDifferences = 0;
    for (std::string::size_type s = 0; s != a.size(); ++s)
        numberDifferences += a[s] != b[s];

    // std::cout << numberDifferences << ' ' << a << ' ' << b << '\n';

    return numberDifferences;
}

inline std::string CorrectBoxIds(BoxIds const& boxIds)
{
    std::string lettersInCommon;

    for (auto i = boxIds.begin(); i != boxIds.end(); ++i)
    {
        auto found = std::find_if(i + 1, boxIds.end(), [=](std::string const& boxId){ return 1 == NumberDifferences(*i, boxId); });
        if (boxIds.end() != found)
        {
            for (std::string::size_type s = 0; s != i->size(); ++s)
                if ((*i)[s] == (*found)[s])
                    lettersInCommon += (*i)[s];
            break;
        }
    }

    return lettersInCommon;
}

int Main(int /* argc */, char const*const /* argv */[])
{
    BoxIds boxIds;
    using istream_iterator = std::istream_iterator<BoxIds::value_type>;
    std::copy(istream_iterator(std::cin), istream_iterator(), std::back_inserter(boxIds));

    std::cout << Checksum(boxIds) << std::endl;
    std::cout << CorrectBoxIds(boxIds) << std::endl;
           

    return 0;
}

