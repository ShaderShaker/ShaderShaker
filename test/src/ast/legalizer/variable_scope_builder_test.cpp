#include "catch.hpp"
#include "ast/node.h"
#include "ast/legalizer/variable_scope_builder.h"
#include "../../parser/parser_helper.h"
#include <sstream>

static AST::TranslationUnit * ParseCode(
    const std::string & code
    )
{
    Parser parser( code.c_str(), code.length() );

    return parser.m_Parser.translation_unit();
}

void CheckVariable(
    const Base::ObjectRef< AST::ScopeBuilder::Variable > & variable,
    const std::string & name,
    const std::string & type
    )
{
    CHECK( variable->m_Name == name );
    CHECK( variable->m_Type == type );
}

void CheckScope(
    const Base::ObjectRef< AST::ScopeBuilder::Scope > & scope,
    const AST::ScopeBuilder::Scope & parent_scope,
    const unsigned int children_scope_count,
    const std::string & scope_name,
    const std::string & scope_type,
    const unsigned int variable_count
    )
{
    CHECK( scope->m_Parent == &parent_scope );
    CHECK( scope->m_Children.size() == children_scope_count );
    CHECK( scope->m_Name == scope_name );
    CHECK( scope->m_Type == scope_type );
    CHECK( scope->m_Variables.size() == variable_count );
}

TEST_CASE( "GlobalScope", "Variables are correctly added to the global scope" )
{
    SECTION( "One variable" )
    {
        AST::TranslationUnit * unit = ParseCode( "float f = 123.0f;" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "f", "float" );
    }

    SECTION( "Multiple variables initialized in same expression" )
    {
        AST::TranslationUnit * unit = ParseCode( "float f1 = 123.0f, f2;" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "f1", "float" );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 1 ], "f2", "float" );
    }

    SECTION( "Multiple variables initialized in multiple expressions" )
    {
        AST::TranslationUnit * unit = ParseCode( "float f1 = 123.0f; float f2;" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "f1", "float" );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 1 ], "f2", "float" );
    }

    SECTION( "Multiple variables of different types" )
    {
        AST::TranslationUnit * unit = ParseCode( "float f = 123.0f; int i = 1;" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "f", "float" );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 1 ], "i", "int" );
    }
}

TEST_CASE( "FunctionScope", "Functions create a new child scope" )
{
    SECTION( "Void function no argument" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo() {}" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "void", 0 );
    }

    SECTION( "Void function one argument" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) {}" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "void", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "f", "float" );
    }

    SECTION( "Void function multiple arguments" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f, int i ) {}" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "void", 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "f", "float" );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 1 ], "i", "int" );
    }

    SECTION( "Function with one statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { float g = 1.0f; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "void", 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "f", "float" );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 1 ], "g", "float" );
    }

    SECTION( "Function with multiple statements" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { float g = 1.0f; int h = 3; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 0, "foo", "void", 3 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );
        CheckVariable( function_scope->m_Variables[ 1 ], "g", "float" );
        CheckVariable( function_scope->m_Variables[ 2 ], "h", "int" );
    }

    SECTION( "Function with block" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { { float g = 1.0f; } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > block_scope = function_scope->m_Children[ 0 ];
        CheckScope( block_scope, *scope_data.m_GlobalScope.m_Children[ 0 ], 0, "", "block", 1 );
        CheckVariable( block_scope->m_Variables[ 0 ], "g", "float" );
    }

    SECTION( "Function with multiple blocks" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { { float g = 1.0f; } { float h = 1.0f; } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 2, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > block_scope_1 = function_scope->m_Children[ 0 ];
        CheckScope( block_scope_1, *function_scope, 0, "", "block", 1 );
        CheckVariable( block_scope_1->m_Variables[ 0 ], "g", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > block_scope_2 = function_scope->m_Children[ 1 ];
        CheckScope( block_scope_2, *function_scope, 0, "", "block", 1 );
        CheckVariable( block_scope_2->m_Variables[ 0 ], "h", "float" );
    }

    SECTION( "Function with nested blocks" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { { float g = 1.0f; { float h = 1.0f; } } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > block_scope = function_scope->m_Children[ 0 ];
        CheckScope( block_scope, *function_scope, 1, "", "block", 1 );
        CheckVariable( block_scope->m_Variables[ 0 ], "g", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > nested_block_scope = block_scope->m_Children[ 0 ];
        CheckScope( nested_block_scope, *block_scope, 0, "", "block", 1 );
        CheckVariable( nested_block_scope->m_Variables[ 0 ], "h", "float" );
    }

    SECTION( "Function with nested blocks and variable redefinition" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { { float f = 2.0f; { float f = 3.0f; } } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > block_scope = function_scope->m_Children[ 0 ];
        CheckScope( block_scope, *function_scope, 1, "", "block", 1 );
        CheckVariable( block_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > nested_block_scope = block_scope->m_Children[ 0 ];
        CheckScope( nested_block_scope, *block_scope, 0, "", "block", 1 );
        CheckVariable( nested_block_scope->m_Variables[ 0 ], "f", "float" );
    }

    SECTION( "Function with if statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { if ( f > 0.5f ) { float g = 1.0f; } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > if_scope = function_scope->m_Children[ 0 ];
        CheckScope( if_scope, *function_scope, 0, "if", "block", 1 );
        CheckVariable( if_scope->m_Variables[ 0 ], "g", "float" );
    }

    SECTION( "Function with if / else statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { if ( f > 0.5f ) { float f = 1.0f; } else { float f = bar(); } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 2, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > if_scope = function_scope->m_Children[ 0 ];
        CheckScope( if_scope, *function_scope, 0, "if", "block", 1 );
        CheckVariable( if_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > else_scope = function_scope->m_Children[ 1 ];
        CheckScope( else_scope, *function_scope, 0, "else", "block", 1 );
        CheckVariable( else_scope->m_Variables[ 0 ], "f", "float" );
    }

    SECTION( "Function with for statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { for ( int i = 0; i < 10; i++ ) { float g = 1.0f; } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > for_scope = function_scope->m_Children[ 0 ];
        CheckScope( for_scope, *function_scope, 0, "for", "block", 2 );
        CheckVariable( for_scope->m_Variables[ 0 ], "i", "int" );
        CheckVariable( for_scope->m_Variables[ 1 ], "g", "float" );
    }

    SECTION( "Function with for statement without init statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( int i ) { for ( ; i < 10; i++ ) { float g = 1.0f; } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "i", "int" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > for_scope = function_scope->m_Children[ 0 ];
        CheckScope( for_scope, *function_scope, 0, "for", "block", 1 );
        CheckVariable( for_scope->m_Variables[ 0 ], "g", "float" );
    }

    SECTION( "Function with while statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { while ( f < 10.0f ) { float g = 1.0f; f++; } }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > while_scope = function_scope->m_Children[ 0 ];
        CheckScope( while_scope, *function_scope, 0, "while", "block", 1 );
        CheckVariable( while_scope->m_Variables[ 0 ], "g", "float" );
    }

    SECTION( "Function with dowhile statement" )
    {
        AST::TranslationUnit * unit = ParseCode( "void foo( float f ) { do { float g = 1.0f; } while ( true ); }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );

        Base::ObjectRef< AST::ScopeBuilder::Scope > function_scope = scope_data.m_GlobalScope.m_Children[ 0 ];
        CheckScope( function_scope, scope_data.m_GlobalScope, 1, "foo", "void", 1 );
        CheckVariable( function_scope->m_Variables[ 0 ], "f", "float" );

        Base::ObjectRef< AST::ScopeBuilder::Scope > while_scope = function_scope->m_Children[ 0 ];
        CheckScope( while_scope, *function_scope, 0, "do", "block", 1 );
        CheckVariable( while_scope->m_Variables[ 0 ], "g", "float" );
    }

    SECTION( "Result function no argument" )
    {
        AST::TranslationUnit * unit = ParseCode( "float foo() { return 1.0f; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "float", 0 );
    }

    SECTION( "Result function one argument" )
    {
        AST::TranslationUnit * unit = ParseCode( "float foo( float f ) { return f; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "float", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "f", "float" );
    }

    SECTION( "Result function multiple arguments" )
    {
        AST::TranslationUnit * unit = ParseCode( "float foo( float f, int i ) { return f * i; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "float", 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "f", "float" );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 1 ], "i", "int" );
    }

    SECTION( "Multiple functions" )
    {
        AST::TranslationUnit * unit = ParseCode( "float foo( int i ) { return 10.0f; } int bar( float f ) { return 0; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 2 );

        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "float", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "i", "int" );

        CheckScope( scope_data.m_GlobalScope.m_Children[ 1 ], scope_data.m_GlobalScope, 0, "bar", "int", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 1 ]->m_Variables[ 0 ], "f", "float" );
    }

    SECTION( "Variable and function" )
    {
        AST::TranslationUnit * unit = ParseCode( "float f = 1.0f; float foo( int i ) { return 10.0f; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "f", "float" );

        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "foo", "float", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "i", "int" );
    }
}

TEST_CASE( "StructureScope", "Structure declarations create a new child scope" )
{
    SECTION( "Structure with one member" )
    {
        AST::TranslationUnit * unit = ParseCode( "struct VS_OUTPUT { float4 Position; };" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "VS_OUTPUT", "", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "Position", "float4" );
    }

    SECTION( "Structure with multiple members" )
    {
        AST::TranslationUnit * unit = ParseCode( "struct VS_OUTPUT { float4 Position; float2 TexturePosition; };" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "VS_OUTPUT", "", 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "Position", "float4" );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 1 ], "TexturePosition", "float2" );
    }

    SECTION( "Multiple structures with multiple members" )
    {
        AST::TranslationUnit * unit = ParseCode( "struct VS_OUTPUT { float4 Position; float2 TexturePosition; }; struct PS_OUTPUT { float4 Position; float4 Color; };" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 2 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "VS_OUTPUT", "", 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "Position", "float4" );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 1 ], "TexturePosition", "float2" );

        CheckScope( scope_data.m_GlobalScope.m_Children[ 1 ], scope_data.m_GlobalScope, 0, "PS_OUTPUT", "", 2 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 1 ]->m_Variables[ 0 ], "Position", "float4" );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 1 ]->m_Variables[ 1 ], "Color", "float4" );
    }

    SECTION( "Structures with global variables" )
    {
        AST::TranslationUnit * unit = ParseCode( "struct VS_OUTPUT { float4 Position; }; float4x4 WvpXf;" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "WvpXf", "float4x4" );

        CHECK( scope_data.m_GlobalScope.m_Children.size() == 1 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "VS_OUTPUT", "", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "Position", "float4" );
    }

    SECTION( "Multiple structures with functions" )
    {
        AST::TranslationUnit * unit = ParseCode( "struct VS_OUTPUT { float4 Position; }; float foo() { return 1.0f; }" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.empty() );
        CHECK( scope_data.m_GlobalScope.m_Children.size() == 2 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "VS_OUTPUT", "", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "Position", "float4" );

        CheckScope( scope_data.m_GlobalScope.m_Children[ 1 ], scope_data.m_GlobalScope, 0, "foo", "float", 0 );
    }

    SECTION( "Multiple structures with global variables and functions" )
    {
        AST::TranslationUnit * unit = ParseCode( "struct VS_OUTPUT { float4 Position; }; float foo( int i ) { return 1.0f; } float4x4 WvpXf;" );
        AST::ScopeBuilder::ScopeData scope_data;
        AST::VariableScopeBuilder scope_builder( scope_data );
        unit->Visit( scope_builder );

        CHECK( scope_data.m_GlobalScope.m_Variables.size() == 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Variables[ 0 ], "WvpXf", "float4x4" );

        CHECK( scope_data.m_GlobalScope.m_Children.size() == 2 );
        CheckScope( scope_data.m_GlobalScope.m_Children[ 0 ], scope_data.m_GlobalScope, 0, "VS_OUTPUT", "", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 0 ]->m_Variables[ 0 ], "Position", "float4" );

        CheckScope( scope_data.m_GlobalScope.m_Children[ 1 ], scope_data.m_GlobalScope, 0, "foo", "float", 1 );
        CheckVariable( scope_data.m_GlobalScope.m_Children[ 1 ]->m_Variables[ 0 ], "i", "int" );
    }
}