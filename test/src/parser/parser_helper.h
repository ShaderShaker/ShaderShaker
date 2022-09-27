#ifndef PARSER_HELPER_H
    #define PARSER_HELPER_H

    #include "HLSLLexer.h"
    #include "HLSLParser.h"

    struct Parser
    {
        Parser( const char * code, const int size ) :
            m_Input( code, size ),
            m_Lexer( &m_Input ),
            m_TokenStream( &m_Lexer ),
            m_Parser( &m_TokenStream )
        {
        }

        antlr4::ANTLRInputStream
            m_Input;
        HLSLLexer
            m_Lexer;
        antlr4::CommonTokenStream
            m_TokenStream;
        HLSLParser
            m_Parser;
    };

#endif