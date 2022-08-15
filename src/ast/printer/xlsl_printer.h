#pragma once

#include "ast/const_visitor.h"
#include <ostream>

namespace AST
{

    class XLSLPrinter : public ConstVisitor
    {
      public:
        XLSLPrinter( std::ostream &stream ) : m_Stream( stream )
        {
        }

        XLSLPrinter &operator=( const XLSLPrinter &other ) = delete;

        void Visit( const Node &node ) override;
        void Visit( const TranslationUnit &translation_unit ) override;
        void Visit( const VariableDeclaration &variable_declaration ) override;
        void Visit( const IntrinsicType &type ) override;
        void Visit( const UserDefinedType &type ) override;
        void Visit( const SamplerType &type ) override;
        void Visit( const TypeModifier &modifier ) override;
        void Visit( const StorageClass &storage_class ) override;
        void Visit( const ArgumentList &list ) override;

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
        void Visit( const PostfixExpression &expression ) override;

        void Visit( const ReturnStatement &statement ) override;
        void Visit( const BreakStatement &statement ) override;
        void Visit( const ContinueStatement &statement ) override;
        void Visit( const EmptyStatement &statement ) override;
        void Visit( const ExpressionStatement &statement ) override;
        void Visit( const IfStatement &statement ) override;
        void Visit( const WhileStatement &statement ) override;
        void Visit( const DoWhileStatement &statement ) override;
        void Visit( const BlockStatement &statement ) override;
        void Visit( const AssignmentStatement &statement ) override;
        void Visit( const VariableDeclarationStatement &statement ) override;

      protected:
        template < class _Table_ >
        void VisitTable( ConstVisitor &visitor, _Table_ &table, const char *separator_cstr, bool add_endl );

        std::ostream &m_Stream;
    };
}

