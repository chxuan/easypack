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

}

#endif
