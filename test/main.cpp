#include <iostream>
#include <vector>
#include <unordered_map>
#include "timer.hpp"
#include "easypack/easypack.hpp"

void test_base_type()
{
    std::cout << "Test base type:" << std::endl;
    try
    {
        int age = 20;
        std::string name = "Jack";
        easypack::pack p;
        p.pack_args(age, name);

        int age2 = 0;
        std::string name2;
        easypack::unpack up(p.get_string());
        up.unpack_args(age2, name2);
        /* up.unpack_top(age2); */
        /* up.unpack_top(name2); */

        std::cout << "age: " << age2 << std::endl;
        std::cout << "name: " << name2 << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void test_stl()
{
    std::cout << "Test stl type:" << std::endl;
    try
    {
        std::vector<int> vec { 1, 2 };
        std::unordered_map<int, std::string> m;
        m.emplace(1, "Hello");
        m.emplace(2, "world");
        easypack::pack p;
        p.pack_args(vec, m);

        std::vector<int> vec2;
        std::unordered_map<int, std::string> m2;
        easypack::unpack up(p.get_string());
        up.unpack_args(vec2, m2);

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

void test_tuple()
{
    std::cout << "Test tuple type:" << std::endl;
    try
    {
        std::tuple<int, std::string> tp = std::make_tuple(10, "Tom");
        std::tuple<int, std::string> tpp = std::make_tuple(11, "Jack");
        std::string name = "Marlin";
        easypack::pack p;
        p.pack_args(tp, tpp, name);

        std::tuple<int, std::string> tp2;
        std::tuple<int, std::string> tpp2;
        std::string name2;
        easypack::unpack up(p.get_string());
        up.unpack_args(tp2, tpp2, name2);
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
    std::string name2;
    std::string name3;
    std::string name4;
    std::string name5;
    std::string name6;
    std::string name7;
    int age;

#ifdef ENABLE_BOOST_SERIALIZATION
    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar & name;
        ar & name2;
        ar & name3;
        ar & name4;
        ar & name5;
        ar & name6;
        ar & name7;
        ar & age;
    }
#endif

#ifdef ENABLE_MSGPACK
    MSGPACK_DEFINE(name, name2, name3, name4, name5, name6, name7, age);
#endif

#ifdef ENABLE_JSON
    META(name, name2, name3, name4, name5, name6, name7, age);
#endif
};

void test_class()
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
        timer t;
        /* for (int i = 0; i < 1000000; ++i) */
        for (int i = 0; i < 10000; ++i)
        {
            PersonInfo info { "Jack", "Jack", "Jack", "Jack", "Jack", "Jack", "Jack", 20 };
            easypack::pack p;
            p.pack_args(info);

            PersonInfo person;
            easypack::unpack up(p.get_string());
            up.unpack_args(person);
        }
        /* std::cout << person.name << " " << person.age << std::endl; */
        std::cout << "time: " << t.elapsed() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    /* test_base_type(); */
    /* test_stl(); */
    /* test_tuple(); */
    test_class();
    return 0;
}

