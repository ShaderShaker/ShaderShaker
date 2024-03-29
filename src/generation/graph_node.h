#pragma once

#include <vector>
#include <base/object_ref.h>
#include <base/object.h>

#include "function_definition.h"

namespace Generation
{
    class GraphNode : public Base::Object
    {

      public:
        using Ref = Base::ObjectRef< GraphNode >;

        GraphNode();
        GraphNode( FunctionDefinition &definition );

        const std::vector< GraphNode::Ref > &GetChildren() const
        {
            return m_Children;
        }

        bool AddParent( GraphNode &parent );
        FunctionDefinition &GetFunctionDefinition()
        {
            return *m_FunctionDefinition;
        }
        const FunctionDefinition &GetFunctionDefinition() const
        {
            return *m_FunctionDefinition;
        }
        bool HasFunctionDefinition() const
        {
            return m_FunctionDefinition;
        }

        template < typename Visitor >
        void VisitDepthFirst( Visitor &visitor ) const
        {
            for ( std::vector< GraphNode::Ref >::const_iterator it = m_Children.begin(), end = m_Children.end();
                  it != end;
                  ++it )
            {
                ( *it )->VisitDepthFirst( visitor );
            }

            visitor.Visit( *this );
        }

      private:
        bool NodeExistsInParents( const GraphNode &node ) const;

        FunctionDefinition::Ref m_FunctionDefinition;
        std::vector< GraphNode * > m_Parents;
        std::vector< GraphNode::Ref > m_Children;
    };
}
