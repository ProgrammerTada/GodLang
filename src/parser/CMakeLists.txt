set(module_name parser)

set(headerfiles
    node.h
    parser.h
)

set(sourcefiles
    parser.cpp
)

add_library(${module_name} ${headerfiles} ${sourcefiles})
