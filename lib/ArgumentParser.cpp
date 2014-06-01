#include <cstdlib>

#include "../include/ArguementParser.h"
#include "../include/ParseException.h"

ArgumentParser::ArgumentParser(int argc, const char* argv[])
: num_elements(0)
, local_size(0)
, argc(argc)
{
    // Copy all the commandline args into a string array
    this->argv = std::vector<std::string>(argv, argv + argc);
}

void ArgumentParser::Validate()
{
    if (argc == 5)
    {
        Parse();
    }
    else
    {
        throw ParseException("Not enough commnandline args");
    }
}

void ArgumentParser::Parse()
{
    num_elements = atoi(argv[2].c_str());
    local_size = atoi(argv[4].c_str());

    if (argv[1].compare("-N") != 0 ||
        num_elements == 0 || // Make sure the 3rd argument is an integer
        argv[3].compare("-L") != 0 ||
        local_size == 0) // Make sure the 5th argument is an integer
    {
        throw ParseException("Invalid commandline args");
    }
}