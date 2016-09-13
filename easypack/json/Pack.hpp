#ifndef _PACK_H
#define _PACK_H

#include <kapok/Kapok.hpp>

namespace easypack
{

class Pack
{
public:
    Pack() = default;
    Pack(const Pack&) = delete;
    Pack& operator=(const Pack&) = delete;

    template<typename T>
    void pack(T& t)
    {
        m_serializer.Serialize(t);
    }

    template<typename... Args>
    void pack(Args&&... args)
    {
        m_serializer.Serialize(std::forward_as_tuple(args...));
    }

    std::string getString()
    {
        return m_serializer.GetString();
    }

private:
    Serializer m_serializer;
};

}

#endif
