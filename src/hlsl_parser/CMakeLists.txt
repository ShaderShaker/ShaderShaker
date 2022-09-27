

add_library(hlslparser STATIC hlsl.cpp)

include(ExternalAntlr4Cpp)

set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/antlr-4.10.1-complete.jar)
find_package(ANTLR REQUIRED)
antlr_target(HLSL HLSL.g4)

target_include_directories(hlslparser PUBLIC ${ANTLR_HLSL_OUTPUT_DIR} .. ${ANTLR4_INCLUDE_DIRS})
target_sources(hlslparser PRIVATE ${ANTLR_HLSL_OUTPUTS})
target_compile_features(hlslparser PUBLIC cxx_std_17)
target_link_libraries(hlslparser PUBLIC antlr4_static)


target_link_libraries(libshaker hlslparser)