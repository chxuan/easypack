#ifndef _PACKUTIL_H
#define _PACKUTIL_H

#include <vector>
#include <tuple>
#include <boost/any.hpp>

namespace easypack
{

template<typename Tuple, std::size_t N>
struct Tuple2Vector
{
    static void foreach(std::vector<boost::any>& vec, const Tuple& t)
    {
        Tuple2Vector<Tuple, N - 1>::foreach(vec, t);
        vec.emplace_back(std::get<N - 1>(t));
    }
};

template<typename Tuple>
struct Tuple2Vector<Tuple, 1>
{
    static void foreach(std::vector<boost::any>& vec, const Tuple& t)
    {
        vec.emplace_back(std::get<0>(t));
    }
};

template<typename... Args>
void tuple2vector(std::vector<boost::any>& vec, const std::tuple<Args...>& t)
{
    Tuple2Vector<decltype(t), sizeof...(Args)>::foreach(vec, t);
}

void unpackArgs(std::vector<boost::any>&, std::size_t) {}

template<typename T, typename... Args>
void unpackArgs(std::vector<boost::any>& vec, std::size_t offset, T&& t, Args&&... args)
{
    t = boost::any_cast<T>(vec[offset]);
    unpackArgs(vec, offset + 1, std::forward<Args>(args)...);
}

}

#endif
