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
        _sr.Serialize(std::forward_as_tuple(args...));
    }

    std::string get_string()
    {
        return _sr.GetString();
    }

private:
    Serializer _sr;
};

}

#endif
