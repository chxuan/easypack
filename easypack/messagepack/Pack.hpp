#ifndef _PACK_H
#define _PACK_H

#include <sstream>
#include "PackUtil.hpp"

namespace easypack
{

class Pack
{
public:
    Pack() = default;
    Pack(const Pack&) = delete;
    Pack& operator=(const Pack&) = delete;

    template<typename... Args>
    void pack(Args&&... args)
    {
        packArgs(m_ss, std::forward<Args>(args)...);
    }

    std::string getString()
    {
        return m_ss.str();
    }

private:
    std::stringstream m_ss;
};

}

#endif
