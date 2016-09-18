#ifndef _PACK_H
#define _PACK_H

#include <sstream>
#include "pack_util.hpp"

namespace easypack
{

class pack
{
public:
    pack() = default;
    pack(const pack&) = delete;
    pack& operator=(const pack&) = delete;

    template<typename... Args>
    void pack_args(Args&&... args)
    {
        pack_args_impl(_ss, std::forward<Args>(args)...);
    }

    std::string get_string()
    {
        return _ss.str();
    }

private:
    std::stringstream _ss;
};

}

#endif
