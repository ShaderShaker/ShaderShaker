#ifndef STATEMENT_NODE_H
    #define STATEMENT_NODE_H

    namespace AST
    {
        struct Expression;

        struct Statement : Node
        {

        };

        struct ReturnStatement : Statement
        {
            AST_HandleVisitor()

            std::shared_ptr<Expression>
                m_Expression;
        };

        struct BreakStatement : Statement
        {
            AST_HandleVisitor()
        };

        struct ContinueStatement : Statement
        {
            AST_HandleVisitor()
        };

        struct DiscardStatement : Statement
        {
            AST_HandleVisitor()
        };

        struct EmptyStatement : Statement
        {
            AST_HandleVisitor()
        };

        struct ExpressionStatement : Statement
        {
            AST_HandleVisitor()

            ExpressionStatement( Expression * expression ) : m_Expression( expression ) {}

            std::shared_ptr<Expression>
                m_Expression;
        };

        struct IfStatement : Statement
        {
            AST_HandleVisitor()

            IfStatement( Expression * condition, Statement * then_statement, Statement * else_statement )
                :
                m_Condition( condition ),
                m_ThenStatement( then_statement ),
                m_ElseStatement( else_statement )
            {

            }

            std::shared_ptr<Expression>
                m_Condition;
            std::shared_ptr<Statement>
                m_ThenStatement,
                m_ElseStatement;
        };

        struct WhileStatement : Statement
        {
            WhileStatement( Expression * condition, Statement * statement ) : m_Condition( condition ), m_Statement( statement ) {}

            std::shared_ptr<Expression>
                m_Condition;
            std::shared_ptr<Statement>
                m_Statement;
        };

        struct DoWhileStatement : Statement
        {
            DoWhileStatement( Expression * condition, Statement * statement ) : m_Condition( condition ), m_Statement( statement ) {}

            std::shared_ptr<Expression>
                m_Condition;
            std::shared_ptr<Statement>
                m_Statement;
        };

        struct BlockStatement : Statement
        {
            void AddStatement( Statement * statement ){ m_StatementTable.emplace_back( statement ); }

            std::vector< std::shared_ptr<Statement> >
                m_StatementTable;
        };

    }

#endif