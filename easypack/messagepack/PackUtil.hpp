#ifndef _PACKUTIL_H
#define _PACKUTIL_H

#include <iostream>
#include <msgpack.hpp>

namespace easypack
{

void packArgs(std::stringstream&) {}

template<typename T, typename... Args>
void packArgs(std::stringstream& ss, T&& t, Args&&... args)
{
    msgpack::pack(ss, t);
    packArgs(ss, std::forward<Args>(args)...);
}

void unpackArgs(const std::string&, std::size_t) {}

template<typename T, typename... Args>
void unpackArgs(const std::string& content, std::size_t offset, T&& t, Args&&... args)
{
    auto oh = msgpack::unpack(content.data(), content.size(), offset);
    t = oh.get().as<typename std::decay<T>::type>();
    unpackArgs(content, offset, std::forward<Args>(args)...);
}

#if 0
void packArgs(boost::archive::binary_oarchive&) {}

template<typename T, typename... Args>
void packArgs(boost::archive::binary_oarchive& oa, T&& t, Args&&... args)
{
    oa << t;
    packArgs(oa, std::forward<Args>(args)...);
}

void unpackArgs(boost::archive::binary_iarchive&) {}

template<typename T, typename... Args>
void unpackArgs(boost::archive::binary_iarchive& ia, T&& t, Args&&... args)
{
    ia >> t;
    unpackArgs(ia, std::forward<Args>(args)...);
}

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
#endif

}

#endif
