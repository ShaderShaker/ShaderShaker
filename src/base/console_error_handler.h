#pragma once

#include <base/error_handler_interface.h>

namespace Base
{
    class ConsoleErrorHandler : public ErrorHandlerInterface
    {
      public:
        void ReportError( const std::string &message, const std::string &file ) override;
    };
}