#include "fragment_definition.h"
#include "function_definition.h"
#include "ast/empty_visitor.h"
#include "ast/node.h"
#include <algorithm>

namespace Generation
{
    namespace
    {
        template < typename T >
        struct Counter
        {
            using iterator_category = std::output_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T *;
            using reference = T &;

            size_t *m_Count;

            explicit Counter( size_t *count ) : m_Count( count )
            {
            }

            Counter( const Counter &counter ) = default;
            Counter( Counter &&counter ) = default;
            Counter &operator=( const Counter &counter ) = default;
            Counter &operator=( Counter &&counter ) = default;

            void operator()( T & /*value*/ )
            {
                ++*m_Count;
            }

            void operator=( T & /*value*/ )
            {
                ++*m_Count;
            }

            T operator*()
            {
                return {};
            }
            Counter &operator++()
            {
                return *this;
            }
            Counter &operator++( int )
            {
                return *this;
            }
        };
    }

    class GetFunctionVisitor : public AST::EmptyVisitor
    {
      public:
        std::vector< Base::ObjectRef< AST::FunctionDeclaration > >::iterator begin()
        {
            return m_FunctionDeclarationTable.begin();
        }

        std::vector< Base::ObjectRef< AST::FunctionDeclaration > >::iterator end()
        {
            return m_FunctionDeclarationTable.end();
        }

      private:
        virtual void Visit( AST::TranslationUnit &translation_unit ) override
        {
            std::vector< Base::ObjectRef< AST::GlobalDeclaration > >::iterator it, end;
            it = translation_unit.m_GlobalDeclarationTable.begin();
            end = translation_unit.m_GlobalDeclarationTable.end();

            for ( ; it != end; ++it )
            {
                ( *it )->Visit( *this );
            }
        }

        virtual void Visit( AST::FunctionDeclaration &function_declaration ) override
        {
            m_FunctionDeclarationTable.emplace_back( &function_declaration );
        }

        std::vector< Base::ObjectRef< AST::FunctionDeclaration > > m_FunctionDeclarationTable;
    };

    Base::ObjectRef< FragmentDefinition > FragmentDefinition::GenerateFragment( AST::TranslationUnit &translation_unit )
    {
        GetFunctionVisitor visitor;
        Base::ObjectRef< FragmentDefinition > fragment_definition;

        translation_unit.Visit( visitor );

        fragment_definition = new FragmentDefinition;

        fragment_definition->m_TranslationUnit = &translation_unit;

        std::vector< Base::ObjectRef< AST::FunctionDeclaration > >::iterator it, end;

        for ( it = visitor.begin(), end = visitor.end(); it != end; ++it )
        {
            Base::ObjectRef< FunctionDefinition > function_definition( new FunctionDefinition );

            function_definition->FillFromFunctionDeclaration( **it );

            fragment_definition->m_FunctionDefinitionTable.push_back( function_definition );
        }

        return fragment_definition;
    }

    bool FragmentDefinition::FindFunctionDefinition( Base::ObjectRef< FunctionDefinition > &definition,
        const std::string &name ) const
    {
        std::vector< Base::ObjectRef< FunctionDefinition > >::const_iterator it, end;

        for ( it = m_FunctionDefinitionTable.begin(), end = m_FunctionDefinitionTable.end(); it != end; ++it )
        {
            if ( ( *it )->GetName() == name )
            {
                definition = *it;
                return true;
            }
        }

        return false;
    }

    bool FragmentDefinition::FindFunctionDefinitionMatchingSemanticSet(
        Base::ObjectRef< FunctionDefinition > &definition,
        const std::set< std::string > &semantic_set ) const
    {
        std::vector< Base::ObjectRef< FunctionDefinition > >::const_iterator it, end;

        for ( it = m_FunctionDefinitionTable.begin(), end = m_FunctionDefinitionTable.end(); it != end; ++it )
        {
            size_t count;

            count = 0;

            std::set_intersection( semantic_set.begin(),
                semantic_set.end(),
                ( *it )->GetOutSemanticSet().begin(),
                ( *it )->GetOutSemanticSet().end(),
                Counter< std::string >( &count ) );

            std::set_intersection( semantic_set.begin(),
                semantic_set.end(),
                ( *it )->GetInOutSemanticSet().begin(),
                ( *it )->GetInOutSemanticSet().end(),
                Counter< std::string >( &count ) );

            if ( count > 0 )
            {
                definition = *it;
                return true;
            }
        }

        return false;
    }

}