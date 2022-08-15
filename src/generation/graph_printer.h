#pragma once

#include <ostream>
#include <set>

namespace Generation
{
    class GraphNode;

    struct GraphPrinter
    {
        GraphPrinter( std::ostream &output_stream );
        void Initialize();
        void Visit( const GraphNode &node );
        void Finalize();

        std::ostream &m_OutputStream;
        std::set< const GraphNode * > m_VisitedNodeSet;

      private:
        GraphPrinter &operator=( const GraphPrinter & );
    };

}
