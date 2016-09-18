#ifndef _UNPACK_H
#define _UNPACK_H

#include <sstream>
#include "comment.hpp"
#include "pack_util.hpp"

namespace easypack
{

class unpack
{
public:
    unpack() = default;
    unpack(const unpack&) = delete;
    unpack& operator=(const unpack&) = delete;
    unpack(const std::string& content) : _is(std::move(content)), _ia(_is) {}

    template<typename... Args>
    void unpack_args(Args&&... args)
    {
        unpack_args_impl(_ia, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpack_top(T& t)
    {
        unpack_args_impl(_ia, t);
    }

private:
    std::istringstream _is;
    boost::archive::binary_iarchive _ia;
};

}

#endif
