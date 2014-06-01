#pragma once
#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <stdexcept>
#include <string>

class ParseException : public std::runtime_error
{
public:
    ParseException(const std::string& msg);
    ~ParseException();

    ParseException& operator=(const ParseException&); // Disable assignment operator

};

#endif