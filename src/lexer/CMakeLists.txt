set(module_name lexer)

set(headerfiles
    lexer.h
)

set(sourcefiles
    lexer.cpp
)

add_library(${module_name} ${headerfiles} ${sourcefiles})
target_include_directories(${module_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
