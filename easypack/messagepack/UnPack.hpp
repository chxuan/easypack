#ifndef _UNPACK_H
#define _UNPACK_H

#include <sstream>
#include "PackUtil.hpp"

namespace easypack
{

class UnPack
{
public:
    UnPack() = default;
    UnPack(const UnPack&) = delete;
    UnPack& operator=(const UnPack&) = delete;
    UnPack(const std::string& content) : m_content(std::move(content)){}

    template<typename... Args>
    void unpack(Args&&... args)
    {
        unpackArgs(m_content, m_offset, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpackTop(T& t)
    {
        unpackArgs(m_content, m_offset, t);
    }

private:
    std::string m_content;
    std::size_t m_offset = 0;
};

}

#endif
