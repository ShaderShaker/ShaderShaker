#pragma once

namespace Base
{
    class Object
    {
      public:
        Object() : m_ReferenceCount( 0 )
        {
        }

        void AddRef() const;
        void RemoveRef() const;

      protected:
        virtual ~Object();

      private:
        mutable int m_ReferenceCount;
    };
}
