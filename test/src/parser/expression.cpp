#include "catch.hpp"
#include "ast/node.h"
#include "parser_helper.h"


AST::Expression * ParseLiteralExpression( const char * code )
{
    Parser parser( code, strlen( code ) );

    return  parser.m_Parser.literal_value();
}

TEST_CASE( "Literal are parsed", "[parser]" )
{
    AST::Expression * expression = 0;
    AST::LiteralExpression * literal_expression;

    SECTION( "Integer are parsed" )
    {
        expression = ParseLiteralExpression( " 1234 " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Int );
        CHECK( literal_expression->m_Value == "1234" );

    }

    SECTION( "Float are parsed" )
    {
        expression = ParseLiteralExpression( " 1234.5f " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Float );
        CHECK( literal_expression->m_Value == "1234.5f" );
    }

    SECTION( "Float are parsed2" )
    {
        expression = ParseLiteralExpression( " 1234.0 " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Float );
        CHECK( literal_expression->m_Value == "1234.0" );
    }

    SECTION( "Float are parsed3" )
    {
        expression = ParseLiteralExpression( " .123f " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Float );
        CHECK( literal_expression->m_Value == ".123f" );
    }

    SECTION( "Float are parsed4" )
    {
        expression = ParseLiteralExpression( " .123 " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Float );
        CHECK( literal_expression->m_Value == ".123" );
    }

    SECTION( "True is parsed" )
    {
        expression = ParseLiteralExpression( " true " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Bool );
        CHECK( literal_expression->m_Value == "true" );
    }

    SECTION( "False is parsed" )
    {
        expression = ParseLiteralExpression( " false " );

        REQUIRE( expression );

        literal_expression = dynamic_cast<AST::LiteralExpression*>( expression );

        REQUIRE( literal_expression );
        CHECK( literal_expression->m_Type == AST::LiteralExpression::Bool );
        CHECK( literal_expression->m_Value == "false" );
    }

    delete expression;
}

TEST_CASE( "Arithmetic expression are parsed", "[parser]" )
{
    AST::Expression * expression = 0;

    SECTION( "Addition is parsed" )
    {
        AST::BinaryOperationExpression * additive_expression;
        const char code[] = "1+2";
        Parser parser( code, sizeof( code ) - 1 );

        expression = parser.m_Parser.additive_expression();

        REQUIRE( expression );

        additive_expression = dynamic_cast<AST::BinaryOperationExpression*>( expression );

        REQUIRE( additive_expression );

        CHECK( additive_expression->m_Operation == AST::BinaryOperationExpression::Addition );
    }

    SECTION( "Subtraction is parsed" )
    {
        AST::BinaryOperationExpression * subtractive_expression;
        const char code[] = " 1 - 2 ";
        Parser parser( code, sizeof( code ) - 1 );

        expression = parser.m_Parser.additive_expression();

        REQUIRE( expression );

        subtractive_expression = dynamic_cast<AST::BinaryOperationExpression*>( expression );

        REQUIRE( subtractive_expression );

        CHECK( subtractive_expression->m_Operation == AST::BinaryOperationExpression::Subtraction );
    }

    delete expression;
}