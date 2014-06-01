#pragma once
#ifndef FILEIOEXCPETION_H
#define FILEIOEXCEPTION_H

#include <stdexcept>
#include <string>

class FileIOException : public std::runtime_error
{
public:
    FileIOException(const std::string& msg);
    ~FileIOException();

    FileIOException& operator=(const FileIOException&); // Disable assignment operator

};

#endif