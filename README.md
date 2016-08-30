Serialization framework based on boost.serialization
===============================================

## 简介

easypack是基于[boost.serialization][1]的二进制序列化框架，使用极其方便。

## Examples
    
* **基本类型**

    ```cpp
    int age = 20;
    std::string name = "Jack";
    easypack::Pack p;
    p.pack(age, name);
    
    int age2;
    std::string name2;
    easypack::UnPack up(p.getString());
    up.unpack(age2, name2); 
    /* up.unpackTop(age2); */
    /* up.unpackTop(name2); */
    ```  
可以看到，pack/unpack支持变参，并且还支持出栈式反序列化，使用非常方便。

* **std::tuple**

    ```cpp
    std::tuple<int, std::string> tp = std::make_tuple(10, "Tom");
    easypack::Pack p;
    p.pack(tp);

    std::tuple<int, std::string> tp2;
    easypack::UnPack up(p.getString());
    up.unpack(tp2);
    ```  
boost序列化默认不支持std::tuple类型，easypack序列化std::tuple提供了和序列化基本类型一样的接口。

* **STL类型**

    ```cpp
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
    ```

* **类类型**

    ```cpp
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
    
    PersonInfo info { "Jack", 20 };
    easypack::Pack p;
    p.pack(info);

    PersonInfo person;
    easypack::UnPack up(p.getString());
    up.unpack(person);
    ```

## 依赖性

* boost.serialization
* c++11

## 兼容性

* `Linux x86_64` gcc 4.8, gcc4.9, gcc 5.
* `Windows x86_64` Visual Studio 2015

## License
This software is licensed under the [MIT license][2]. © 2016 chxuan


  [1]: http://www.boost.org/
  [2]: https://github.com/chxuan/easypack/blob/master/LICENSE
