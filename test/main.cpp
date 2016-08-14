#include <iostream>
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
        std::string address2;
        easypack::UnPack up(p.getString());
        /* up.unpack(age2, name2); */
        up.unpackTop(age2);
        up.unpackTop(name2);

        std::cout << age2 << std::endl;
        std::cout << name2 << std::endl;
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
        std::stack<int> s;
        s.push(100);
        s.push(200);
        m.emplace(1, "Hello");
        m.emplace(2, "world");
        easypack::Pack p;
        p.pack(vec, m, s);

        std::vector<int> vec2;
        std::unordered_map<int, std::string> m2;
        std::stack<int> s2;
        easypack::UnPack up(p.getString());
        up.unpack(vec2, m2, s2);

        for (auto& iter : vec2)
        {
            std::cout << iter << std::endl;
        }
        for (auto& iter : m2)
        {
            std::cout << "key: " << iter.first << ", value: " << iter.second << std::endl;
        }
        while (!s2.empty())
        {
            std::cout << s2.top() << std::endl;
            s2.pop(); 
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
    std::cout << "Test class type:" << std::endl;
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

