#ifndef _PACK_H
#define _PACK_H

#include <sstream>
#include "comment.hpp"
#include "pack_util.hpp"

namespace easypack
{

class pack
{
public:
    pack(const pack&) = delete;
    pack& operator=(const pack&) = delete;
    pack() : _oa(_os) {}

    template<typename... Args>
    void pack_args(Args&&... args)
    {
        pack_args_impl(_oa, std::forward<Args>(args)...);
    }

    std::string get_string()
    {
        return _os.str();
    }

private:
    std::ostringstream _os;
    boost::archive::binary_oarchive _oa;
};

}

#endif
