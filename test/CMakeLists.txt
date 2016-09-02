cmake_minimum_required(VERSION 2.8)
project(test)

set(OUTPUTNAME test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated -g -O2 -std=c++14")

option(DEFINE_BOOST_SERIALIZATION "Boost serialization switch" OFF)
option(DEFINE_MSGPACK "msgpack switch" OFF)

if(DEFINE_BOOST_SERIALIZATION)
    add_definitions(-DENABLE_BOOST_SERIALIZATION)
endif(DEFINE_BOOST_SERIALIZATION)

if(DEFINE_MSGPACK)
    ADD_DEFINITIONS(-DENABLE_MSGPACK)
endif(DEFINE_MSGPACK)

aux_source_directory(. DIR_SRCS)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/..)

if(DEFINE_BOOST_SERIALIZATION)
    include_directories($ENV{BOOST_INCLUDE_PATH})
endif(DEFINE_BOOST_SERIALIZATION)

if(DEFINE_MSGPACK)
    include_directories(${PROJECT_SOURCE_DIR}/../3rdparty/msgpack-c/include)
endif(DEFINE_MSGPACK)

if(DEFINE_BOOST_SERIALIZATION)
    link_directories($ENV{BOOST_LIB_PATH})
endif(DEFINE_BOOST_SERIALIZATION)

add_executable(${OUTPUTNAME} ${DIR_SRCS})

if(DEFINE_BOOST_SERIALIZATION)
    target_link_libraries(${OUTPUTNAME} boost_serialization)
    target_link_libraries(${OUTPUTNAME} boost_system)
endif(DEFINE_BOOST_SERIALIZATION)
