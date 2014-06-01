#pragma once
#ifndef CLEXCEPTION_H
#define CLEXCEPTION_H

#include <stdexcept>
#include <string>

class CLException : public std::runtime_error
{
public:
    CLException(const std::string& msg);
    ~CLException();

private:

    CLException& operator=(const CLException&); // Disable assignment operator
};

#endif