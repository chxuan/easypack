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
    unpack(const std::string& content) : is_(std::move(content)), ia_(is_) {}

    template<typename... Args>
    void unpack_args(Args&&... args)
    {
        unpack_args_impl(ia_, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpack_top(T& t)
    {
        unpack_args_impl(ia_, t);
    }

private:
    std::istringstream is_;
    boost::archive::binary_iarchive ia_;
};

}

#endif
