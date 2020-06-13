
add_library(libshaker)

add_subdirectory(ast)
add_subdirectory(base)
add_subdirectory(generation)
add_subdirectory(hlsl_parser)
add_subdirectory(utils)


target_include_directories(libshaker PUBLIC . )
target_compile_features(libshaker PUBLIC cxx_std_17)

add_executable(shader_shaker main.cpp)
target_include_directories( shader_shaker PRIVATE ../contrib/tclap/include )
target_link_libraries(shader_shaker libshaker)