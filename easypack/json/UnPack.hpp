#ifndef _UNPACK_H
#define _UNPACK_H

#include <iostream>
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
    UnPack(const std::string& content) : m_content(std::move(content)) {}

    template<typename... Args>
    void unpack(Args&&... args)
    {
        m_deserializer.Parse(m_content);
        std::tuple<typename std::decay<Args>::type...> tp;
        m_deserializer.Deserialize(tp);
        m_vec.reserve(sizeof...(Args));
        tuple2vector(m_vec, tp);
        const std::size_t offset = 0;
        unpackArgs(m_vec, offset, std::forward<Args>(args)...);
    }

#if 0
    template<typename T>
    void unpackTop(T& t)
    {
        rapidjson::Document doc;
        doc.Parse<0>(m_content.c_str());
        if (doc.HasParseError())
        {
            /* throw std::runtime_error(std::string(doc.GetParseError())); */
        }
        for (SizeType i = 0; i < doc.Size(); ++i)
        {
            /* std::cout << doc[i].GetObject() << std::endl; */
            doc[i].GetObject();
        }
    }
#endif

private:
    std::string m_content;
    std::size_t m_offset = 0;
    std::vector<boost::any> m_vec;
    DeSerializer m_deserializer;
};

}

#endif
