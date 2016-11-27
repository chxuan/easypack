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
    pack() : oa_(os_) {}

    template<typename... Args>
    void pack_args(Args&&... args)
    {
        pack_args_impl(oa_, std::forward<Args>(args)...);
    }

    std::string get_string()
    {
        return os_.str();
    }

private:
    std::ostringstream os_;
    boost::archive::binary_oarchive oa_;
};

}

#endif
