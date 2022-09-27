ShaderShaker2 ![](https://github.com/ShaderShaker/ShaderShaker/workflows/CI/badge.svg)
=============

Shader Shaker has been developed to solve our two main problems with shader development :

- The multiple languages our engine needs to support
- The combinational number of shader with the supported rendering technique

How it works
------------

The architecture is simple :

1. The HLSL files are converted to an AST using a ANTLR parser.
2. The AST is then processed, cleaned and optimized.
3. Finally, a writer generates code.

How to build
------------

Cmake is used as project generator. To build the project, follow those steps :

    mkdir build                  #
    cmake -G "Unix Makefiles" .. # You can use any generator
    make                         # make the lib and the binary
    make test                    # Run the tests
