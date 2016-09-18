#ifndef _PACK_UTIL_H
#define _PACK_UTIL_H

#include <tuple>
#include "comment.hpp"
#include "traits_util.hpp"

namespace easypack
{

template<typename Tuple, std::size_t N>
struct tuple_oarchive
{
    static void foreach(boost::archive::binary_oarchive& oa, const Tuple& t)
    {
        tuple_oarchive<Tuple, N - 1>::foreach(oa, t);
        oa << std::get<N - 1>(t);
    }
};

template<typename Tuple>
struct tuple_oarchive<Tuple, 1>
{
    static void foreach(boost::archive::binary_oarchive& oa, const Tuple& t)
    {
        oa << std::get<0>(t);
    }
};

template<typename... Args>
void pack_tuple(boost::archive::binary_oarchive& oa, const std::tuple<Args...>& t)
{
    tuple_oarchive<decltype(t), sizeof...(Args)>::foreach(oa, t);
}

template<typename Tuple, std::size_t N>
struct tuple_iarchive
{
    static void foreach(boost::archive::binary_iarchive& ia, Tuple& t)
    {
        tuple_iarchive<Tuple, N - 1>::foreach(ia, t);
        ia >> std::get<N - 1>(t);
    }
};

template<typename Tuple>
struct tuple_iarchive<Tuple, 1>
{
    static void foreach(boost::archive::binary_iarchive& ia, Tuple& t)
    {
        ia >> std::get<0>(t);
    }
};

template<typename... Args>
void unpack_tuple(boost::archive::binary_iarchive& ia, std::tuple<Args...>& t)
{
    tuple_iarchive<decltype(t), sizeof...(Args)>::foreach(ia, t);
}

void pack_args_impl(boost::archive::binary_oarchive&) {}

template<typename T, typename... Args>
typename std::enable_if<!is_tuple<T>::value>::type pack_args_impl(boost::archive::binary_oarchive& oa, T&& t, Args&&... args)
{
    oa << t;
    pack_args_impl(oa, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
typename std::enable_if<is_tuple<T>::value>::type pack_args_impl(boost::archive::binary_oarchive& oa, T&& t, Args&&... args)
{
    pack_tuple(oa, std::forward<T>(t));
    pack_args_impl(oa, std::forward<Args>(args)...);
}

void unpack_args_impl(boost::archive::binary_iarchive&) {}

template<typename T, typename... Args>
typename std::enable_if<!is_tuple<T>::value>::type unpack_args_impl(boost::archive::binary_iarchive& ia, T&& t, Args&&... args)
{
    ia >> t;
    unpack_args_impl(ia, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
typename std::enable_if<is_tuple<T>::value>::type unpack_args_impl(boost::archive::binary_iarchive& ia, T&& t, Args&&... args)
{
    unpack_tuple(ia, std::forward<T>(t));
    unpack_args_impl(ia, std::forward<Args>(args)...);
}

}

#endif
