#pragma once

#include <set>
#include <map>
#include <string>
#include <memory>
#include "fragment_definition.h"
#include "base/object.h"
#include "base/object_ref.h"
namespace AST
{
    struct FunctionDeclaration;
}

namespace Generation
{
    class FunctionDefinition : public Base::Object
    {

      public:
        using Ref = Base::ObjectRef< FunctionDefinition >;

        void FillFromFunctionDeclaration( AST::FunctionDeclaration &declaration );

        const std::set< std::string > &GetInSemanticSet() const
        {
            return m_InSemanticSet;
        }

        const std::set< std::string > &GetOutSemanticSet() const
        {
            return m_OutSemanticSet;
        }

        const std::set< std::string > &GetInOutSemanticSet() const
        {
            return m_InOutSemanticSet;
        }

        const AST::FunctionDeclaration &GetFunctionDeclaration() const
        {
            return *m_FunctionDeclaration;
        }

        void GetAllOutSemanticSet( std::set< std::string > &set );
        void GetAllInSemanticSet( std::set< std::string > &set );

        const std::string &GetName() const
        {
            return m_Name;
        }

        std::string GetSemanticType( const std::string &semantic ) const;

        const std::map< std::string, std::string > &GetSemanticTypeTable() const
        {
            return m_SemanticToTypeMap;
        }

        const std::string &GetSourceFilename() const;
        int GetSourceFileLine() const;

      private:
        void SetTypeForSemantic( const std::string &type, const std::string &semantic );

        std::string m_Name;
        std::set< std::string > m_InSemanticSet, m_OutSemanticSet, m_InOutSemanticSet;
        std::map< std::string, std::string > m_SemanticToTypeMap;

        Base::ObjectRef< AST::FunctionDeclaration > m_FunctionDeclaration;
    };

}
