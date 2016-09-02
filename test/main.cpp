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
        easypack::Pack p;
        p.pack(tp);

        std::tuple<int, std::string> tp2;
        easypack::UnPack up(p.getString());
        up.unpack(tp2);
        std::cout << std::get<0>(tp2) << std::endl;
        std::cout << std::get<1>(tp2) << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

#ifdef ENABLE_BOOST_SERIALIZATION
struct PersonInfo
{
    std::string name;
    int age;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar & name;
        ar & age;
    }
};

void testClass()
{
    std::cout << "Test boost.serialization user-defined classes type:" << std::endl;
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
#endif

#ifdef ENABLE_MSGPACK
struct PersonInfo
{
    std::string name;
    int age;

    MSGPACK_DEFINE(name, age);
};

void testClass()
{
    std::cout << "Test msgpack user-defined classes type:" << std::endl;
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
#endif

int main()
{
    testBaseType();
    testSTL();
    testTuple();
    testClass();
    return 0;
}

