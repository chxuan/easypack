#ifndef _PACK_H
#define _PACK_H

#include <sstream>
#include "Comment.hpp"
#include "PackUtil.hpp"
#include "Traits.hpp"

namespace easypack
{

class Pack
{
public:
    Pack(const Pack&) = delete;
    Pack& operator=(const Pack&) = delete;
    Pack() : m_oa(m_os) {}

    template<typename... Args>
    void pack(Args&&... args)
    {
        packArgs(m_oa, std::forward<Args>(args)...);
    }

    template<typename Tuple>
    typename std::enable_if<is_tuple<Tuple>::value>::type pack(Tuple&& t)
    {
        packTuple(m_oa, std::forward<Tuple>(t));
    }

    std::string getString()
    {
        return m_os.str();
    }

private:
    std::ostringstream m_os;
    boost::archive::binary_oarchive m_oa;
};

}

#endif
