#pragma  once
#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <vector>
#include <string>

class ArgumentParser
{
public:

    ArgumentParser(int argc, const char* argv[]);
    ~ArgumentParser() {}

    void               Validate();
    int                get_num_elements() { return num_elements; }
    int                get_local_size() { return local_size; }

private:

    void Parse();
    int  num_elements;
    int  local_size;

    int                      argc;
    std::vector<std::string> argv;

    ArgumentParser(const ArgumentParser&); // Disable copy constructor
    ArgumentParser& operator=(const ArgumentParser&); // Disable assignment operator
};

#endif