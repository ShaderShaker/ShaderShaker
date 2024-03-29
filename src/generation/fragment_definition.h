#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>
#include "base/object.h"
#include "base/object_ref.h"

namespace AST
{
    struct TranslationUnit;
}

namespace Generation
{
    class FunctionDefinition;

    class FragmentDefinition : public Base::Object
    {

      public:
        using Ref = Base::ObjectRef< FragmentDefinition >;

        static Base::ObjectRef< FragmentDefinition > GenerateFragment( AST::TranslationUnit &translation_unit );

        bool FindFunctionDefinition( Base::ObjectRef< FunctionDefinition > &definition, const std::string &name ) const;

        bool FindFunctionDefinitionMatchingSemanticSet( Base::ObjectRef< FunctionDefinition > &definition,
            const std::set< std::string > &semantic_set ) const;

        const AST::TranslationUnit &GetTranslationUnit() const
        {
            return *m_TranslationUnit;
        }

      private:
        Base::ObjectRef< AST::TranslationUnit > m_TranslationUnit;
        std::vector< Base::ObjectRef< FunctionDefinition > > m_FunctionDefinitionTable;
    };

}
