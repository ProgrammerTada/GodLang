set(module_name lexer)

set(headerfiles
    lexer.h
)

set(sourcefiles
    lexer.cpp
)

add_library(${module_name} ${headerfiles} ${sourcefiles})
