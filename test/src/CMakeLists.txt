add_executable(unittest main.cpp)

add_subdirectory(ast)
add_subdirectory(generation)
add_subdirectory(parser)

target_include_directories(unittest PUBLIC ../../contrib/catch)
target_link_libraries(unittest PRIVATE libshaker)

add_test(NAME unittest COMMAND unittest)