cmake_minimum_required(VERSION 3.30)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(SILE-Interpreter)

set(used_modules
    lexer
    #parser
    #runtime
)

#foreach(m in LISTS used_modules)
#    add_subdirectory(${m})
#endforeach()

add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(runtime)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} used_modules)
