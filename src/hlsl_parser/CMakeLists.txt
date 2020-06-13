

target_sources(libshaker PUBLIC HLSLLexer.cpp HLSLParser.cpp hlsl.cpp hlsl_traits.cpp)

target_include_directories(libshaker PUBLIC . ../../contrib/antlr)