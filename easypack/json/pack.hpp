#ifndef _PACK_H
#define _PACK_H

#include <kapok/Kapok.hpp>

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
        sr_.Serialize(std::forward_as_tuple(args...));
    }

    std::string get_string()
    {
        return sr_.GetString();
    }

private:
    Serializer sr_;
};

}

#endif
