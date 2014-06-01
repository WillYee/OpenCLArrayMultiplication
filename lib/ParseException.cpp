#include "../include/ParseException.h"

ParseException::ParseException(const std::string& msg)
: runtime_error(msg.c_str())
{
}

ParseException::~ParseException()
{
}
