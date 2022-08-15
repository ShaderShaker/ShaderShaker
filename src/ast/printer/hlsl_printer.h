#pragma once

#include "ast/printer/xlsl_printer.h"
#include <ostream>

namespace AST
{

    class HLSLPrinter : public XLSLPrinter
    {
      public:
        HLSLPrinter( std::ostream &stream ) : XLSLPrinter( stream )
        {
        }

        using XLSLPrinter::Visit;
        void Visit( const VariableDeclarationBody &body ) override;
        void Visit( const InitialValue &initial_value ) override;
        void Visit( const Annotations &annotations ) override;
        void Visit( const AnnotationEntry &annotation_entry ) override;
        void Visit( const TextureDeclaration &declaration ) override;
        void Visit( const SamplerDeclaration &declaration ) override;
        void Visit( const SamplerBody &body ) override;
        void Visit( const StructDefinition &definition ) override;
        void Visit( const FunctionDeclaration &declaration ) override;
        void Visit( const Argument &argument ) override;
        void Visit( const DiscardStatement &statement ) override;
    };
}

