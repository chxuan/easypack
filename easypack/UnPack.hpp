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
    void parse(const std::string& content)
    {
        m_is.str(content);
    }

    template<typename... Args>
    void unpack(Args&&... args)
    {
        boost::archive::binary_iarchive ia(m_is);
        unpackArgs(ia, std::forward<Args>(args)...);
    }

    template<typename Tuple>
    typename std::enable_if<is_tuple<Tuple>::value>::type unpack(Tuple&& t)
    {
        boost::archive::binary_iarchive ia(m_is);
        unpackTuple(ia, std::forward<Tuple>(t));
    }

private:
    std::istringstream m_is;
};

}

#endif
