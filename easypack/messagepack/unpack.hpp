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
    unpack(const std::string& content) : content_(std::move(content)){}

    template<typename... Args>
    void unpack_args(Args&&... args)
    {
        unpack_args_impl(content_, offset_, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpack_top(T& t)
    {
        unpack_args_impl(content_, offset_, t);
    }

private:
    std::string content_;
    std::size_t offset_ = 0;
};

}

#endif
