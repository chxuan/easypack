#ifndef _UNPACK_H
#define _UNPACK_H

#include <sstream>
#include "pack_util.hpp"

namespace easypack
{

class unpack
{
public:
    unpack() = default;
    unpack(const unpack&) = delete;
    unpack& operator=(const unpack&) = delete;
    unpack(const std::string& content) : _content(std::move(content)){}

    template<typename... Args>
    void unpack_args(Args&&... args)
    {
        unpack_args_impl(_content, _offset, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpack_top(T& t)
    {
        unpack_args_impl(_content, _offset, t);
    }

private:
    std::string _content;
    std::size_t _offset = 0;
};

}

#endif
