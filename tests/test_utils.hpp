/* 
PrimesBench/test_utils.hpp by Chris 
23.01.2022 
*/

#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <algorithm>
#include <sstream>

template<class T>
static std::string get_diff(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    std::vector<T> result{};
    std::set_symmetric_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::back_inserter(result));
    std::stringstream stream{};
    stream << "[ ";
    for (auto elem : result)
    {
        stream << elem << ' ';
    }
    stream << ']';
    return stream.str();
}

#endif