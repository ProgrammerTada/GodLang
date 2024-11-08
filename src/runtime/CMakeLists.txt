set(module_name runtime)

set(headerfiles
    irmruntime.h
)

set(sourcefiles
    irmruntime.cpp
)

add_library(${module_name} ${headerfiles} ${sourcefiles})
