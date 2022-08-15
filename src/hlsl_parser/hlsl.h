#pragma once

namespace AST
{
    struct TranslationUnit;
}
#include <base/object_ref.h>
#include <string>

namespace HLSL
{
    Base::ObjectRef< AST::TranslationUnit > ParseHLSL( const std::string &filename );
}
