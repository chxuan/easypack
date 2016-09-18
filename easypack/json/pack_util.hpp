#ifndef _PACK_UTIL_H
#define _PACK_UTIL_H

#include <vector>
#include <tuple>
#include <boost/any.hpp>

namespace easypack
{

template<typename Tuple, std::size_t N>
struct foreach_tuple
{
    static void foreach(std::vector<boost::any>& vec, const Tuple& t)
    {
        foreach_tuple<Tuple, N - 1>::foreach(vec, t);
        vec.emplace_back(std::get<N - 1>(t));
    }
};

template<typename Tuple>
struct foreach_tuple<Tuple, 1>
{
    static void foreach(std::vector<boost::any>& vec, const Tuple& t)
    {
        vec.emplace_back(std::get<0>(t));
    }
};

template<typename... Args>
void tuple2vector(std::vector<boost::any>& vec, const std::tuple<Args...>& t)
{
    foreach_tuple<decltype(t), sizeof...(Args)>::foreach(vec, t);
}

void unpack_args_impl(std::vector<boost::any>&, std::size_t) {}

template<typename T, typename... Args>
void unpack_args_impl(std::vector<boost::any>& vec, std::size_t offset, T&& t, Args&&... args)
{
    t = boost::any_cast<T>(vec[offset]);
    unpack_args_impl(vec, offset + 1, std::forward<Args>(args)...);
}

}

#endif
