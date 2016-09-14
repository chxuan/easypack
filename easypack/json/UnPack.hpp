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
        std::vector<boost::any> vec;
        vec.reserve(sizeof...(Args));
        tuple2vector(vec, tp);
        unpackArgs(vec, m_offset, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpackTop(T& t)
    {
        m_deserializer.Parse(parse());
        m_deserializer.Deserialize(t);
    }

private:
    std::string parse()
    {
        rapidjson::Document doc;
        doc.Parse<0>(m_content.c_str());
        if (doc.HasParseError())
        {
            throw std::runtime_error("Parsing to document failed.");
        }

        if (!doc.IsArray())
        {
            throw std::runtime_error("Json format error.");
        }

        if (m_offset >= doc.Size())
        {
            throw std::runtime_error("Offset out of range.");
        }

        rapidjson::StringBuffer sb;
        rapidjson::Writer<StringBuffer> writer(sb);
        doc[m_offset].Accept(writer);
        ++m_offset;   
        return sb.GetString();
    }

private:
    std::string m_content;
    std::size_t m_offset = 0;
    DeSerializer m_deserializer;
};

}

#endif
