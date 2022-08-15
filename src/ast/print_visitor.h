#pragma once

#include "ast/const_visitor.h"

namespace AST
{
    class PrintVisitor : public ConstVisitor
    {

      public:
        void Visit( const Node &node ) override;
        void Visit( const TranslationUnit &translation_unit ) override;
        void Visit( const VariableDeclaration &variable__declaration ) override;
        void Visit( const IntrinsicType &type ) override;
        void Visit( const UserDefinedType &type ) override;
        void Visit( const SamplerType &type ) override;
        void Visit( const TypeModifier &modifier ) override;
        void Visit( const StorageClass &storage_class ) override;
        void Visit( const VariableDeclarationBody &body ) override;
        void Visit( const InitialValue &initial_value ) override;
        void Visit( const Annotations &annotations ) override;
        void Visit( const AnnotationEntry &annotation_entry ) override;
        void Visit( const TextureDeclaration &declaration ) override;
        void Visit( const SamplerDeclaration &declaration ) override;
        void Visit( const SamplerBody &body ) override;
        void Visit( const StructDefinition &definition ) override;

        // Expressions
        void Visit( const LiteralExpression &expression ) override;
        void Visit( const VariableExpression &expression ) override;
        void Visit( const UnaryOperationExpression &expression ) override;
        void Visit( const BinaryOperationExpression &expression ) override;
        void Visit( const CallExpression &expression ) override;
        void Visit( const ArgumentExpressionList &list ) override;
        void Visit( const Swizzle &swizzle ) override;
        void Visit( const PostfixSuffixCall &postfix_suffix ) override;
        void Visit( const PostfixSuffixVariable &postfix_suffix ) override;
        void Visit( const ConstructorExpression &expression ) override;
        void Visit( const ConditionalExpression &expression ) override;
        void Visit( const LValueExpression &expression ) override;
        void Visit( const PreModifyExpression &expression ) override;
        void Visit( const PostModifyExpression &expression ) override;
        void Visit( const CastExpression &expression ) override;
        void Visit( const AssignmentExpression &expression ) override;

        // Statements

        void Visit( const ReturnStatement &statement ) override;
        void Visit( const BreakStatement &statement ) override;
        void Visit( const ContinueStatement &statement ) override;
        void Visit( const DiscardStatement &statement ) override;
        void Visit( const EmptyStatement &statement ) override;
        void Visit( const ExpressionStatement &statement ) override;
        void Visit( const IfStatement &statement ) override;
        void Visit( const WhileStatement &statement ) override;
        void Visit( const DoWhileStatement &statement ) override;
        void Visit( const BlockStatement &statement ) override;
    };
}
