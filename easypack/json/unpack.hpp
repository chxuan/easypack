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
    unpack(const std::string& content) : content_(std::move(content)) {}

    template<typename... Args>
    void unpack_args(Args&&... args)
    {
        dr_.Parse(content_);
        std::tuple<typename std::decay<Args>::type...> tp;
        dr_.Deserialize(tp);
        std::vector<boost::any> vec;
        vec.reserve(sizeof...(Args));
        tuple2vector(vec, tp);
        unpack_args_impl(vec, offset_, std::forward<Args>(args)...);
    }

    template<typename T>
    void unpack_top(T& t)
    {
        dr_.Parse(parse());
        dr_.Deserialize(t);
    }

private:
    std::string parse()
    {
        rapidjson::Document doc;
        doc.Parse<0>(content_.c_str());
        if (doc.HasParseError())
        {
            throw std::runtime_error("Parsing to document failed.");
        }

        if (!doc.IsArray())
        {
            throw std::runtime_error("Json format error.");
        }

        if (offset_ >= doc.Size())
        {
            throw std::runtime_error("Offset out of range.");
        }

        rapidjson::StringBuffer sb;
        rapidjson::Writer<StringBuffer> writer(sb);
        doc[offset_].Accept(writer);
        ++offset_;   
        return sb.GetString();
    }

private:
    std::string content_;
    std::size_t offset_ = 0;
    DeSerializer dr_;
};

}

#endif
