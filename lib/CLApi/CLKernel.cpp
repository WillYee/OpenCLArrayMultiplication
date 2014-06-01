#include <fstream>
#include <sstream>
#include <string>

#include "../../include/CLApi/CLKernel.h"
#include "../../include/CLApi/CLException.h"
#include "../../include/FileIOException.h"


CLKernel::CLKernel(const std::string& function, 
                   const std::string& file, 
                   cl::Context& ctx, 
                   cl::Device& default_device)
    : function_name(function)
    , file_name(file)
    , context(ctx)
    , device(default_device)
{
    build_program();
    kernel = cl::Kernel(program, function_name.c_str());
}

void CLKernel::build_program()
{
    cl::Program::Sources sources;

    std::ifstream input_stream(file_name, std::ios::in | std::ifstream::binary);

    if (input_stream)
    {
        // Read in the cl file and parse the string source
        std::string        raw_src;
        std::ostringstream contents;

        contents << input_stream.rdbuf();
        input_stream.close();
        raw_src = contents.str();
        sources.push_back({ raw_src.c_str(), raw_src.length() });

        program = cl::Program(context, sources);

        if (program.build({ device }) == CL_SUCCESS)
        {
            return;
        }

        throw CLException("Error building: " + program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device));

    }

    throw FileIOException("Could not open file\n");
}

void CLKernel::set_kernel_arg(int arg_num, cl::Buffer& arg)
{
    if (kernel.setArg(arg_num, arg) != CL_SUCCESS)
    {
        // Convert int to string
        std::stringstream ss;
        ss << arg_num;

        throw CLException("Could not set kernel arg: " + ss.str());
    }
}

cl::Kernel& CLKernel::get_kernel()
{
    return kernel;
}

CLKernel::~CLKernel()
{
}
