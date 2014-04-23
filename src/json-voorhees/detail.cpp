/** \file
 *  
 *  Copyright (c) 2012 by Travis Gockel. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the Apache License
 *  as published by the Apache Software Foundation, either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  \author Travis Gockel (travis@gockelhut.com)
**/
#include "detail.hpp"
#include "char_convert.hpp"

#include <sstream>

namespace jsonv
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// kind                                                                                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* kind_desc(kind type)
{
    switch (type)
    {
    case kind::object:
        return "object";
    case kind::array:
        return "array";
    case kind::string:
        return "string";
    case kind::integer:
        return "integer";
    case kind::decimal:
        return "decimal";
    case kind::boolean:
        return "boolean";
    case kind::null:
        return "null";
    default:
        return "UNKNOWN";// should never happen
    }
}

bool kind_valid(kind k)
{
    switch (k)
    {
    case kind::object:
    case kind::array:
    case kind::string:
    case kind::integer:
    case kind::decimal:
    case kind::boolean:
    case kind::null:
        return true;
    default:
        return false;
    }
}

void check_type(kind expected, kind actual)
{
    if (expected != actual)
    {
        std::ostringstream stream;
        stream << "Unexpected type: expected " << kind_desc(expected)
            << " but found " << kind_desc(actual) << ".";
        throw kind_error(stream.str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Printing                                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream_type& stream_escaped_string(ostream_type& stream, const string_type& str)
{
    stream << "\"";
    detail::string_encode(stream, str);
    stream << "\"";
    return stream;
}

}