#ifndef EMPTY_VISITOR_H
#define EMPTY_VISITOR_H

#include "visitor.h"

namespace AST
{

    class EmptyVisitor : public Visitor
    {

      public:
        void Visit( Node & /*node*/ ) override
        {
        }
        void Visit( TranslationUnit & /*translation_unit*/ ) override
        {
        }
        void Visit( VariableDeclaration & /*variable_declaration*/ ) override
        {
        }
        void Visit( IntrinsicType & /*type*/ ) override
        {
        }
        void Visit( UserDefinedType & /*type*/ ) override
        {
        }
        void Visit( SamplerType & /*type*/ ) override
        {
        }
        void Visit( TypeModifier & /*modifier*/ ) override
        {
        }
        void Visit( StorageClass & /*storage_class*/ ) override
        {
        }
        void Visit( VariableDeclarationBody & /*body*/ ) override
        {
        }
        void Visit( InitialValue & /*initial_value*/ ) override
        {
        }
        void Visit( Annotations & /*annotations*/ ) override
        {
        }
        void Visit( AnnotationEntry & /*annotation_entry*/ ) override
        {
        }
        void Visit( TextureDeclaration & /*declaration*/ ) override
        {
        }
        void Visit( SamplerDeclaration & /*declaration*/ ) override
        {
        }
        void Visit( SamplerBody & /*body*/ ) override
        {
        }
        void Visit( StructDefinition & /*definition*/ ) override
        {
        }
        void Visit( FunctionDeclaration & /*declaration*/ ) override
        {
        }
        void Visit( ArgumentList & /*list*/ ) override
        {
        }
        void Visit( Argument & /*argument*/ ) override
        {
        }

        // Expressions
        void Visit( LiteralExpression & /*expression*/ ) override
        {
        }
        void Visit( VariableExpression & /*expression*/ ) override
        {
        }
        void Visit( UnaryOperationExpression & /*expression*/ ) override
        {
        }
        void Visit( BinaryOperationExpression & /*expression*/ ) override
        {
        }
        void Visit( CallExpression & /*expression*/ ) override
        {
        }
        void Visit( ArgumentExpressionList & /*list*/ ) override
        {
        }
        void Visit( Swizzle & /*swizzle*/ ) override
        {
        }
        void Visit( PostfixSuffixCall & /*postfix_suffix*/ ) override
        {
        }
        void Visit( PostfixSuffixVariable & /*postfix_suffix*/ ) override
        {
        }
        void Visit( ConstructorExpression & /*expression*/ ) override
        {
        }
        void Visit( ConditionalExpression & /*expression*/ ) override
        {
        }
        void Visit( LValueExpression & /*expression*/ ) override
        {
        }
        void Visit( PreModifyExpression & /*expression*/ ) override
        {
        }
        void Visit( PostModifyExpression & /*expression*/ ) override
        {
        }
        void Visit( CastExpression & /*expression*/ ) override
        {
        }
        void Visit( AssignmentExpression & /*expression*/ ) override
        {
        }
        void Visit( PostfixExpression & /*expression*/ ) override
        {
        }

        // Statements

        void Visit( ReturnStatement & /*statement*/ ) override
        {
        }
        void Visit( BreakStatement & /*statement*/ ) override
        {
        }
        void Visit( ContinueStatement & /*statement*/ ) override
        {
        }
        void Visit( DiscardStatement & /*statement*/ ) override
        {
        }
        void Visit( EmptyStatement & /*statement*/ ) override
        {
        }
        void Visit( ExpressionStatement & /*statement*/ ) override
        {
        }
        void Visit( IfStatement & /*statement*/ ) override
        {
        }
        void Visit( WhileStatement & /*statement*/ ) override
        {
        }
        void Visit( DoWhileStatement & /*statement*/ ) override
        {
        }
        void Visit( BlockStatement & /*statement*/ ) override
        {
        }
        void Visit( AssignmentStatement & /*statement*/ ) override
        {
        }
        void Visit( VariableDeclarationStatement & /*statement*/ ) override
        {
        }
    };
}

#endif