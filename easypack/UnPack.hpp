#ifndef _UNPACK_H
#define _UNPACK_H

#include <sstream>
#include "Comment.hpp"
#include "PackUtil.hpp"
#include "Traits.hpp"

namespace easypack
{

class UnPack : private NonCopyable
{
public:
    UnPack(const std::string& content) : m_is(content), m_ia(m_is) {}

    template<typename... Args>
    void unpack(Args&&... args)
    {
        unpackArgs(m_ia, std::forward<Args>(args)...);
    }

    template<typename Tuple>
    typename std::enable_if<is_tuple<Tuple>::value>::type unpack(Tuple&& t)
    {
        unpackTuple(m_ia, std::forward<Tuple>(t));
    }

    template<typename T>
    void unpackTop(T& t)
    {
        m_ia >> t;
    }

private:
    std::istringstream m_is;
    boost::archive::binary_iarchive m_ia;
};

}

#endif
