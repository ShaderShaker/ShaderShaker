#include "hlsl.h"

#include "HLSLLexer.h"
#include "HLSLParser.h"
#include "ast/node.h"


Base::ObjectRef<AST::TranslationUnit> HLSL::ParseHLSL( const std::string & filename )
{
    antlr4::ANTLRFileStream input;
    input.loadFromFile( filename );
    HLSLLexer lexer( &input );
    antlr4::CommonTokenStream token_stream( &lexer );
    HLSLParser parser( &token_stream );

    return parser.translation_unit()->_unit;
}