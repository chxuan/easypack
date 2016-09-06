#ifndef _UNPACK_H
#define _UNPACK_H

#include <sstream>
#include "Comment.hpp"
#include "PackUtil.hpp"

namespace easypack
{

class UnPack
{
public:
    UnPack() = default;
    UnPack(const UnPack&) = delete;
    UnPack& operator=(const UnPack&) = delete;
    UnPack(const std::string& content) : m_is(std::move(content)), m_ia(m_is) {}

    template<typename... Args>
    void unpack(Args&&... args)
    {
        unpackArgs(m_ia, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpackTop(T& t)
    {
        unpackArgs(m_ia, t);
    }

private:
    std::istringstream m_is;
    boost::archive::binary_iarchive m_ia;
};

}

#endif
