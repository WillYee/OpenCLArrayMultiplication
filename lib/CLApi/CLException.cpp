#include "../../include/CLApi/CLException.h"

CLException::CLException(const std::string& msg)
: runtime_error(msg)
{
}


CLException::~CLException()
{
}
