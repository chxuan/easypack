#ifndef _UNPACK_H
#define _UNPACK_H

#include <iostream>
#include <boost/any.hpp>
#include <kapok/Kapok.hpp>
#include "pack_util.hpp"

namespace easypack
{

class unpack
{
public:
    unpack() = default;
    unpack(const unpack&) = delete;
    unpack& operator=(const unpack&) = delete;
    unpack(const std::string& content) : _content(std::move(content)) {}

    template<typename... Args>
    void unpack_args(Args&&... args)
    {
        _dr.Parse(_content);
        std::tuple<typename std::decay<Args>::type...> tp;
        _dr.Deserialize(tp);
        std::vector<boost::any> vec;
        vec.reserve(sizeof...(Args));
        tuple2vector(vec, tp);
        unpack_args_impl(vec, _offset, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpackTop(T& t)
    {
        _dr.Parse(parse());
        _dr.Deserialize(t);
    }

private:
    std::string parse()
    {
        rapidjson::Document doc;
        doc.Parse<0>(_content.c_str());
        if (doc.HasParseError())
        {
            throw std::runtime_error("Parsing to document failed.");
        }

        if (!doc.IsArray())
        {
            throw std::runtime_error("Json format error.");
        }

        if (_offset >= doc.Size())
        {
            throw std::runtime_error("Offset out of range.");
        }

        rapidjson::StringBuffer sb;
        rapidjson::Writer<StringBuffer> writer(sb);
        doc[_offset].Accept(writer);
        ++_offset;   
        return sb.GetString();
    }

private:
    std::string _content;
    std::size_t _offset = 0;
    DeSerializer _dr;
};

}

#endif
