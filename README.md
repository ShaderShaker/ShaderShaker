ShaderShaker2
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

Premake is used as project generator. To build the project, follow those steps :

    cd src/hlsl_parser               # go to HLSL parser directory
    ./generate_parser.sh             # generate the HLSL parser (use .bat file for Windows systems)
    mkdir build                      #
    cmake -G "Unix Makefiles" ..     # You can use any generator
    make                             # make the lib and the binary
    make test                        # Run the tests


