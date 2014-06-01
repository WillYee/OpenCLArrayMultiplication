#include "../include/FileIOException.h"

FileIOException::FileIOException(const std::string& msg)
    : runtime_error(msg.c_str())
{
}

FileIOException::~FileIOException()
{
}
