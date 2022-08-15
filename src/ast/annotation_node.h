#pragma once

namespace AST
{
    struct AnnotationEntry;

    struct Annotations : Node
    {
        AST_HandleVisitor();

        using AnnotationTableType = std::vector< Base::ObjectRef< AnnotationEntry > >;

        void AddEntry( AnnotationEntry *entry )
        {
            m_AnnotationTable.emplace_back( entry );
        }

        Annotations *Clone() const override;

        AnnotationTableType m_AnnotationTable;
    };

    struct AnnotationEntry : Node
    {
        AST_HandleVisitor();

        AnnotationEntry()
        {
        }
        AnnotationEntry( const std::string &type, const std::string &name, const std::string &value )
            : m_Type( type ), m_Name( name ), m_Value( value )
        {
        }

        AnnotationEntry *Clone() const override;

        std::string m_Type, m_Name, m_Value;
    };
}
