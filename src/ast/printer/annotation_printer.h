#pragma once

#include "ast/tree_traverser.h"
#include <ostream>

namespace AST
{
    class AnnotationPrinter : public TreeTraverser
    {
      public:
        AnnotationPrinter( std::ostream &stream ) : m_Stream( stream )
        {
        }
        AnnotationPrinter &operator=( const AnnotationPrinter & ) = delete;

        void Visit( const Node &node ) override;
        void Visit( const Annotations &annotations ) override;
        void Visit( const AnnotationEntry &annotation_entry ) override;

      private:
        std::ostream &m_Stream;
    };
}
