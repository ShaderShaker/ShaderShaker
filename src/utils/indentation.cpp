#include "utils/indentation.h"
#include <assert.h>

int get_indent_index()
{
    static int index = std::ios_base::xalloc();
    return index;
}

std::ios_base &inc_ind( std::ios_base &stream )
{
    stream.iword( get_indent_index() )++;
    return stream;
}

std::ios_base &dec_ind( std::ios_base &stream )
{
    long & value = stream.iword( get_indent_index() );

    value--;

    assert( value >= 0 );

    return stream;
}
