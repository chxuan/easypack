#include <iostream>
#include <vector>
#include <unordered_map>
#include "easypack/EasyPack.hpp"

void testBaseType()
{
    std::cout << "Test base type:" << std::endl;
    try
    {
        int age = 20;
        std::string name = "Jack";
        easypack::Pack p;
        p.pack(age, name);

        int age2 = 0;
        std::string name2;
        easypack::UnPack up(p.getString());
        up.unpack(age2, name2);
        /* up.unpackTop(age2); */
        /* up.unpackTop(name2); */

        std::cout << "age: " << age2 << std::endl;
        std::cout << "name: " << name2 << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void testSTL()
{
    std::cout << "Test stl type:" << std::endl;
    try
    {
        std::vector<int> vec { 1, 2 };
        std::unordered_map<int, std::string> m;
        m.emplace(1, "Hello");
        m.emplace(2, "world");
        easypack::Pack p;
        p.pack(vec, m);

        std::vector<int> vec2;
        std::unordered_map<int, std::string> m2;
        easypack::UnPack up(p.getString());
        up.unpack(vec2, m2);

        for (auto& iter : vec2)
        {
            std::cout << iter << std::endl;
        }
        for (auto& iter : m2)
        {
            std::cout << "key: " << iter.first << ", value: " << iter.second << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void testTuple()
{
    std::cout << "Test tuple type:" << std::endl;
    try
    {
        std::tuple<int, std::string> tp = std::make_tuple(10, "Tom");
        std::tuple<int, std::string> tpp = std::make_tuple(11, "Jack");
        std::string name = "Marlin";
        easypack::Pack p;
        p.pack(tp, tpp, name);
        std::cout << p.getString() << std::endl;

        std::tuple<int, std::string> tp2;
        std::tuple<int, std::string> tpp2;
        std::string name2;
        easypack::UnPack up(p.getString());
        up.unpack(tp2, tpp2, name2);
        std::cout << std::get<0>(tp2) << std::endl;
        std::cout << std::get<1>(tp2) << std::endl;
        std::cout << std::get<0>(tpp2) << std::endl;
        std::cout << std::get<1>(tpp2) << std::endl;
        std::cout << name2 << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

struct PersonInfo
{
    std::string name;
    int age;

#ifdef ENABLE_BOOST_SERIALIZATION
    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar & name;
        ar & age;
    }
#endif

#ifdef ENABLE_MSGPACK
    MSGPACK_DEFINE(name, age);
#endif

#ifdef ENABLE_JSON
    META(name, age);
#endif
};

void testClass()
{
#ifdef ENABLE_BOOST_SERIALIZATION
    std::cout << "Test boost.serialization user-defined classes type:" << std::endl;
#endif

#ifdef ENABLE_MSGPACK
    std::cout << "Test msgpack user-defined classes type:" << std::endl;
#endif

#ifdef ENABLE_JSON
    std::cout << "Test json user-defined classes type:" << std::endl;
#endif

    try
    {
        PersonInfo info { "Jack", 20 };
        easypack::Pack p;
        p.pack(info);

        PersonInfo person;
        easypack::UnPack up(p.getString());
        up.unpack(person);
        std::cout << person.name << " " << person.age << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    testBaseType();
    testSTL();
    testTuple();
    testClass();
    return 0;
}

