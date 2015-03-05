#ifndef VISITOR_ITEM_SEPARATOR_H
    #define VISITOR_ITEM_SEPARATOR_H

    #include <string>
    #include <iosfwd>

    namespace AST
    {
        class ConstVisitor;
        
        template< class _Table_ >
        class VisitorItemSeparator
        {
        public:

            virtual void operator()( ConstVisitor & visitor, const _Table_ & /*table*/, const typename _Table_::const_iterator & current_iterator )
            {
                ( *current_iterator )->Visit( visitor );
            }
        };

        template< class _Table_ >
        class VisitorStreamArrayItemSeparator : public VisitorItemSeparator< _Table_ >
        {
        public:
            
            VisitorStreamArrayItemSeparator( std::ostream & stream, const std::string & separator = ",", const bool add_endl = false ) :
                VisitorItemSeparator< _Table_ >(), m_Stream(stream), m_Separator(separator), m_AddEndl( add_endl )
            {
            }

            virtual void operator()( ConstVisitor & visitor, const  _Table_ & table, const typename _Table_::const_iterator & current_iterator ) override
            {
                if ( current_iterator != table.begin() )
                {
                    m_Stream << m_Separator;
                }

                if ( m_AddEndl )
                {
                    m_Stream << endl_ind;
                }

                ( *current_iterator )->Visit( visitor );
            }

        private:

            VisitorStreamArrayItemSeparator & operator =( const VisitorStreamArrayItemSeparator & );

            std::ostream
                & m_Stream;
            std::string
                m_Separator;
            bool
                m_AddEndl;
        };
    }

#endif