#pragma once

#include <base/object.h>
#include <base/object_ref.h>
#include <string>

namespace Base
{
    class ErrorHandlerInterface : public Object
    {
      public:
        using Ref = ObjectRef< ErrorHandlerInterface >;

        virtual ~ErrorHandlerInterface()
        {
        }

        virtual void ReportError( const std::string &message, const std::string &file ) = 0;
    };
}
