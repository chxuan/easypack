#ifndef _PACKUTIL_H
#define _PACKUTIL_H

#include <tuple>
#include "Comment.hpp"
#include "Traits.hpp"

namespace easypack
{

template<typename Tuple, std::size_t N>
struct PackTuple
{
    static void foreach(boost::archive::binary_oarchive& oa, const Tuple& t)
    {
        PackTuple<Tuple, N - 1>::foreach(oa, t);
        oa << std::get<N - 1>(t);
    }
};

template<typename Tuple>
struct PackTuple<Tuple, 1>
{
    static void foreach(boost::archive::binary_oarchive& oa, const Tuple& t)
    {
        oa << std::get<0>(t);
    }
};

template<typename... Args>
void packTuple(boost::archive::binary_oarchive& oa, const std::tuple<Args...>& t)
{
    PackTuple<decltype(t), sizeof...(Args)>::foreach(oa, t);
}

template<typename Tuple, std::size_t N>
struct UnPackTuple
{
    static void foreach(boost::archive::binary_iarchive& ia, Tuple& t)
    {
        UnPackTuple<Tuple, N - 1>::foreach(ia, t);
        ia >> std::get<N - 1>(t);
    }
};

template<typename Tuple>
struct UnPackTuple<Tuple, 1>
{
    static void foreach(boost::archive::binary_iarchive& ia, Tuple& t)
    {
        ia >> std::get<0>(t);
    }
};

template<typename... Args>
void unpackTuple(boost::archive::binary_iarchive& ia, std::tuple<Args...>& t)
{
    UnPackTuple<decltype(t), sizeof...(Args)>::foreach(ia, t);
}

void packArgs(boost::archive::binary_oarchive&) {}

template<typename T, typename... Args>
typename std::enable_if<!is_tuple<T>::value>::type packArgs(boost::archive::binary_oarchive& oa, T&& t, Args&&... args)
{
    oa << t;
    packArgs(oa, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
typename std::enable_if<is_tuple<T>::value>::type packArgs(boost::archive::binary_oarchive& oa, T&& t, Args&&... args)
{
    packTuple(oa, std::forward<T>(t));
    packArgs(oa, std::forward<Args>(args)...);
}

void unpackArgs(boost::archive::binary_iarchive&) {}

template<typename T, typename... Args>
typename std::enable_if<!is_tuple<T>::value>::type unpackArgs(boost::archive::binary_iarchive& ia, T&& t, Args&&... args)
{
    ia >> t;
    unpackArgs(ia, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
typename std::enable_if<is_tuple<T>::value>::type unpackArgs(boost::archive::binary_iarchive& ia, T&& t, Args&&... args)
{
    unpackTuple(ia, std::forward<T>(t));
    unpackArgs(ia, std::forward<Args>(args)...);
}

}

#endif
