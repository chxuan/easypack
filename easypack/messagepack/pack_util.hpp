#ifndef _PACK_UTIL_H
#define _PACK_UTIL_H

#include <iostream>
#include <msgpack.hpp>

namespace easypack
{

void pack_args_impl(std::stringstream&) {}

template<typename T, typename... Args>
void pack_args_impl(std::stringstream& ss, T&& t, Args&&... args)
{
    msgpack::pack(ss, t);
    pack_args_impl(ss, std::forward<Args>(args)...);
}

void unpack_args_impl(const std::string&, std::size_t) {}

template<typename T, typename... Args>
void unpack_args_impl(const std::string& content, std::size_t offset, T&& t, Args&&... args)
{
    auto oh = msgpack::unpack(content.data(), content.size(), offset);
    t = oh.get().as<typename std::decay<T>::type>();
    unpack_args_impl(content, offset, std::forward<Args>(args)...);
}

}

#endif
