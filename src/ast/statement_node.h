#pragma once

namespace AST
{
    struct Expression;

    struct Statement : Node
    {
        virtual Statement *Clone() const override
        {
            return 0;
        }
    };

    struct ReturnStatement : Statement
    {
        AST_HandleVisitor();

        ReturnStatement()
        {
        }
        ReturnStatement( Expression *expression ) : m_Expression( expression )
        {
        }

        ReturnStatement *Clone() const override;

        Base::ObjectRef< Expression > m_Expression;
    };

    struct BreakStatement : Statement
    {
        AST_HandleVisitor();

        BreakStatement *Clone() const override
        {
            return new BreakStatement;
        }
    };

    struct ContinueStatement : Statement
    {
        AST_HandleVisitor();

        ContinueStatement *Clone() const override
        {
            return new ContinueStatement;
        }
    };

    struct DiscardStatement : Statement
    {
        AST_HandleVisitor();

        DiscardStatement *Clone() const override
        {
            return new DiscardStatement;
        }
    };

    struct EmptyStatement : Statement
    {
        AST_HandleVisitor();

        EmptyStatement *Clone() const override
        {
            return new EmptyStatement;
        }
    };

    struct ExpressionStatement : Statement
    {
        AST_HandleVisitor();

        ExpressionStatement()
        {
        }
        ExpressionStatement( Expression *expression ) : m_Expression( expression )
        {
        }

        ExpressionStatement *Clone() const override;

        Base::ObjectRef< Expression > m_Expression;
    };

    struct IfStatement : Statement
    {
        AST_HandleVisitor();

        IfStatement()
        {
        }
        IfStatement( Expression *condition, Statement *then_statement, Statement *else_statement )
            : m_Condition( condition ), m_ThenStatement( then_statement ), m_ElseStatement( else_statement )
        {
        }

        IfStatement *Clone() const override;

        Base::ObjectRef< Expression > m_Condition;
        Base::ObjectRef< Statement > m_ThenStatement, m_ElseStatement;
    };

    struct WhileStatement : Statement
    {
        AST_HandleVisitor();

        WhileStatement()
        {
        }
        WhileStatement( Expression *condition, Statement *statement )
            : m_Condition( condition ), m_Statement( statement )
        {
        }

        WhileStatement *Clone() const override;

        Base::ObjectRef< Expression > m_Condition;
        Base::ObjectRef< Statement > m_Statement;
    };

    struct DoWhileStatement : Statement
    {
        AST_HandleVisitor();

        DoWhileStatement()
        {
        }
        DoWhileStatement( Expression *condition, Statement *statement )
            : m_Condition( condition ), m_Statement( statement )
        {
        }

        DoWhileStatement *Clone() const override;

        Base::ObjectRef< Expression > m_Condition;
        Base::ObjectRef< Statement > m_Statement;
    };

    struct ForStatement : Statement
    {
        ForStatement()
        {
        }
        ForStatement( Statement *init_statement,
            Expression *equality_expression,
            Expression *modify_expression,
            Statement *statement )
            : m_InitStatement( init_statement ),
              m_Statement( statement ),
              m_EqualityExpression( equality_expression ),
              m_ModifyExpression( modify_expression )
        {
        }

        ForStatement *Clone() const override;

        Base::ObjectRef< Statement > m_InitStatement, m_Statement;
        Base::ObjectRef< Expression > m_EqualityExpression, m_ModifyExpression;
    };

    struct BlockStatement : Statement
    {
        AST_HandleVisitor();

        void AddStatement( Statement *statement )
        {
            m_StatementTable.emplace_back( statement );
        }

        BlockStatement *Clone() const override;

        std::vector< Base::ObjectRef< Statement > > m_StatementTable;
    };

    struct VariableDeclarationStatement : Statement
    {
        AST_HandleVisitor();

        void SetType( Type *type )
        {
            assert( type );
            m_Type = type;
        }
        void AddStorageClass( StorageClass *storage_class )
        {
            assert( storage_class );
            m_StorageClass.emplace_back( storage_class );
        }
        void AddTypeModifier( TypeModifier *type_modifier )
        {
            assert( type_modifier );
            m_TypeModifier.emplace_back( type_modifier );
        }
        void AddBody( VariableDeclarationBody *body )
        {
            assert( body );
            m_BodyTable.emplace_back( body );
        }

        VariableDeclarationStatement *Clone() const override;

        Base::ObjectRef< Type > m_Type;
        std::vector< Base::ObjectRef< StorageClass > > m_StorageClass;
        std::vector< Base::ObjectRef< TypeModifier > > m_TypeModifier;
        std::vector< Base::ObjectRef< VariableDeclarationBody > > m_BodyTable;
    };

    struct AssignmentStatement : Statement
    {
        AST_HandleVisitor();

        AssignmentStatement()
        {
        }
        AssignmentStatement( LValueExpression *lvexp, AssignmentOperator op, Expression *exp )
            : m_Expression( new AssignmentExpression( lvexp, op, exp ) )
        {
        }

        AssignmentStatement *Clone() const override;

        Base::ObjectRef< AssignmentExpression > m_Expression;
    };

}
