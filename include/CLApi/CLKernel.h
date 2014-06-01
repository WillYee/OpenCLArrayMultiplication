#pragma once

#ifndef CLKERNEL_H
#define CLKERNEL_H

#include <string>
#include <vector>

#include "../cl.hpp"

class CLKernel
{

public:
    CLKernel(const std::string& function, 
             const std::string& file, 
             cl::Context& ctx, 
             cl::Device& default_device);

    ~CLKernel();

    cl::Kernel& get_kernel();

    void set_kernel_arg(int arg_num, cl::Buffer& arg);
private:
    
    void build_program();

    const std::string& function_name;
    const std::string& file_name;
    cl::Context& context;
    
    cl::Kernel   kernel;
    cl::Program  program;
    cl::Device&  device;

    CLKernel(const CLKernel&); // Disable copy constructor
    CLKernel& operator=(const CLKernel&); // Disable assignment operator
};

#endif