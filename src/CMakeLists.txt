set(used_modules
    lexer
    parser
    runtime
)

foreach(mod ${used_modules})
    add_subdirectory(${mod})
endforeach()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

message("asdfdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd")
message(${BOOST_ROOT})

target_link_libraries(${PROJECT_NAME} ${used_modules})
