cmake_minimum_required(VERSION 3.31)
project(GodLang)

set(CMAKE_CXX_STANDARD 17)
message("asdfdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd")
message(${BOOST_ROOT})
include_directories(${BOOST_ROOT})

add_subdirectory(src)
