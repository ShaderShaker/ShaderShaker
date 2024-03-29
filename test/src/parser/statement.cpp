#include "catch.hpp"
#include "ast/node.h"
#include "parser_helper.h"

TEST_CASE( "Jump statement are parsed", "[parser]" )
{
    AST::Statement * statement = 0;

    SECTION( "Return is parsed" )
    {
        AST::ReturnStatement * return_statement;
        const char code[] = " return; ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.jump_statement()->_statement;

        REQUIRE( statement );

        return_statement = dynamic_cast<AST::ReturnStatement*>( statement );

        REQUIRE( return_statement );
        CHECK( !return_statement->m_Expression );
    }

    SECTION( "Return with expression is parsed" )
    {
        AST::ReturnStatement * return_statement;
        const char code[] = " return 1; ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.jump_statement()->_statement;

        REQUIRE( statement );

        return_statement = dynamic_cast<AST::ReturnStatement*>( statement );

        REQUIRE( return_statement );
        CHECK( return_statement->m_Expression );
    }

    SECTION( "Break is parsed" )
    {
        AST::BreakStatement * break_statement;
        const char code[] = " break; ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.jump_statement()->_statement;

        REQUIRE( statement );

        break_statement = dynamic_cast<AST::BreakStatement*>( statement );

        REQUIRE( break_statement );
    }

    SECTION( "Continue is parsed" )
    {
        AST::ContinueStatement * continue_statement;
        const char code[] = " continue; ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.jump_statement()->_statement;

        REQUIRE( statement );

        continue_statement = dynamic_cast<AST::ContinueStatement*>( statement );

        REQUIRE( continue_statement );
    }

    SECTION( "Discard is parsed" )
    {
        AST::DiscardStatement * discard_statement;
        const char code[] = " discard; ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.jump_statement()->_statement;

        REQUIRE( statement );

        discard_statement = dynamic_cast<AST::DiscardStatement*>( statement );

        REQUIRE( discard_statement );
    }

    delete statement;
}

TEST_CASE( "Empty statement is parsed", "[parser]" )
{
    AST::Statement * statement = 0;
    AST::EmptyStatement * empty_statement;
    const char code[] = " ; ";
    Parser parser( code, sizeof( code ) - 1 );

    statement = parser.m_Parser.statement()->_statement;

    REQUIRE( statement );

    empty_statement = dynamic_cast<AST::EmptyStatement*>( statement );

    REQUIRE( empty_statement );

    delete statement;
}

TEST_CASE( "Expression statement is parsed", "[parser]" )
{
    AST::ExpressionStatement * statement = 0;
    const char code[] = " 1; ";
    Parser parser( code, sizeof( code ) - 1 );

    statement = parser.m_Parser.expression_statement()->_statement;

    REQUIRE( statement );
    REQUIRE( statement->m_Expression );

    delete statement;
}

TEST_CASE( "Block statement is parsed" )
{
    AST::BlockStatement * statement = 0;

    SECTION( "Empty block is parsed" )
    {
        const char code[] = " { } ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.block_statement()->_statement;

        REQUIRE( statement );
        CHECK( statement->m_StatementTable.size() == 0 );
    }

    SECTION( "Non empty block is parsed" )
    {
        const char code[] = " { 1; 2; 3; } ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.block_statement()->_statement;

        REQUIRE( statement );
        CHECK( statement->m_StatementTable.size() == 3 );
    }

    delete statement;
}

TEST_CASE( "Variable declaration statement is parsed" )
{
    AST::VariableDeclarationStatement * statement = 0;

    SECTION( "Simple variable is parsed" )
    {
        const char code[] = " float test; ";
        Parser parser( code, sizeof( code ) - 1 );

        statement = parser.m_Parser.local_variable_declaration()->_statement;

        REQUIRE( statement );
        CHECK( statement->m_Type->m_Name == "float" );
        REQUIRE( statement->m_BodyTable.size() == 1 );
        CHECK( statement->m_BodyTable[ 0 ]->m_Name == "test" );
        CHECK( !statement->m_BodyTable[ 0 ]->m_InitialValue  );
    }

    delete statement;
}

