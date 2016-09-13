#ifndef _UNPACK_H
#define _UNPACK_H

#include <boost/any.hpp>
#include <kapok/Kapok.hpp>
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

    template<typename T>
    void unpack(T& t)
    {
        m_deserializer.Parse(m_content);
        m_deserializer.Deserialize(t);
    }

    template<typename... Args>
    void unpack(Args&&... args)
    {
        m_deserializer.Parse(m_content);
        std::tuple<typename std::decay<Args>::type...> tp;
        m_deserializer.Deserialize(tp);
        std::vector<boost::any> vec;
        vec.reserve(sizeof...(Args));
        tuple2vector(vec, tp);
        const std::size_t offset = 0;
        unpackArgs(vec, offset, std::forward<Args>(args)...);
    }

#if 0
    template<typename T>
    void unpackTop(T& t)
    {
        unpackArgs(m_content, m_offset, t);
    }
#endif

private:
    std::string m_content;
    DeSerializer m_deserializer;
};

}

#endif
