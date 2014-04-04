#ifndef EXPRESSION_NODE_H
    #define EXPRESSION_NODE_H

    namespace AST
    {

        struct Expression : Node
        {

        };

        struct ConditionalExpression : Expression
        {
            AST_HandleVisitor()

            std::shared_ptr<Expression> m_Condition;
            std::shared_ptr<Expression> m_IfTrue;
            std::shared_ptr<Expression> m_IfFalse;

        };

        struct BinaryOperationExpression : Expression
        {
            AST_HandleVisitor()
            enum Operation
            {
                LogicalOr,
                LogicalAnd,
                BitwiseOr,
                BitwiseXor,
                BitwiseAnd,
                Equality,
                Difference,
                LessThan,
                GreaterThan,
                LessThanOrEqual,
                GreaterThanOrEqual,
                BitwiseLeftShift,
                BitwiseRightShift,
                Addition,
                Subtraction,
                Multiplication,
                Division,
                Modulo,
            };

            BinaryOperationExpression(
                Operation operation,
                Expression * left_expression,
                Expression * right_expression
                ) :
                m_Operation( operation ),
                m_LeftExpression( left_expression ),
                m_RightExpression( right_expression )
            {}

            Operation
                m_Operation;
            std::shared_ptr<Expression>
                m_LeftExpression,
                m_RightExpression;

        };

        struct UnaryOperationExpression : Expression
        {
            AST_HandleVisitor()
            enum Operation
            {
                Plus,
                Minus,
                Not,
                BitwiseNot
            };

            UnaryOperationExpression(
                Operation operation,
                Expression * expression
                ) :
                m_Operation( operation ),
                m_Expression( expression )
            {}

            Operation
                m_Operation;
            std::shared_ptr<Expression>
                m_Expression;

        };

        struct CastExpression: Expression
        {
            AST_HandleVisitor()
            CastExpression(
                Type * type,
                int array_size,
                Expression * expression
                ) :
                m_Type( type ),
                m_ArraySize( array_size ),
                m_Expression( expression )
            {

            }

            std::shared_ptr<Type>
                m_Type;
            int
                m_ArraySize;
            std::shared_ptr<Expression>
                m_Expression;

        };

        struct LiteralExpression : Expression
        {
            AST_HandleVisitor()
            enum Type
            {
                Int,
                Float,
                Bool
            };

            LiteralExpression( Type type, const std::string & value ) : m_Type( type ), m_Value( value )
            {

            }

            Type
                m_Type;
            std::string
                m_Value;
        };

        struct VariableExpression: Expression
        {
            AST_HandleVisitor()

            VariableExpression( const std::string & name ) : m_Name( name ){}

            std::string
                m_Name;
            std::shared_ptr<Expression>
                m_SubscriptExpression;
        };

        struct PostfixExpression : Expression
        {
            AST_HandleVisitor()
            PostfixExpression( Expression *expression, PostfixSuffix * suffix ) : m_Expression( expression ), m_Suffix( suffix ){}

            std::shared_ptr<Expression>
                m_Expression;
            std::shared_ptr<PostfixSuffix>
                m_Suffix;
        };


    }
#endif